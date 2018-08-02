#pragma once

/********************************************************************
	������:	        2005/02/17
	������:	        17.2.2005   16:09
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\SelectChannelDialog.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    SelectChannelDialog
	����������:	    h
	�����(�):	    ������
    �����(�):       CSelectChannelDialog, sServerInfo
	
��������:	
*********************************************************************/

struct sServerInfo
{
	CComBSTR	m_Computer;
	CLSID		m_ServerCLSID;
};

class CSelectChannelDialog
	: public CDialogImpl<CSelectChannelDialog>
	, public CDialogResize<CSelectChannelDialog>
	, public CWinDataExchange<CSelectChannelDialog>
{
public:
	typedef CSelectChannelDialog thisClass;

	enum { IDD = IDD_SELECT_CHANNEL };

	CTreeViewCtrl m_Tree;
	CString m_Computer; //��� ����������
	CString m_Channel;	//��� ����
	CLSID	m_OPCServerCLSID; //CLSID �������

	BEGIN_DDX_MAP(thisClass)

	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)

		NOTIFY_HANDLER(IDC_TREE_CHANNEL, TVN_SELCHANGED, OnTvnSelChanged)
		
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CDialogResize<thisClass>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(thisClass)
		//	DLGRESIZE_CONTROL(IDC_VARIABLE_LIST, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		//	DLGRESIZE_CONTROL(IDC_ADD_VAR, DLSZ_MOVE_Y)
		//	DLGRESIZE_CONTROL(IDC_DEL_VAR, DLSZ_MOVE_Y)
		//	DLGRESIZE_CONTROL(IDC_CHANGE_VAR, DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()

	CSelectChannelDialog(void) : m_Channel(""){}
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTvnSelChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	/// Fill tags tree for HIERARCHIAL OPC
	void FillTree(HTREEITEM root, CComPtr<IOPCBrowseServerAddressSpace> sas);
	/// Fill tags tree for FLAT OPC
	void FillTreeFlat(HTREEITEM root, CComPtr<IOPCBrowseServerAddressSpace> sas);
	//������� ������� ������ �� ��������� ���������� 
	HRESULT PingRemoteServer(CString Computer, CLSID ServerOPOC, DWORD nTimeout);
};
