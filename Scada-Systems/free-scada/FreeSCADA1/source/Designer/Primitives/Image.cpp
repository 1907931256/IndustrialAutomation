#include "StdAfx.h"
#include "../MainFrm.h"
#include "BaseObject.h"
#include ".\image.h"

namespace Primitives
{
	CImage::CImage(void)
	{
		//��������� ����� ���������-������ sCtrlParam(���-��� ��������)
		TCtrlParamList Visual;
		TCategoryMap::iterator it = _Categories.find(CAT_APPEARANCE);
		if(it != _Categories.end())
		{			
			Visual = it->second;
		}
		
		Visual.push_back(sCtrlParam (CT_IMAGES, L"Image"));
		Visual.push_back(sCtrlParam(CT_FLAG, L"Border"));
		Visual.push_back(sCtrlParam(CT_COLOR, L"Border color"));
		Visual.push_back(sCtrlParam(CT_INT, L"Border thickness"));
		Visual.push_back(sCtrlParam(CT_FLAG, L"Auto size"));
		Visual.sort(sCompareName());

		_Categories[CAT_APPEARANCE] = Visual;

		
	}

	CImage::~CImage(void)
	{
	}

	//��������� ��������
	void CImage::Draw(HDC dc_) 
	{
		const bool Visible = IsVisible();
		//� ��������� �������� ������ �������
		SetVisible(true);

		CObjImage::Draw(dc_);
		for_each(_Manipulators.begin(),_Manipulators.end(), bind2nd(mem_fun(&CObject::Draw), dc_));

		//��������������� ��������� ��������
		SetVisible(Visible);
	}

	//���������� ��������� �������� ������
	void CImage::OnSetFocus()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		//���� ������� � �������� ���������� ��������� �������
		prop->SetObject(this);
		prop->FreeInst();
		CObjImage::OnSetFocus();
		CBaseObject<CImage>::OnSetFocus();
	}

	//���������� ������ �������� ������
	void CImage::OnLostFocus()
	{
		CObjImage::OnLostFocus();
		CBaseObject<CImage>::OnLostFocus();
	}

	
	//���������� ��������� �������
	void CImage::OnEdit()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		prop->RefreshProperty();
		prop->FreeInst();
		return CObjImage::OnEdit();
	}

	//���������� �������� ������� ������ ����
	BOOL CImage::OnMouseLButtonDblClk(sVector Point)
	{
		return CObjImage::OnMouseLButtonDblClk(Point);
	}
	
	//���������� �������������� �������
	void CImage::Serialize(CMemFile& file, BOOL IsLoading)
	{
		CObjImage::Serialize(file, IsLoading);
		if(IsLoading)
		{
			wstring name = GetImageName();
			SetImage(name);
		}
	}


	//�������� ��������
	void CImage::SetImage(wstring Name)
	{
		if(!g_MainFrame)return;

		wstring FileName = g_MainFrame->m_Doc.m_Archive.GetSpecialFolder(CArchiveManager::SF_IMAGES) + L"\\" + Name;
		if(g_MainFrame->m_Doc.m_Archive.IsFileExists(FileName))
		{
			CMemFile* memfile;
			g_MainFrame->m_Doc.m_Archive.OpenMemFile(FileName, &memfile);
			::CImage image;
			image.Load(*memfile);
			LoadImage(image);
			SetImageName(Name);
			g_MainFrame->m_View.RedrawWindow(); 
		}
	}

	//�������� �������� ��������� � ���������� Category � ��������� Name
	bool CImage::GetParamValue(enCatID Category, wstring Name, sParam& Param)
	{
		BEGIN_GET_PROP_MAP(Category, Name, Param)
			GET_PROP_STRING(CAT_APPEARANCE, L"Image", GetImageName().c_str())
			GET_PROP_BOOL(CAT_APPEARANCE, L"Border", IsDrawBorder())
			GET_PROP_RGB(CAT_APPEARANCE, L"Border color", GetBorderColor())
			GET_PROP_INT(CAT_APPEARANCE, L"Border thickness", GetBorderWidth())
			GET_PROP_BOOL(CAT_APPEARANCE, L"Auto size", GetStretchImage())
		END_GET_PROP_MAP()
		return CBaseObject<CImage>::GetParamValue(Category, Name, Param);	
	}

	//���������� �������� ��������� � ���������� Category � ��������� Name
	bool CImage::SetParamValue(enCatID Category, wstring Name, sParam Param)
	{
		BEGIN_SET_PROP_MAP(Category, Name, Param)
			SET_PROP_STRING(CAT_APPEARANCE, L"Image", SetImage(val))
			SET_PROP_BOOL(CAT_APPEARANCE, L"Border",  DrawBorder(val))
			SET_PROP_RGB(CAT_APPEARANCE, L"Border color", SetBorderColor(val))
			SET_PROP_INT(CAT_APPEARANCE, L"Border thickness", SetBorderWidth(val))
			SET_PROP_BOOL(CAT_APPEARANCE, L"Auto size", SetStretchImage(val))
		END_SET_PROP_MAP()
		bool res = CBaseObject<CImage>::SetParamValue(Category, Name, Param);
		RotateImage(GetAngle());

		HelpersLib::CCfgReg reg;
		CString RegPath;
		RegPath.Format(L"%s\\LastObjectSettings\\Image", cProduct);
		reg.Open((LPCTSTR)RegPath, false, true);
		reg.WriteFloat(L"Width", GetSize().x);
		reg.WriteFloat(L"Height", GetSize().y);
		reg.WriteString(L"Image", GetImageName().c_str());
		return res;
	}

	//���������� ������� ����� ������ ���� 
	BOOL CImage::OnMouseLButtonDown(sVector Point)
	{
		return CBaseObject<CImage>::OnMouseLButtonDown(Point);
	}

	//���������� ������ ������ ������ ���� 
	BOOL CImage::OnMouseRButtonDown(sVector Point)
	{
		return CBaseObject<CImage>::OnMouseRButtonDown(Point);
	}

	//���������� ���������� ����� ������ ���� 
	BOOL CImage::OnMouseLButtonUp(sVector Point)
	{
		return CBaseObject<CImage>::OnMouseLButtonUp(Point);
	}

	//���������� ����������� ����
	BOOL CImage::OnMouseMove(sVector Point)
	{
		return CBaseObject<CImage>::OnMouseMove(Point);
	}

	//���������� ������� ������� ����������
	BOOL CImage::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{	
		return CBaseObject<CImage>::OnKeyDown(wParam, lParam);
	}

	//�������� �������� �� point �� ������
	bool CImage::HitTest(sVector point)
	{
		return CBaseObject<CImage>::HitTest(point);
	}
}