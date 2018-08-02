#include "StdAfx.h"
#include ".\sound.h"

namespace Primitives
{
	CSound::CSound(void)
	{
		RemoveParam(CAT_GEOMETRY, L"Angle");
		RemoveParam(CAT_GEOMETRY, L"Height");
		RemoveParam(CAT_GEOMETRY, L"Width");
		_Categories[CAT_GEOMETRY].sort(sCompareName());

		RemoveParam(CAT_APPEARANCE, L"Color");
		_Categories[CAT_APPEARANCE].sort(sCompareName());
		
		_Categories[CAT_DATA].push_back(sCtrlParam(CT_SOUND, L"Sound"));
		_Categories[CAT_DATA].push_back(sCtrlParam(CT_BOOL, L"Loop"));
		_Categories[CAT_DATA].sort(sCompareName());
	}

	CSound::~CSound(void)
	{
	}

	//�������� �������� � ��������� Name ��������� Category
	bool CSound::GetParamValue(enCatID Category, wstring Name, sParam& Param)
	{
		BEGIN_GET_PROP_MAP(Category, Name, Param)
			GET_PROP_STRING(CAT_DATA, L"Sound", GetSoundName().c_str())
			GET_PROP_BOOL(CAT_DATA, L"Loop", GetLoop())
		END_GET_PROP_MAP()
		return CBaseObject<CSound>::GetParamValue(Category, Name, Param);	
	}

	//���������� �������� � ��������� Name ��������� Category
	bool CSound::SetParamValue(enCatID Category, wstring Name, sParam Param)
	{
		BEGIN_SET_PROP_MAP(Category, Name, Param)
			SET_PROP_STRING(CAT_DATA, L"Sound", SetSoundName(val))
			SET_PROP_BOOL(CAT_DATA, L"Loop", SetLoop(val))
		END_SET_PROP_MAP()
		return CBaseObject<CSound>::SetParamValue(Category, Name, Param);
	}

	//���������� ��������� �������� ������
	void CSound::OnSetFocus()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		//��������� ���� ������� ����������� �������
		prop->SetObject(this);
		prop->FreeInst();
		
		CObject* obj = GetObject();
		CManipulatorMover		*move	= new CManipulatorMover(obj);
		_Manipulators.push_front(move);
	}

	//���������� ������ �������� ������
	void CSound::OnLostFocus()
	{
		CBaseObject<CSound>::OnLostFocus();
	}

	//���������� ��������� �������
	void CSound::OnEdit()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		prop->RefreshProperty();
		prop->FreeInst();
	}

	//���������
	void CSound::Draw(HDC dc_)
	{
		const bool Visible = IsVisible();
		//� ��������� ������ ������ �������
		SetVisible(true);

		CObjSound::Draw(dc_);
		CBaseObject<CSound>::Draw(dc_);
		//��������������� �������� �������� ���������
		SetVisible(Visible);
	}

	//���������� ������� ����� ������ ����
	BOOL CSound::OnMouseLButtonDown(sVector Point)
	{
		return CBaseObject<CSound>::OnMouseLButtonDown(Point);
	}

	//���������� ������� ������ ������ ����
	BOOL CSound::OnMouseRButtonDown(sVector Point)
	{
		return CBaseObject<CSound>::OnMouseRButtonDown(Point);
	}

	//���������� �������� ������� ����� ������ ����
	BOOL CSound::OnMouseLButtonDblClk(sVector Point)
	{
		return CBaseObject<CSound>::OnMouseLButtonDblClk(Point);
	}

    //���������� ���������� ����� ������ ����
	BOOL CSound::OnMouseLButtonUp(sVector Point)
	{
		return CBaseObject<CSound>::OnMouseLButtonUp(Point);
	}

	//���������� ����������� ����
	BOOL CSound::OnMouseMove(sVector Point)
	{
		return CBaseObject<CSound>::OnMouseMove(Point);
	}

	//���������� ������� ������� ����������
	BOOL CSound::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{	
		return CBaseObject<CSound>::OnKeyDown(wParam, lParam);
	}

	//�������� �������� �� ������ point �� ������
	bool CSound::HitTest(sVector point)
	{
		return CBaseObject<CSound>::HitTest(point);
	}

	
}