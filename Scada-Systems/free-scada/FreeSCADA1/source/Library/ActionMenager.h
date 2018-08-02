#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   11:04
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ActionMenager.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ActionMenager
	����������:	    h
	�����(�):	    �������, ������
    �����(�):       CActionMenager
	
��������:	������ ���� ������������ ����� �������� �������(��������). 
���������� �� ������� Singleton. 
���������: ����������, ��������/��������������, ����������, �������� � �.�.

  ������ ������ ����� ��������� ������� ������ ��������, �� ��� �������� 
������ ���� ������ �����. ����������� � ���� ���� <������,������ ��������>.
*********************************************************************/

#include "Action.h"
class CArchiveManager;

class CActionMenager
	: public CSingleton<CActionMenager>
{
public:
	typedef list<CAction*>			TActions;
	typedef map<wstring, TActions>	TMapObjActions;
	typedef list<enActionType>		TActionTypes;

	//�������� �������� � �������
	CAction * CActionMenager::AddAction(wstring Object, enActionType Type);
	//����� �������� ��������� ���� � �������
	CAction * FindAction(wstring Object,const wstring &name);
	CAction* FindAction(const wstring &name);

	//������� �������� ��������� ���� � �������
	BOOL RemoveAction(wstring Object, const wstring & name);
	//������� ��� ��������
	BOOL RemoveAll();
	//������� ��� �������� � ��������� �������
	BOOL RemoveObject(wstring Object);
	
	//�������� ��������� ��������
	BOOL ModifyAction(wstring Object, CAction* Action);

	//�������� ������ ���� �������� � ��������� �������
	BOOL GetAllActions(wstring Object, TActions& Actions);
	TActions GetAllActions(wstring Object, enActionType Type);
	//�������� ��� �������� (����� OnUpdate ��� ������� ��������)
	void UpdateActions();

	//��������/����������
	virtual void Serialize(CMemFile& file, BOOL IsLoading=TRUE);

protected:
	CActionMenager(void);
	~CActionMenager(void);
	DEF_SINGLETON(CActionMenager);
	CArchiveManager *_ArcManager;
	TMapObjActions _Actions;
};

typedef CSingletonPtr<CActionMenager> CActionMenagerPtr;