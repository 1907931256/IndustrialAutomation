#pragma once
#include "../PropertyWindow/ObjectPropertyWindow.h"
#include "BaseObject.h"

namespace Primitives
{
	class CEllipse
		:public CObjEllipse
		,public CBaseObject<CEllipse>
	{
	public:
		CEllipse(void);
		virtual ~CEllipse(void);
		
		//����������� ���������
		virtual BOOL OnMouseLButtonDown(sVector Point);
		virtual BOOL OnMouseRButtonDown(sVector Point);
		virtual BOOL OnMouseLButtonDblClk(sVector Point);
		virtual BOOL OnMouseLButtonUp(sVector Point);
		virtual BOOL OnMouseMove(sVector Point);
		virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam);
		virtual void OnSetFocus();
		virtual void OnLostFocus();
		virtual void OnEdit();
		//��������� �������
		virtual void Draw(HDC dc);
		//��������, �������� �� point �� ������
		virtual bool HitTest(sVector point);
		//�������� �������� ��������� � ���������� Category � ��������� Name
		virtual bool GetParamValue(enCatID Category, wstring Name, sParam& Param);
		//���������� �������� ��������� � ���������� Category � ��������� Name
		virtual bool SetParamValue(enCatID Category, wstring Name, sParam Param);
		
	protected:


	};
}
