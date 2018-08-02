#pragma once
/********************************************************************
	������:	        2005/02/08
	������:	        8.2.2005   16:08
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives\Image.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Primitives
	��� �����:	    Image
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       CImage
	
��������:	����� CImage ������������ ��� ������ �����������
*********************************************************************/

#include "../PropertyWindow/ObjectPropertyWindow.h"
#include "BaseObject.h"

namespace Primitives
{
	class CImage
		:public CObjImage
		,public CBaseObject<CImage>
	{
	public:
		CImage(void);
		virtual ~CImage(void);

		//����������� ���������
		virtual BOOL OnMouseLButtonDown(sVector Point);
		virtual BOOL OnMouseRButtonDown(sVector Point);
		virtual BOOL OnMouseLButtonUp(sVector Point);
		virtual BOOL OnMouseMove(sVector Point);
		virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam);
		virtual void OnSetFocus();
		virtual void OnLostFocus();
		virtual BOOL OnMouseLButtonDblClk(sVector Point);
		//���������� ��������� ������
		virtual void OnEdit();
		//�������� �������� �� point �� ������
		virtual bool HitTest(sVector point);
		//��������� ��������
		virtual void Draw(HDC dc_); 
		//�������� �������� �� ������
		virtual void SetImage(wstring Name);
		//����������-�������� �������
		virtual void Serialize(CMemFile& file, BOOL IsLoading = 1);
		//�������� �������� ��������� � ���������� Category � ��������� Name
		virtual bool GetParamValue(enCatID Category, wstring Name, sParam& Param);
		//���������� �������� ��������� � ���������� Category � ��������� Name
		virtual bool SetParamValue(enCatID Category, wstring Name, sParam Param);

	protected:


	};
}
