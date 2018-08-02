#pragma once
/********************************************************************
	������:	        2004/12/07
	������:	        7.12.2004   18:03
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\VariableMenager.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    VariableMenager
	����������:	    h
	�����(�):	    ������
    �����(�):       CVariableMenager
	
	  ����� "�������� ����������".
	�������� ������ ����������. ���������� �������� � ��������� ����.������������ 
	���������� �����������. ���� ��������� ������������� �������������.

	  ���� ���������� ������� � �����-�� ������� OPC, �� ������	���� ���������� 
	�������� ��������� ���������������� ������ OPC. ���������� ��������� � OPC 
	���������� ������ ������������� �� ��� ������ (��������������� ����� �������������)
*********************************************************************/

#include "MemFile.h"
class CVariableMenager
	:public CSingleton<CVariableMenager>
{
public:
	//��� ����������
	enum enVariableType
	{
		VT_NONE,	//��� �� ���������
		VT_SIMPLE,	//������ ����������
		VT_OPC		//���������� ������� � OPC
	};
	//��������� ����������� ����������
	struct sVariable
	{
		enVariableType			Type;		//��� ����������
		CComVariant				Value;		//�������� ����������
		struct sSettings
		{
			//��������� ��������� ��������� � ���������� OPC-����� � OPC-������
			struct sOPC
			{
				wstring	TagName;			// ������� ������
				GUID	guid;				// CLSID �������
				wstring	Computer;			// ��� ���������� � OPC
			}OPC;
		}Settings;
	};

	//�������� ������ ���� ����������
	TStrings GetVariableList();

	//�������� ���������� ��������� � OPC
	void AddOPCVariable(wstring Name, CComVariant Value, wstring TagName, GUID guid, wstring Computer);
	//�������� ������� ����������
	void AddSimpleVariable(wstring Name, CComVariant Value);

	//�������� �������� ����������. ���� ����� ���������� ��� ������������ 
	//�������� �� ���������
	CComVariant GetVariable(wstring Name, CComVariant Default = NULL);
	const CComVariant operator[](wstring Name){return GetVariable(Name);};

	//�������� ��� ����������. 
	CVariableMenager::enVariableType GetVariableType(wstring Name);

	sVariable::sSettings GetVariableSetting(wstring Name);

	//�������� �������� � ����������. ���� ���������� ���� WriteToServer � ���������� 
	//����� ��� OPC, �� ���������� ������ �������� � OPC-�����
	void SetVariable(wstring Name, CComVariant Value, bool WriteToServer = false);

	void RemoveVariable(wstring Name);

	void Serialize(CMemFile& file, BOOL IsLoading);

	bool TestVariableInUse(wstring Name);

protected:
	typedef map<wstring, sVariable> TVariables;	//����� ����������

	//Constructor/Destructor
	CVariableMenager(void){};
	~CVariableMenager(void){};
	DEF_SINGLETON(CVariableMenager);

	//������� ���������� �� OPC ������
	void PostToOPC(sVariable &var);
	void SendToOPC(sVariable &var);
	//����� �������� ���������� �� OPC ������
	static DWORD WINAPI PostToOPCThread(LPVOID);

	TVariables _Variables;			//������ ����������
	CComAutoCriticalSection _CS;	//����������� ������ ��� ������� � ������ �� ������ �������
};

typedef CVariableMenager::sVariable::sSettings TVariableSettings;
typedef CSingletonPtr<CVariableMenager> CVariableMenagerPtr;