#pragma once
/********************************************************************
	������:	        2005/02/17
	������:	        17.2.2005   17:32
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\SimpleVariableDialog.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    SimpleVariableDialog
	����������:	    h
	�����(�):	    �������
    �����(�):       CSimpleVariableDialog
	
��������:	������ ��� ��������� ������� ����������
*********************************************************************/

#include "resource.h"

class CSimpleVariableDialog
	: public CDialogImpl<CSimpleVariableDialog>
	, public CDialogResize<CSimpleVariableDialog>
	, public CWinDataExchange<CSimpleVariableDialog>
{
typedef CSimpleVariableDialog thisClass;
public:
	enum { IDD = IDD_SIMLPE_VARIABLE };

	CString m_Name; //��� ���������
	CString	m_Type;	//��� ����������
	CString m_Value; //�������� ����������


	BEGIN_DDX_MAP(thisClass)
		DDX_TEXT(IDC_VALUE_SIMPLE_VARIABLE, m_Value)
		DDX_TEXT(IDC_NAME_SIMPLE_VARIABLE, m_Name)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_CODE_HANDLER(CBN_SELCHANGE, OnCbnSelchange)
		COMMAND_RANGE_CODE_HANDLER(IDC_VALUE_SIMPLE_VARIABLE, IDC_NAME_SIMPLE_VARIABLE, EN_CHANGE, OnEnChange)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CDialogResize<thisClass>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(thisClass)
		DLGRESIZE_CONTROL(IDC_NAME_SIMPLE_VARIABLE, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_VALUE_SIMPLE_VARIABLE, DLSZ_SIZE_X)
	END_DLGRESIZE_MAP()

	CSimpleVariableDialog(): m_Name(""), m_Value("0"), m_Type("Float")
	{

	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEnChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//��������, ��� �� ��������� �����������
	bool IsSetAll();
protected:
	
};
