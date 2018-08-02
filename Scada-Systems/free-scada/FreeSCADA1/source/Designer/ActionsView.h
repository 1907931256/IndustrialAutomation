#pragma once
/********************************************************************
	������:	        2005/02/09
	������:	        9.2.2005   14:20
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\ActionsView.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    ActionsView
	����������:	    h
	�����(�):	    �������
    �����(�):		CPropertyList, CActionsView
	
��������:	����� CPropertyList ��������� ���� �������, 
			����� CActionsView ��������� ���� ����������� ������������� 
			���������� ��������, �������� ���������� �������
*********************************************************************/

#include "resource.h"


class CPropertyList
	: public CPropertyListImpl<CPropertyList>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_PropertyList"), GetWndClassName())

	typedef CPropertyListImpl<CPropertyList> baseClass;
	BEGIN_MSG_MAP(CPropertyListView)
		CHAIN_MSG_MAP(baseClass)
	//	FORWARD_NOTIFICATIONS()
	//	DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	
};

class CActionsView
: public CWindowImpl<CActionsView>
{
public:
	typedef CWindowImpl<CActionsView> baseClass ;
	BEGIN_MSG_MAP(CActionsView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_POSTCREATE, OnPostCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		COMMAND_ID_HANDLER(ID_ACTION_MOVER, OnAddActionMover)
		COMMAND_ID_HANDLER(ID_ACTION_SIZER, OnAddActionSizer)
		COMMAND_ID_HANDLER(ID_ACTION_ROTATE, OnAddActionRotate)
		COMMAND_ID_HANDLER(ID_ACTION_VISUAL, OnAddActionVisual)
		COMMAND_ID_HANDLER(ID_ACTION_COLOR, OnAddActionColor)
		COMMAND_ID_HANDLER(ID_ACTION_PLAY_SOUND, OnAddActionPlaySound)
		COMMAND_ID_HANDLER(ID_ACTION_CHANGE_IMAGE, OnAddActionChangeImage)
		COMMAND_ID_HANDLER(ID_ACTION_CURVE, OnAddActionCurve)
		COMMAND_ID_HANDLER(ID_DEL_ACTION, OnDeleteAction)
		NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnToolbarDropDown)
		NOTIFY_CODE_HANDLER(PIN_ITEMCHANGED, OnItemChanged) 
		//CHAIN_MSG_MAP_MEMBER(m_Prop)
		REFLECT_NOTIFICATIONS()
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP();
	CActionsView();

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPostCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//�������������� ���� ������ ��������
	LRESULT OnToolbarDropDown(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);
	//���������� �������� �����������
	LRESULT OnAddActionMover(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� �������� ��������� ��������
	LRESULT OnAddActionSizer(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� �������� ��������
	LRESULT OnAddActionRotate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� �������� ��������� ���������
	LRESULT OnAddActionVisual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� �������� ��������� �����
	LRESULT OnAddActionColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAddActionPlaySound(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAddActionChangeImage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAddActionCurve(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	//�������� ��������
	LRESULT OnDeleteAction(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� ����� ���������� ������
	LRESULT OnItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& bHandled);

	void SetObject(Primitives::CBase* obj);
	//���������� � ���� ���������� ��������, ������� ���� � �������
	void AddActionsToList();
	//���������� �������� � ���� ����������
	void AddToList(CAction* Action);
	//���������� �������� ���������� ���������
	void SaveValue();
	
	//�������� �������� ������ � ���� ������������� ��������
	float FloatFromProp(HPROPERTY prop);
	//�������� �������� ������ � ���� ������
	wstring StringFromProp(HPROPERTY prop);
	
	
	//������������� ����� ���� ������ �������� �������������� ��� �� ��������������
	void SetMenuItemEnabled(enActionType Type, bool Enabled);
	//�������� ID ������ ���� ������ �������� �� ���� ��������
	UINT GetIDFromType(enActionType Type);
	//�������� ��������� �������� �������� �� ���� ��������
	wstring GetNameFromType(enActionType Type);
	
	CMenu m_ActionsMenu;
	Primitives::CBase* m_Object; //��������� ������
	CPropertyList m_Prop; //���� ���������� ��������
	CToolBarXPCtrl m_Toolbar;
	TActionsMap	m_ActionsMap; //����� ��� ��������-������ �������� sCtrlParam(��������-�������)

};
