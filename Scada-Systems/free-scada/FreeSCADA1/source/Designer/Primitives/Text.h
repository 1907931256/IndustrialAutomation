#pragma once
/********************************************************************
	������:	        2005/02/09
	������:	        9.2.2005   13:54
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives\Text.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives
	��� �����:	    Text
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       CText
	
��������:	����� ��������� � ��������� ������ ������������ �����
*********************************************************************/

#include "BaseObject.h"
namespace Primitives
{
	class CText
		:public CObjText
		,public CBaseObject<CText>
	{
	public:
		CText(void);
		~CText(void);
		//����������� ���������
		virtual BOOL OnMouseLButtonDown(sVector Point);
		virtual BOOL OnMouseRButtonDown(sVector Point);
		virtual BOOL OnMouseLButtonDblClk(sVector Point);
		virtual BOOL OnMouseLButtonUp(sVector Point);
		virtual BOOL OnMouseMove(sVector Point);
		virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam);
		virtual void OnSetFocus();
		virtual void OnLostFocus();
		//���������� ��������� �������
		virtual void OnEdit();
		//��������� ������
		virtual void Draw(HDC dc);
		//�������� �������� �� ������ point �� ������
		virtual bool HitTest(sVector point);
		//�������� �������� ���������
		virtual bool GetParamValue(enCatID Category, wstring Name, sParam& Param);
		//���������� �������� ���������
		virtual bool SetParamValue(enCatID Category, wstring Name, sParam Param);		
		//�������� ��������� �������� ���������
		virtual wstring StrFromCatID(enCatID id);
		//�������� ������������ ������ � ���� ������
		wstring GetAlignAsText();
		//���������� ������������ ������ ����� ������ 
		void SetAlignAsText(wstring Align);
	};
}