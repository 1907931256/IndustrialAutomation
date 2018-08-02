#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   17:46
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives\ManipulatorSizeLeft.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives
	��� �����:	    ManipulatorSizeLeft
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       CManipulatorSizeLeft
	
��������:	����� ������������ ��� ��������� ������ ������� (��� ������������ 
			������� � ������� ���� �� ����� �������)
*********************************************************************/

#include "manipulator.h"

namespace Primitives
{

	class CManipulatorSizeLeft :
		public CManipulator
	{
	public:
		CManipulatorSizeLeft(CObject* Obj);
		virtual ~CManipulatorSizeLeft(void);
		//��������� ������������
		virtual void Draw(HDC dc);
		//����������� ���������
		virtual BOOL OnMouseLButtonDown(sVector Point);
		virtual BOOL OnMouseLButtonUp(sVector Point);
		virtual BOOL OnMouseMove(sVector Point);
		//�������� �������� �� point �� ������
		virtual bool HitTest(sVector point);
		//���������� ����������� ������ �������
		virtual void SetMinSize(sVector MinSize){ _MinSize = MinSize; }
		//�������� ����������� ������ �������
		virtual sVector GetMinSize(){ return _MinSize; }

	protected:
		sVector _BrickSize;
		sVector _MinSize;
		CBrush	_Brush;
		CPen	_Pen;
		sVector	_LastPosition;
		bool	_MLButtonDown;
	};

}