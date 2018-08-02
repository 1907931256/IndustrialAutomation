#pragma once

/********************************************************************
	������:	        2005/02/17
	������:	        17.2.2005   12:00
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\PropertyWindow\ObjectPropertyWindow.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\PropertyWindow
	��� �����:	    ObjectPropertyWindow
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       CObjectPropertyWindow
	
��������:	����� ����������� ���� � ����������, ���������� � ���� ���� ���������� �
			���� ��������			
*********************************************************************/


#include "PropertyListView.h"
#include "../ActionsView.h"
#include "../Primitives/BaseObject.h"

class CObjectPropertyWindow
	: public CTabbedFrameImpl<CObjectPropertyWindow, CDotNetTabCtrl<CTabViewTabItem>, dockwins::CTitleDockingWindowImpl< CTabbedDockingWindow,CWindow,dockwins::COutlookLikeTitleDockingWindowTraits> >
	, public DVF::CBaseView
{
	typedef CTabbedFrameImpl<CObjectPropertyWindow, CDotNetTabCtrl<CTabViewTabItem>, dockwins::CTitleDockingWindowImpl< CTabbedDockingWindow,CWindow,dockwins::COutlookLikeTitleDockingWindowTraits> > baseClass;
	typedef CObjectPropertyWindow thisClass;

public:
	DECLARE_WND_CLASS_EX(_T("Atributes Window"), CS_DBLCLKS, COLOR_APPWORKSPACE)

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_POSTCREATE, OnPostCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_UPDATEVIEW, OnUpdateView)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		CHAIN_MSG_MAP(baseClass)
		REFLECT_NOTIFICATIONS()
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPostCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnUpdateView(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void UpdateBarsPosition(RECT& /*rect*/, BOOL /*bResizeBars = TRUE*/){};
	
	//��������� ���������, ��� �������� ����� ������������
	void SetObject(Primitives::CBase* obj)
	{	//��������� � ���� ����������
		_Properties.SetObject(obj);

		//��������� � ���� ��������
		_Actions.SetObject(obj);
	}

	//���������� �������� � ���� ����������
	void RefreshProperty()
	{
		_Properties.RefreshProrerty();
	}

	inline void SaveObjectValue()
	{
		_Properties.SaveObjectValue(TRUE);
	}

	inline static thisClass* Instance(bool bReflectNotifications = true){if(!_Self) _Self = new thisClass(bReflectNotifications);_RefCount++; return _Self;};
	inline void FreeInst(){_RefCount--; if(!_RefCount){delete this; _Self=NULL;}};
protected:
	static thisClass* _Self;	//��������� "�� ����"
	static DWORD _RefCount;

	CPropertyListView _Properties; //���� ������
	CActionsView  _Actions;

	CObjectPropertyWindow(bool bReflectNotifications = true):baseClass(bReflectNotifications){};
	~CObjectPropertyWindow(){};
};
