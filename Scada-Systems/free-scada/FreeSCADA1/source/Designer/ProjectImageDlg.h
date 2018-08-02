#pragma once
/********************************************************************
	������:	        2005/02/17
	������:	        17.2.2005   12:56
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\ProjectImageDlg.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    ProjectImageDlg
	����������:	    h
	�����(�):	    ������
    �����(�):       CProjectImageDlg
	
��������:	������ ��� ������ � ������������� �������
*********************************************************************/

class CProjectImageDlg
	: public CDialogImpl<CProjectImageDlg>
	, public CDialogResize<CProjectImageDlg>
	, public CWinDataExchange<CProjectImageDlg>
{
	typedef CProjectImageDlg thisClass;

	CArchiveManager* _Menager;
public:
	enum { IDD = IDD_PROJECT_IMAGES };

	
	UINT m_Width; //������ ���������� �����������
	UINT m_Height;	//������ ���������� �����������
	CBitmap m_Preview; //Bitmap ��������� �����������

	CProjectImageDlg(CArchiveManager *mng)
		: _Menager(mng)
		, m_Width(0)
		, m_Height(0){};

	BEGIN_DDX_MAP(thisClass)
		DDX_UINT(IDC_WIDTH, m_Width)
		DDX_UINT(IDC_HEIGHT, m_Height)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_HANDLER(IDC_LOAD_FROM_FILE, BN_CLICKED, OnBnClickedLoadFromFile)
		COMMAND_HANDLER(IDC_RENAME, BN_CLICKED, OnBnClickedRename)
		COMMAND_HANDLER(IDC_IMAGE_LIST, LBN_SELCHANGE, OnLbnSelchangeImageList)
		COMMAND_HANDLER(IDC_DELETE, BN_CLICKED, OnBnClickedDelete)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP(CDialogResize<thisClass>)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(thisClass)

		DLGRESIZE_CONTROL(IDC_IMAGE_LIST, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_PREVIEW, DLSZ_MOVE_X)

		DLGRESIZE_CONTROL(IDC_LOAD_FROM_FILE,	DLSZ_MOVE_Y|DLSZ_MOVE_X|DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_RENAME,			DLSZ_MOVE_Y|DLSZ_MOVE_X|DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_DELETE,			DLSZ_MOVE_Y|DLSZ_MOVE_X|DLSZ_SIZE_X)

		DLGRESIZE_CONTROL(IDC_GROUP,			DLSZ_MOVE_X|DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_STATIC_W,			DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_STATIC_H,			DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_WIDTH,			DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_HEIGHT,			DLSZ_MOVE_X)

		DLGRESIZE_CONTROL(IDOK,					DLSZ_MOVE_Y|DLSZ_MOVE_X)

	END_DLGRESIZE_MAP()


	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	
	//���������� ������ ������� ����������� ������� ��� ���� � �������
	void FillList();

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�������� ����������� �� �����
	LRESULT OnBnClickedLoadFromFile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�������������� ����������� ������������ � ������
	LRESULT OnBnClickedRename(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� ����������� � ListBox-�, ���������� ��������� �����������
	LRESULT OnLbnSelchangeImageList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�������� �����������
	LRESULT OnBnClickedDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//��������� Bitmap-�
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
