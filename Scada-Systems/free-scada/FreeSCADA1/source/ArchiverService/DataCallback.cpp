// CDataCallback.cpp : Implementation of CCDataCallback

#include "stdafx.h"
#include "DataCallback.h"
#include "DataLayer.h"
#include "Connections.h"
#include "EventLogger.h"

// CDataCallback

STDMETHODIMP CDataCallback::OnDataChange( DWORD  /*dwTransid*/,  DWORD  /*hGroup*/,  HRESULT  /*hrMasterquality*/,  HRESULT  /*hrMastererror*/,  DWORD  dwCount,  DWORD *  phClientItems,  VARIANT *  pvValues,  WORD *  pwQualities,  FILETIME *  pftTimeStamps,  HRESULT *  /*pErrors*/)
{
	//������� ��������� �� ������� ������ (��� ���� ����������� ��������� �������)
	CSingletonPtr<CDataLayer> DataLayer;
	TDataQueue& queue = DataLayer->LockQueue();

	try
	{
		for(DWORD i=0;i<dwCount;i++)
		{
			//���������� ������ ���������������� ������
			if(_Connections)
				_Connections->UpdateItemTimer(phClientItems[i]);

			if((pwQualities[i]&OPC_QUALITY_MASK)!= OPC_QUALITY_GOOD)
			{
				CString msg;
				msg.Format(L"������ �������� ������: ItemID=%u; Quality=%X",phClientItems[i],pwQualities[i]);
				Helpers::CEventLoggerPtr log;
				log->LogMessage(msg);
				TRACE(L"Data skiped\n\r");
				//continue;
			}
			//�������� ����� ������ � �������
			sData data;
			data.Data		= pvValues[i];
			data.ItemID		= phClientItems[i];
			data.Quality	= pwQualities[i];
			memcpy(&data.Time, &pftTimeStamps[i], sizeof(FILETIME));
			//TRACE(L"Data pushed\n\r");
			queue.push(data);

			//ATLTRACE("*** %s\n",__FUNCTION__);
		}
	}catch(...)
	{
		DataLayer->ReleaseQueue();
		return S_OK;
	}
	//����������� �������
	DataLayer->ReleaseQueue();
	return S_OK;
}

STDMETHODIMP CDataCallback::OnReadComplete( DWORD  /*dwTransid*/,  DWORD  /*hGroup*/,  HRESULT  /*hrMasterquality*/,  HRESULT  /*hrMastererror*/,  DWORD  /*dwCount*/,  DWORD *  /*phClientItems*/,  VARIANT *  /*pvValues*/,  WORD *  /*pwQualities*/,  FILETIME *  /*pftTimeStamps*/,  HRESULT *  /*pErrors*/)
{
	return S_OK;
}

STDMETHODIMP CDataCallback::OnWriteComplete( DWORD  /*dwTransid*/,  DWORD  /*hGroup*/,  HRESULT  /*hrMastererr*/,  DWORD  /*dwCount*/,  DWORD *  /*pClienthandles*/,  HRESULT *  /*pErrors*/)
{
	return S_OK;
}

STDMETHODIMP CDataCallback::OnCancelComplete( DWORD  /*dwTransid*/,  DWORD  /*hGroup*/)
{
	return S_OK;
}