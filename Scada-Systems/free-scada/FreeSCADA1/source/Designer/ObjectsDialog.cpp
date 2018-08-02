#include "StdAfx.h"
#include ".\objectsdialog.h"
#include "ObjectMenager.h"

LRESULT CObjectsDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DlgResize_Init(true, true, NULL);
	DoDataExchange(DDX_LOAD);
	CenterWindow(GetParent());

	m_List = (CListBox)GetDlgItem(IDC_LIST_OBJECTS);
	m_List.ResetContent();

	CObjectMenagerPtr mng;

	//��������� ������ ���� ���������� � ����� ���������� ���������
	TStrings Names =  mng->GetObjectNames();
	CObject* SelObj = mng->GetSelected();
	wstring SelName = L"";
	if(SelObj != NULL)SelName = SelObj->GetName();
	int i = 0;
	
	//��������� ListBox ������� ��������
	if(!Names.empty())
	{
		for(TStrings::iterator it = Names.begin(); it != Names.end(); it++, i++)
		{
			int item = m_List.AddString(it->c_str());
			//������ ���������� � ListBox-� �������� ��������
			if(wcscmp(SelName.c_str(), it->c_str()) == 0)
				m_List.SetSel(item);
		}
	}

	//�������� ������ ���� �������� �� Listbox-� � ������ �� �����������
	TStrings SelectedNames = mng->GetSelection()->GetObjects();
	if(!SelectedNames.empty())
	{
		for(TStrings::iterator it = SelectedNames.begin(); it != SelectedNames.end(); it++, i++)
		{
			int item = m_List.AddString(it->c_str());
			m_List.SetSel(item);
		}
	}

	return TRUE;
}


LRESULT CObjectsDialog::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return TRUE;
}

LRESULT CObjectsDialog::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_ObjectNames.clear();
	if(wID != IDOK)
	{
		EndDialog(wID);
		return 0;
	}


	TStrings Selected; //������ ���� ��������� ����������

	int count = m_List.GetCount();


	//��������� ������ ��������� ����������
	for(int i =0; i < count; i++)
	{
		if(m_List.GetSel(i))
		{
			wchar_t buffer[0xff];
			m_List.GetText(i, buffer); 
			wstring str(buffer);
			Selected.push_back(str);
		}
	}



	CObjectMenagerPtr mng;
	mng->SelectObject(NULL);

//���� ������ ���� �������� �������, ������ ��� ���������
	if(Selected.size() == 1)
	{
		CObject* obj = mng->FindObject(*Selected.begin());
		if(obj != NULL)
			mng->SelectObject(obj);
	}

//���� ����� ������ �������� - �������� � Selection
	if(Selected.size() > 1)
	{
		for(TStrings::iterator it = Selected.begin(); it != Selected.end(); it++)
		{
			CObject* obj = mng->FindObject(*it);
			if(obj != NULL)
				mng->AddToSelected(obj);
		}
	}

	EndDialog(wID);
	return 0;
}


