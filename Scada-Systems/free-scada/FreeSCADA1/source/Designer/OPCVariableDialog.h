#pragma once
/********************************************************************
	������:	        2005/02/17
	������:	        17.2.2005   12:31
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\OPCVariableDialog.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    OPCVariableDialog
	����������:	    h
	�����(�):	    ������, �������
    �����(�):       COPCVariableDialog
	
��������:	����� ������� ��� �������� OPC ����������
*********************************************************************/

#include <atlcrack.h>

class COPCVariableDialog
	: public CDialogImpl<COPCVariableDialog>
	, public CDialogResize<COPCVariableDialog>
	, public CWinDataExchange<COPCVariableDialog>

	
{
public:
	typedef COPCVariableDialog thisClass;

	enum { IDD = IDD_OPC_VARIABLE };

	CString m_Name;			//��� ����������
	CString	m_Type;			//��� ����������
	CString m_ComputerName;	//��� ����������
	CString m_ServerName;	//��� �������
	CString m_ChannelName;	//��� ������
	GUID	m_ServerGUID;	//UUID �������
	
	COPCVariableDialog(void) 
		: m_ComputerName("localhost")
		, m_ServerName("")
	{}


	BEGIN_DDX_MAP(thisClass)
		DDX_TEXT(IDC_NAME_OPC_VARIABLE, m_Name)
		DDX_TEXT(IDC_NAME_COMPUTER, m_ComputerName)
		DDX_TEXT(IDC_NAME_CHANNEL, m_ChannelName)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MSG_WM_GETMINMAXINFO(OnGetMinMaxInfo)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_BROWSE_COMPUTER, OnBrowseComputer)
		COMMAND_ID_HANDLER(IDC_BROWSE_CHANNEL, OnBrowseChannel)
		COMMAND_HANDLER(IDC_NAME_SERVER, CBN_SELCHANGE, OnServerSelchange)
		COMMAND_HANDLER(IDC_TYPE_VARIABLE, CBN_SELCHANGE, OnTypeSelchange)
		COMMAND_HANDLER(IDC_NAME_SERVER, CBN_DROPDOWN, OnCbnDropDown)
		COMMAND_HANDLER(IDC_NAME_COMPUTER, EN_CHANGE, OnEnChange)
		COMMAND_HANDLER(IDC_NAME_OPC_VARIABLE, EN_CHANGE, OnNameEnChange)

		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CDialogResize<thisClass>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(thisClass)
		DLGRESIZE_CONTROL(IDC_NAME_OPC_VARIABLE, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_TYPE_VARIABLE, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_GROUP, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_NAME_COMPUTER, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_NAME_SERVER, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_NAME_CHANNEL, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_BROWSE_COMPUTER, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_BROWSE_CHANNEL, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X|DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X|DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//����� �������
	LRESULT OnServerSelchange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//����� ���� ����������
	LRESULT OnTypeSelchange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//���������� ������ ��������
	LRESULT OnCbnDropDown(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� ����� ����������, ��������� ����� � Edit
	LRESULT OnBrowseComputer(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//����� ������� ������ ������
	LRESULT OnBrowseChannel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� ����� ���������� ��� ���������� ��� "�������"
	LRESULT OnEnChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� �������� ����������
	LRESULT OnNameEnChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//����� ������� ������ ����������
	CString BrowseComputer();
	//���������� ComboBox-� ������� ��������
	void FillListServer();
	//�������� ��������� �� ��� ���� ��� ��� ����������
	bool IsSetAll();
	//���������� ��������� ������������ �������� ������� � ����
	void UpdateCtrls();

	LRESULT OnBnClickedBrowseChannel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
};
