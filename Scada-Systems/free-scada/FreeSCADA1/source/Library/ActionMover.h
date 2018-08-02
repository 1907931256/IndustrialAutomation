#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   10:43
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ActionMover.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ActionMover
	����������:	    h
	�����(�):	    ������
    �����(�):       CActionMover
	
	��������:	������ action ������������ ���������� ������ �� �������� 
	���������� (Polyline) � ����������� �� �������� ���������.
*********************************************************************/

#include "action.h"
#include "Object.h"
#include "ObjPolyline.h"

class CActionMover :
	public CAction
{
public:
	//�����������/����������
	CActionMover(CObject* Owner_);
	~CActionMover(void);

	//������� "����������"
	virtual void Update();

	//������� ��������/����������
	virtual void Serialize(CMemFile& file, BOOL IsLoading);

	//�������� �������� ��������� ������ �� ��� ����������� ��������
	virtual bool GetParamValue(wstring Name, CComVariant& Variant);
	//���������� �������� ��������� ������ �� ��� ����������� ��������
	virtual bool SetParamValue(wstring Name, CComVariant Variant);

	//������ ��� �������, ������� ����� �������������� � �������� ����
	void SetPathObject(wstring PathObject);
	//�������� ��� �������, ������� ����� �������������� � �������� ����
	wstring GetPathObject();

protected:
	float			_CurrentPos;//0..1
	wstring			_PathObject;
};
