#include "StdAfx.h"
#include ".\connections.h"
#include "DataLayer.h"
#include "EventLogger.h"
#include <vector>

#define LCID_RUSSIAN	MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_NEUTRAL),SORT_DEFAULT)

//"�������" ��� ��������� ����������
struct fCompareConnection
{
	CLSID	_ServerCLSID;
	CString	_Computer;
	ULONG	_UpdateInterval;

	fCompareConnection(CLSID ServerCLSID, CString Computer, ULONG UpdateInterval)
		: _ServerCLSID(ServerCLSID)
		, _Computer(Computer)
		, _UpdateInterval(UpdateInterval){};

	bool operator()(const CConnections::sConnection& conn)
	{
		return (	IsEqualCLSID(_ServerCLSID, conn.ServerCLSID) &&
			StrCmpI(_Computer, conn.Computer) == 0 &&
			_UpdateInterval == conn.UpdateInterval);
	}
};


CConnections::CConnections(void)
{
}

CConnections::~CConnections(void)
{
}

BOOL CConnections::Start(void)
{
	//�������� ������ ������� � ��������� ����� (����������� ������ �� ����������)
	CSingletonPtr<CDataLayer> DataLayer;
	TChannelsMap Channels;
	DataLayer->CopyChannels(Channels);

	//������� ������ ��� ������ ������ � OPC
	_Callback = new CDataCallback(this);

	//������������� ��� ������
	for(TChannelsMap::iterator i=Channels.begin();i!=Channels.end();i++)
	{
		{
			CSingletonPtr<CEventLogger> log;
			CString msg;
			msg.Format(L"����������� ������ '%s'",i->second.Name);
			log->LogMessage(msg);
		}
		//�������� ��������� �� ����������
		sConnection* Connection = GetConnection(i->second.ServerCLSID, i->second.Computer, i->second.UpdateInterval);
		if(Connection)
		{
			ATLASSERT(Connection->OPCGroup != NULL);

			OPCITEMDEF		item;
			OPCITEMRESULT	*results	= NULL;
			HRESULT			*Errors		= NULL;
			HRESULT			hr;

			ZeroMemory(&item, sizeof(OPCITEMDEF));
			item.bActive	= TRUE;
			item.hClient	= i->first;
			item.szItemID	= CComBSTR(i->second.Name);

			//��������� ����� �� ����������
			hr = Connection->OPCGroup->AddItems(1, &item, &results, &Errors);
			if(hr != S_OK)
			{
				//��������� ������
				CSingletonPtr<CEventLogger> log;
				switch(hr) //�������� ������ "� �����"
				{
				case E_FAIL:		log->GenMsg(ERR_OPCCONNECT_FAIL);break;
				case E_OUTOFMEMORY:	log->GenMsg(ERR_OPCCONNECT_OUTOFMEMORY);break;
				case E_INVALIDARG:	log->GenMsg(ERR_OPCCONNECT_INVALIDARG);break;
				default:
					if(FAILED(hr))
						log->GenMsg(ERR_OPCCONNECT_FAIL_UNKN);
				}
				if(Errors) //����� ��������� ��������
				{
					switch(Errors[0])
					{
					case OPC_E_INVALIDITEMID:	log->GenMsg(ERR_OPCCONNECT_INVALIDITEMID);break;
					case OPC_E_UNKNOWNITEMID:	log->GenMsg(ERR_OPCCONNECT_UNKNOWNITEMID);break;
					}
				}
			}
			else
			{
				//��������� ����� � ����� ����������� ������� � ���������� ������
				Connection->Items[i->first] = results[0].hServer;
				Connection->ResetTimer(i->first);
			}
			//����������� ������
			LocalFree(results);
			LocalFree(Errors);
		}
	}
	return TRUE; //��� ���������� ������� ������������
}

void CConnections::Stop(void)
{
	//������������� ��� ����������
	for(TConnections::iterator connection=_Connections.begin();connection!=_Connections.end();connection++)
	{
		ATLASSERT(connection->OPCGroup != NULL);
	
		//���������� ������ hServerItems (��� ����������)
		vector<OPCHANDLE> hServerItems;
		typedef map<DWORD,OPCHANDLE>::const_iterator it;
		for(it tag=connection->Items.begin();tag!=connection->Items.end();tag++)
		{	
			//���� ������ handle ��� � ������ - ���������
			if(find(hServerItems.begin(), hServerItems.end(), tag->second) == hServerItems.end())
				hServerItems.push_back(tag->second);
		}

		//��������� ��� ������
		HRESULT *results;
		TEST_HR(connection->OPCGroup->RemoveItems(static_cast<DWORD>(hServerItems.size()), &hServerItems[0], &results));
		LocalFree(results);

		//"������������" �� �������� ������
		TEST_HR(AtlUnadvise(connection->OPCGroup, __uuidof(IOPCDataCallback), connection->Advise));
		//������� OPC ������
		connection->OPCServer->RemoveGroup(connection->hGroup, FALSE);

		//����������� ����������
		connection->OPCGroup	= NULL;
		connection->OPCServer	= NULL;
	}
	//������� ������ ����������
	_Connections.clear();

	//������� ������ OPCDataCallback 
	_Callback->Release();
	_Callback = NULL;
}

CConnections::sConnection* CConnections::GetConnection(CLSID ServerCLSID, CString Computer, ULONG UpdateInterval)
{
	//���� ���������� ����������� ����� ��� ��������
	TConnections::iterator it = find_if(_Connections.begin(),
										_Connections.end(),
										fCompareConnection(ServerCLSID,Computer,UpdateInterval));
	if(it != _Connections.end())
		return &*it;	//���������� �����������

	CEventLoggerPtr log;
	CString msg;
	msg.Format(L"��������������� ���������� � OPC ��������: Computer='%s', UpdateInterval=%u��",Computer,UpdateInterval);
	log->LogMessage(msg);

	//������ ���������� ���. ������� �����
	sConnection Connection;
	memcpy(&Connection.ServerCLSID, &ServerCLSID, sizeof(CLSID));
	Connection.Computer			= Computer;
	Connection.UpdateInterval	= UpdateInterval;

	//����������� ��������� IOPCServer � ���������� �������
	COSERVERINFO	si;
	MULTI_QI		qi;
	ZeroMemory(&si,sizeof(COSERVERINFO));
	ZeroMemory(&qi,sizeof(MULTI_QI));
	si.pwszName = CComBSTR(Connection.Computer);
	qi.pIID	= &__uuidof(IOPCServer);
	HRESULT hr;
	hr = CoCreateInstanceEx(Connection.ServerCLSID, NULL, CLSCTX_ALL, &si, 1, &qi);
	if(!TEST_HR(hr) || !TEST_HR(qi.hr))
	{
		log->GenMsg(ERR_OPCCONNECT_CANT_CREATE_INSTANCE);
		return NULL;
	}
	hr = qi.pItf->QueryInterface(__uuidof(IOPCServer), (void**)&Connection.OPCServer);
	qi.pItf->Release();
	if(!TEST_HR(hr))
	{
		log->GenMsg(ERR_OPCCONNECT_CANT_QUERY_IOPCSERVER);
		return NULL;
	}

	//��������� ������ �� ������� � ����������� �� ���������
	LONG TimeBias			= NULL;
	FLOAT PercentDeadBand	= NULL;
	GUID riid				= IID_IUnknown;
	CComPtr<IUnknown>		pUnk;
	
	hr = Connection.OPCServer->AddGroup(	CComBSTR(""), TRUE, UpdateInterval,
							0, &TimeBias, &PercentDeadBand, LCID_RUSSIAN,
							&Connection.hGroup, &Connection.UpdateInterval,
							riid, &pUnk);
	if(!TEST_HR(hr))
	{
		log->GenMsg(ERR_OPCCONNECT_CANT_ADD_GROUP);
		return NULL;
	}
	if(!TEST_HR(pUnk.QueryInterface(&Connection.OPCGroup)))
	{
		log->GenMsg(ERR_OPCCONNECT_CANT_QUERY_IOPCITEMMGT);
		return NULL;
	}
	if(Connection.UpdateInterval != UpdateInterval)
	{
		log->GenMsg(ERR_OPCCONNECT_TOO_FAST);
		UpdateInterval = Connection.UpdateInterval;
	}

	//"�������������" �� �������� ������
	hr = AtlAdvise(	Connection.OPCGroup, _Callback, IID_IOPCDataCallback, &Connection.Advise);
	if(!TEST_HR(hr))
	{
		CSingletonPtr<CEventLogger> log;
		if(hr == E_ACCESSDENIED)
			log->GenMsg(ERR_OPCCONNECT_ACCESSDENIED);
		else
			log->GenMsg(ERR_OPCCONNECT_CANT_SUBSCRIBE_CALLBACK);
		return NULL;
	}

	//��������� ����� ������������� ���������� � ������ ����������
	_Connections.push_back(Connection);

	it = find_if(_Connections.begin(),
				_Connections.end(),
				fCompareConnection(ServerCLSID,Computer,UpdateInterval));
	ATLASSERT(it != _Connections.end());
	return &*it;	//���������� �����������
}

void CConnections::UpdateItemTimer(DWORD ItemID)
{
	//���������� ������ � ���������� ������
	for(TConnections::iterator i=_Connections.begin();i!=_Connections.end();i++)
	{
		if(i->Items.find(ItemID) != i->Items.end())
			i->ResetTimer(ItemID);
	}
}

void CConnections::CheckItemTimers()
{
	//������������� ��� ����������
	typedef map<DWORD,OPCHANDLE>::iterator it;
	for(TConnections::iterator connection=_Connections.begin();connection!=_Connections.end();connection++)
	{
		//������������� ��� ������������ ������
		for(it tag=connection->Items.begin();tag!=connection->Items.end();tag++)
		{
			//�� ��������� �� ������?
			if(connection->IsTimeout(tag->first))
			{	//������ ���������. ���������������.
				ATLASSERT(connection->OPCGroup != NULL);

				CSingletonPtr<CEventLogger> log;
				log->GenMsg(ERR_OPCCONNECT_LOST_CONNECTION);

				//�������� ������ �������� �������� ������
				CSingletonPtr<CDataLayer> DataLayer;
				sChannel Channel;
				if(DataLayer->GetChannelByItemID(tag->first, Channel) == FALSE)
				{
					
					log->GenMsg(ERR_OPCCONNECT_FAIL);
					continue;
				}

				//�������������� �����
				OPCITEMDEF		item;
				OPCITEMRESULT	*results	= NULL;
				HRESULT			*Errors		= NULL;

				ZeroMemory(&item, sizeof(OPCITEMDEF));
				item.bActive	= TRUE;
				item.hClient	= tag->first;
				item.szItemID	= CComBSTR(Channel.Name);

				HRESULT hr;
				hr = connection->OPCGroup->AddItems(1, &item, &results, &Errors);
				if(hr != S_OK)
				{
					if(hr == 0x800706ba)
					{
						//������ RPC ���������� (����� ������������� ����� ����������)
						ReconnectAllItemsOnConnection(*connection);
						return;
					}

					if(hr != S_OK)
					{
						CSingletonPtr<CEventLogger> log;
						switch(hr)
						{
						case E_FAIL:		log->GenMsg(ERR_OPCCONNECT_FAIL);break;
						case E_OUTOFMEMORY:	log->GenMsg(ERR_OPCCONNECT_OUTOFMEMORY);break;
						case E_INVALIDARG:	log->GenMsg(ERR_OPCCONNECT_INVALIDARG);break;
						default:
							if(FAILED(hr))
								log->GenMsg(ERR_OPCCONNECT_FAIL_UNKN);
						}
						if(Errors)
						{
							switch(Errors[0])
							{
							case OPC_E_INVALIDITEMID:	log->GenMsg(ERR_OPCCONNECT_INVALIDITEMID);break;
							case OPC_E_UNKNOWNITEMID:	log->GenMsg(ERR_OPCCONNECT_UNKNOWNITEMID);break;
							}
						}
					}
				}
				else
				{
					//��������� handle ������ � ����� �����������
					connection->Items[tag->first] = results[0].hServer;
					//���������� ������
					connection->ResetTimer(tag->first);
				}
				LocalFree(results);
				LocalFree(Errors);
			}
		}
	}
}

void CConnections::ReconnectAllItemsOnConnection(sConnection OldConnection)
{
	//������ ������ ������������ ������� (�� ��� ����� ���������� ������)
	vector<DWORD> ItemIDs;
	for(map<DWORD,OPCHANDLE>::const_iterator i=OldConnection.Items.begin();i!=OldConnection.Items.end();i++)
		ItemIDs.push_back(i->first);

	//���� ��������� ���������� � ������ ���������� � ������� ���
	TConnections::iterator it = find_if(_Connections.begin(),
										_Connections.end(), 
										fCompareConnection(OldConnection.ServerCLSID,OldConnection.Computer,OldConnection.UpdateInterval));
	ATLASSERT(it != _Connections.end());
	//"������������" �� �������� ������
	TEST_HR(AtlUnadvise(it->OPCGroup, __uuidof(IOPCDataCallback), it->Advise));
	//������� OPC ������
	it->OPCServer->RemoveGroup(it->hGroup, FALSE);
	//����������� ����������
	it->OPCGroup	= NULL;
	it->OPCServer	= NULL;
	_Connections.erase(it);

	//������������� ��� ������
	for(vector<DWORD>::iterator ItemID=ItemIDs.begin();ItemID!=ItemIDs.end();ItemID++)
	{
		//�������� ��������� ���������� � ������
		CSingletonPtr<CDataLayer> DataLayer;
		sChannel Channel;
		DataLayer->GetChannelByItemID(*ItemID, Channel);

		//��������/���������� ����� ����������
		sConnection* Connection = GetConnection(OldConnection.ServerCLSID, OldConnection.Computer, OldConnection.UpdateInterval);
		if(Connection)
		{
			ATLASSERT(Connection->OPCGroup != NULL);

			//������ ����� �� ����������
			OPCITEMDEF		item;
			OPCITEMRESULT	*results	= NULL;
			HRESULT			*Errors		= NULL;
			
			ZeroMemory(&item, sizeof(OPCITEMDEF));
			item.bActive	= TRUE;
			item.hClient	= *ItemID;
			item.szItemID	= CComBSTR(Channel.Name);

			HRESULT hr;
			hr = Connection->OPCGroup->AddItems(1, &item, &results, &Errors);
			if(hr != S_OK)
			{
				//��������� ������
				CSingletonPtr<CEventLogger> log;
				switch(hr)
				{
				case E_FAIL:		log->GenMsg(ERR_OPCCONNECT_FAIL);break;
				case E_OUTOFMEMORY:	log->GenMsg(ERR_OPCCONNECT_OUTOFMEMORY);break;
				case E_INVALIDARG:	log->GenMsg(ERR_OPCCONNECT_INVALIDARG);break;
				default:
					if(FAILED(hr))
						log->GenMsg(ERR_OPCCONNECT_FAIL_UNKN);
				}
				if(Errors)
				{
					switch(Errors[0])
					{
					case OPC_E_INVALIDITEMID:	log->GenMsg(ERR_OPCCONNECT_INVALIDITEMID);break;
					case OPC_E_UNKNOWNITEMID:	log->GenMsg(ERR_OPCCONNECT_UNKNOWNITEMID);break;
					}
				}
			}
			else
			{
				//��������� ����� � ����� ����������� ������� � ���������� ������
				Connection->Items[*ItemID] = results[0].hServer;
				Connection->ResetTimer(*ItemID);
			}
			LocalFree(results);
			LocalFree(Errors);
		}
	}
}