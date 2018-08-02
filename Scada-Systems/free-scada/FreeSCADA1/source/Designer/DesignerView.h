// DesignerView.h : interface of the CDesignerView class
//
/////////////////////////////////////////////////////////////////////////////
/********************************************************************
	������:	        2005/02/16
	������:	        16.2.2005   9:13
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\DesignerView.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    DesignerView
	����������:	    h
	�����(�):	    ������
    �����(�):       CDesignerView
	
��������:	����� CDesignerView ��������� ����������� ���� ����������� ���������
*********************************************************************/

#pragma once
#include <atlcrack.h>
#include "Doc.h"
#include ".\Primitives\Select.h"

	class CDesignerView 
	: public CWindowImpl<CDesignerView>
	, public DVF::CBaseView
{
protected:
	CBitmap         _Background; //Bitmap ���  �����������
	CBitmap			_ViewportBuffer; //��������������� Bitmap ��� ��������� ����������
	Primitives::CSelect*		_Select; //������ ��� ������ ����������

public:
	CBitmap			m_Viewport; //Bitmap ��� ���� � ���� ����������� �� ���� �������
	
	bool			m_IsLimit; //���������� �� ������� ���������
	sVector			m_WorkArea;	//
	bool			m_IsBGImage; //����� �� ��� � ���� ����������� 
	bool			m_StrchBGImage; //����������� �� ����������� �� �������� ������� ���������
	::CImage 		m_BGImage; //����������� ��� ����

	sRGB			m_BackGrdColor; //������� ��� ����
				

	DECLARE_WND_CLASS(NULL)

	CDesignerView() 
		: m_IsLimit(false)
		, m_WorkArea(0,0)
		, m_IsBGImage(false)
		, m_StrchBGImage(false)
		, m_BackGrdColor(cBackgroundColor)
	{
		_Select  =	new Primitives::CSelect();
		CObjectMenagerPtr mng;
		mng->SetSelection(_Select);
	}


	BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnUpdate();

	BEGIN_MSG_MAP(CDesignerView)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MSG_WM_HSCROLL(OnHScroll)
		MSG_WM_VSCROLL(OnVScroll)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	
//����������� ���������
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	//�������� ������������� ���������� ������������� ���� � ObjectMenager-�
	bool IsUniquePrimitive(enCreatePrimitive Primitive);
	//������������ Bitmap-� ��� ���� � ���� ����������� �� ���� �������
	void UpdateBackGround();
	//������������ Bitmap-� ��� �����������
	void CreateBackground();

	LRESULT OnHScroll(int code, short pos, HWND hwndCtl);
	LRESULT OnVScroll(int code, short pos, HWND hwndCtl);
};
