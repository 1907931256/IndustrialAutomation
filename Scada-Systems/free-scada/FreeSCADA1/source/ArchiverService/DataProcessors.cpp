#include "StdAfx.h"
#include ".\dataprocessors.h"
#include <functional>

namespace DataProcessors
{
	fGenEvntOnChange::fGenEvntOnChange()
		:fDataProcessor()
	{
		_Events = NULL;
		_LastData.Clear();
	}

	fGenEvntOnChange::~fGenEvntOnChange()
	{
		_Events = NULL;
	}

	void fGenEvntOnChange::Process(sData& data)
	{
		//���� ����������� � �� �� �����������, ������������
		if(!IsConnected())
		{
			if(!Connect())
			{
				CEventLoggerPtr log;
				log->LogMessage(L"������ ��� ����������� � ��");
				throw E_FAIL;
			}
			//����������� ��������� IEvents
			HRESULT hr;
			hr = _Connection->GetEvents(&_Events);
			if(FAILED(hr))
			{
				CEventLoggerPtr log;
				log->DecodeIError(_Connection);
				throw hr;
			}
		}

		//���������� ������ ������ ���� ���� ���������� ��������
		if(_LastData.vt != VT_EMPTY)
		{
			_LastData.ChangeType(data.Data.vt);
			if(_LastData == data.Data)
				return;	//������ �����. ������� ��������� ������������ ������
		
			//��� ���� BOOL ���� ��������� -1 � 1
			_LastData.ChangeType(data.Data.vt);
			if(_LastData.vt == VT_BOOL)
				_LastData = _LastData.boolVal?1:0;
			if(data.Data.vt == VT_BOOL)
				data.Data = data.Data.boolVal?1:0;

			//���������� �������
			if(_LastData < data.Data)
				_Events->AddEvent(data.ItemID, ET_CHANGE_MIN_TO_MAX, CComVariant());
			else
				_Events->AddEvent(data.ItemID, ET_CHANGE_MAX_TO_MIN, CComVariant());
		}

		//��������� "�������" ��������
		_LastData = data.Data;
	}

	fGenEvntOnCrossValue::fGenEvntOnCrossValue(CComVariant Value,ULONG EvntUp, ULONG EvntDown)
		: fDataProcessor()
		, _Value(Value)
		, _Reach(FALSE)
		, _Leave(FALSE)
		, _EvntUp(EvntUp)
		, _EvntDown(EvntDown)
	{
		
	}
	fGenEvntOnCrossValue::~fGenEvntOnCrossValue()
	{
		_Events = NULL;
	}

	void fGenEvntOnCrossValue::Process(sData& data)
	{
		//���� ����������� � �� �� �����������, ������������
		if(!IsConnected())
		{
			if(!Connect())
			{
				CEventLoggerPtr log;
				log->LogMessage(L"������ ��� ����������� � ��");
				throw E_FAIL;
			}
			//����������� ��������� IEvents
			HRESULT hr;
			hr = _Connection->GetEvents(&_Events);
			if(FAILED(hr))
			{
				CEventLoggerPtr log;
				log->DecodeIError(_Connection);
				throw hr;
			}
		}

		//��� ���� BOOL ���� ��������� -1 � 1
		if(_Value.vt == VT_BOOL)
			_Value = _Value.boolVal?1:0;
		if(data.Data.vt == VT_BOOL)
			data.Data = data.Data.boolVal?1:0;

		//���������� ������� ������ � ������ ����������� �������
		// �� ���� ������ ������� ������ �� ������������
		if(data.Data > _Value && !_Reach)
		{
			//�������� ������ ������ ��� ��������� ������� �����
			_Events->AddEvent(data.ItemID, _EvntUp, CComVariant());
			_Reach = TRUE;
			_Leave = FALSE;
		}
		else 
			if(data.Data < _Value && !_Leave)
			{
				//�������� ������ ������ ��� ��������� ������� ����
				_Events->AddEvent(data.ItemID, _EvntDown, CComVariant());
				_Reach = FALSE;
				_Leave = TRUE;
			}
	}
}