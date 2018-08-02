#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   16:26
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives\ManipulatorRotate.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives
	��� �����:	    ManipulatorRotate
	����������:	    h
	�����(�):	    �������
    �����(�):       CManipulatorRotate
	
��������:	����� ������������ ��� �������� �������
*********************************************************************/

#include "manipulator.h"
namespace Primitives
{

class CManipulatorRotate :
	public CManipulator
{
public:
	CManipulatorRotate(CObject* Obj);
	~CManipulatorRotate(void);

	//��������� ������������
	virtual void Draw(HDC dc);
	//����������� ���������
	virtual BOOL OnMouseLButtonDown(sVector Point);
	virtual BOOL OnMouseLButtonUp(sVector Point);
	virtual BOOL OnMouseMove(sVector Point);
	//�������, �������� �� point � ������� �������
	virtual bool HitTest(sVector point);

protected:
	CBrush	_Brush;
	CPen	_Pen;
	sVector	_LastPosition;
	bool	_MLButtonDown;
};

}
