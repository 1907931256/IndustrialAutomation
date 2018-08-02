#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   15:54
	���� � �����: 	d:\Work\Projects\�-����\Source\Visualizator\Doc.h
	����������:	    d:\Work\Projects\�-����\Source\Visualizator
	��� �����:	    Doc
	����������:	    h
	�����(�):	    ������
    �����(�):       CDoc
	
��������:	�������� ��������� ������� �������� ������� � ����������� � OPC.
*********************************************************************/


#include "ArrayOfOPCConnection.h"

class CDoc
	: public DVF::CBaseDocument
{
public:
	CArchiveManager		m_Archive;			//�����
	sSchemaSettings		m_SchemaSettings;	//��������� ������� �����

	CDoc(void);
	~CDoc(void);

	//��������� ������
	bool LoadProject(wstring FileName);
	
	//������� �����
	bool SelectSchema(wstring Name);

	//�������� ���
	void EmptyView();

	//������������ � OPC
	void ConnectToOPC();

	/// Refresh channels (COPCDataCallback sould be called for all tags)
	void RefreshOPC();

	//�������� ��� ���������� �� OPC Handle
	inline wstring GetVariableNameByOPCHandle(OPCHANDLE handle){return _OPCHandles[handle];};

	//void UpdateTagTimer(OPCHANDLE handle);
	//BOOL TestTagTimer();
	inline bool TestCon(){return _OPCConnections->TestServers();};


protected:
	CArrayOfOPCConnection*	_OPCConnections;
	map<OPCHANDLE,wstring>	_OPCHandles;
	map<OPCHANDLE,ULONG>	_OPCTagTimer;
	CComAutoCriticalSection _OPCTimerCS;

	void UpdateMainCaption();
};