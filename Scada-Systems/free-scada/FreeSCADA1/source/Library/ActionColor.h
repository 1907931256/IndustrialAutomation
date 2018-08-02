#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   10:56
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ActionColor.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ActionColor
	����������:	    h
	�����(�):	    ������
    �����(�):       CActionColor
	
	��������:	������ action �������� ���� �������  � ����������� 
	�� �������� ���������. ���� ������ ���������� �� ���������� � ���������.
*********************************************************************/


#include "action.h"
#include "Object.h"


class CActionColor
	: public CAction
{
public:
	//�����������/����������
	CActionColor(CObject* Owner_);
	~CActionColor(void);

	//������� "����������"
	virtual void Update();

	//���������� ��������� �������� �����
	inline void SetStartColor(sRGB Color){_StartColor = Color;};
	//�������� ��������� �������� �����
	inline sRGB GetStartColor(){return _StartColor;};
	
	//���������� �������� �������� �����
	inline void SetEndColor(sRGB Color){_EndColor = Color;};
	//�������� �������� �������� �����
	inline sRGB GetEndColor(){return _EndColor;};
	
	//������� ��������/����������
	virtual void Serialize(CMemFile& file, BOOL IsLoading = TRUE);

	//�������� �������� ��������� ������ �� ��� ����������� ��������
	virtual bool GetParamValue(wstring Name, CComVariant& Variant);
	//���������� �������� ��������� ������ �� ��� ����������� ��������
	virtual bool SetParamValue(wstring Name, CComVariant Variant);

protected:
	sRGB _StartColor;
	sRGB _EndColor;
};
