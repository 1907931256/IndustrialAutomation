#pragma once
/********************************************************************
	������:	        2005/02/09
	������:	        9.2.2005   10:19
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives\ManipulatorVertex.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives
	��� �����:	    ManipulatorVertex
	����������:	    h
	�����(�):	    �������
    �����(�):       CManipulatorVertex
	
��������:	����� ������������ ��� ���������� � ����������� ������ ���������
			� ������� ����
*********************************************************************/

#include "manipulator.h"

namespace Primitives
{

	class CManipulatorVertex :
		public CManipulator
	{
	public:
		CManipulatorVertex(CObject* Obj);
		~CManipulatorVertex(void);
		//�������� ������������
		virtual void Draw(HDC dc);
		//����������� ���������
		virtual BOOL OnMouseLButtonDown(sVector Point);
		virtual BOOL OnMouseLButtonUp(sVector Point);
		virtual BOOL OnMouseMove(sVector Point);
		virtual BOOL OnMouseRButtonDown(sVector Point);
		//�������� �������� �� ������ point �� ���� �� ������ ��� �����
		virtual bool HitTest(sVector point);
		//�������� �������� �� ������ point �� ������
		bool HitLine(sVector point, vector< sVector >::iterator& vertex);

	protected:
		sVector _BrickSize;
		CBrush	_Brush;
		CPen	_Pen;
		sVector	_LastPosition;
		bool	_MLButtonDown;
		vector< sVector >::iterator _CurrentVertex;//��������, ����������� �� 
													//������� �������
	};
 
}