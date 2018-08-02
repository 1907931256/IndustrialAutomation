#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   17:21
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives\ManipulatorSizeBottom.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives
	��� �����:	    ManipulatorSizeBottom
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       CManipulatorSizeBottom
	
��������:	����� ������������ ��� ��������� ������� ������� (������������ ��
			������ �������)
*********************************************************************/

#include "manipulator.h"

namespace Primitives
{

class CManipulatorSizeBottom :
	public CManipulator
{
public:
	CManipulatorSizeBottom(CObject* Obj);
	virtual ~CManipulatorSizeBottom(void);
	//��������� ������������
	virtual void Draw(HDC dc);
	//����������� ���������
	virtual BOOL OnMouseLButtonDown(sVector Point);
	virtual BOOL OnMouseLButtonUp(sVector Point);
	virtual BOOL OnMouseMove(sVector Point);
	//������� �������� �� point �� ������
	virtual bool HitTest(sVector point);
	//������ ����������� ������ �������
	virtual void SetMinSize(sVector MinSize){ _MinSize = MinSize; }
	//�������� ����������� ������ �������
	virtual sVector GetMinSize(){ return _MinSize; }

protected:
	sVector _BrickSize; //������ ���������� �� ������� ������������� ������
	CBrush	_Brush;
	CPen	_Pen;
	sVector	_LastPosition;
	bool	_MLButtonDown;
	sVector	_MinSize;	//����������� ������ ������� ������� ����������� ��������
};

}