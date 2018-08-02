#include "StdAfx.h"
#include ".\engine.h"

#include "DataLayer.h"

CAutoSingletonCreator<CEngine> _AutoCreateEngine;


CEngine::CEngine(void)
{
}

CEngine::~CEngine(void)
{
}

void CEngine::TimerProc(HWND /*hwnd*/,UINT /*uMsg*/,UINT_PTR /*idEvent*/,DWORD /*dwTime*/)
{
	//��������� ��� �������� �������
	CSingletonPtr<CEngine> self;
	self->_Connections.CheckItemTimers();
}

void CEngine::Start(void)
{
	CSingletonPtr<CDataLayer> DataLayer;
	if(DataLayer->Initialize())
	{
		if(_Connections.Start())
		{
			_TimerID = SetTimer(NULL, NULL, 500, TimerProc);
			CEventLoggerPtr log;
			log->LogMessage(L"��������� ��������");
			return;
		}
	}

	//��������� ��������� ���������. ������������� ������.
	TerminateProcess(GetCurrentProcess(), ~0);
}

void CEngine::Stop(void)
{
	CEventLoggerPtr log;
	log->LogMessage(L"��������� �����������");

	//���������� ���������
	KillTimer(NULL, _TimerID);
	_Connections.Stop();

	CSingletonPtr<CDataLayer> DataLayer;
	DataLayer->DeInitialize();
}

void CEngine::Pause(void)
{
	CEventLoggerPtr log;
	log->LogMessage(L"��������� ���������� �� �����");

	CSingletonPtr<CDataLayer> DataLayer;
	DataLayer->SetWorkState(FALSE);
}

void CEngine::Continue(void)
{
	CEventLoggerPtr log;
	log->LogMessage(L"��������� ��������");

	CSingletonPtr<CDataLayer> DataLayer;
	DataLayer->SetWorkState(TRUE);
}
