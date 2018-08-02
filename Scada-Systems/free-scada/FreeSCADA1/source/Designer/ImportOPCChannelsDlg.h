#pragma once
/********************************************************************
	������:	        2005/02/17
	������:	        17.2.2005   12:31
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\OPCVariableDialog.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    OPCVariableDialog
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       CImportOPCChannelsDlg
	
��������:	����� ������� ��� �������� OPC ����������
*********************************************************************/

#include <atlcrack.h>

class CImportOPCChannelsDlg
	: public CDialogImpl<CImportOPCChannelsDlg>
	, public CWinDataExchange<CImportOPCChannelsDlg>
{
public:
	typedef CImportOPCChannelsDlg thisClass;

	enum { IDD = IDD_IMPORT_OPC_CHANNELS };

	CString m_Prefix;		//������� ����������
	CString m_ComputerName;	//��� ����������
	CString m_ServerName;	//��� �������
	GUID	m_ServerGUID;	//UUID �������
	
	CImportOPCChannelsDlg(void) 
		: m_ComputerName("localhost")
		, m_ServerName("")
	{}


	BEGIN_DDX_MAP(thisClass)
		DDX_TEXT(IDC_VARIABLE_PREFIX, m_Prefix)
		DDX_TEXT(IDC_NAME_COMPUTER, m_ComputerName)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_BROWSE_COMPUTER, OnBrowseComputer)
		COMMAND_HANDLER(IDC_NAME_SERVER, CBN_SELCHANGE, OnServerSelchange)
		COMMAND_HANDLER(IDC_NAME_SERVER, CBN_DROPDOWN, OnCbnDropDown)
		COMMAND_HANDLER(IDC_NAME_COMPUTER, EN_CHANGE, OnEnChange)
		COMMAND_HANDLER(IDC_VARIABLE_PREFIX, EN_CHANGE, OnPrefixEnChange)

		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//����� �������
	LRESULT OnServerSelchange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� ������ ��������
	LRESULT OnCbnDropDown(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� ����� ����������, ��������� ����� � Edit
	LRESULT OnBrowseComputer(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//����� ������� ������ ������
	LRESULT OnBrowseChannel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� ����� ���������� ��� ���������� ��� "�������"
	LRESULT OnEnChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� �������� ����������
	LRESULT OnPrefixEnChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//����� ������� ������ ����������
	CString BrowseComputer();
	//���������� ComboBox-� ������� ��������
	void FillListServer();
	//�������� ��������� �� ��� ����
	bool IsSetAll();
	//���������� ��������� ������������ �������� ������� � ����
	void UpdateCtrls();
};
