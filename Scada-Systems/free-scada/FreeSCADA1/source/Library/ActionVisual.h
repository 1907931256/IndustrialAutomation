#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   10:24
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ActionVisual.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ActionVisual
	����������:	    h
	�����(�):	    �������
    �����(�):       CActionVisual
	
��������:	������ action �������� ���� ��������� ������� � ����������� ��
�������� ���������.
*********************************************************************/


#include "action.h"
#include "Object.h"

class CActionVisual
	: public CAction
{
public:
	//�����������/����������
	CActionVisual(CObject* Owner_);
	~CActionVisual(void);

	//������� "����������"
	virtual void Update();
};
