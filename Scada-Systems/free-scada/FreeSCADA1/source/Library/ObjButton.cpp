#include "common.h"
#include "ObjectMenager.h"
#include "VariableMenager.h"
#include "MemFile.h"
#include ".\objbutton.h"
#include "Action.h"

CObjButton::CObjButton(void)
{
	//������������� �������
	_VariableName	= L"";
	_IsDown			= false; 

	SetName(GenerateUniqueObjectName(L"Button_"));

	_Font.Name		= L"Arial";
	_Font.Height	= 14;
	_Font.Bold		= true;
	_Font.Italic	= false;
	_Font.StrikeOut	= false;
	_Font.Underline	= false;

	_Caption		= GetName();

	SetTypeID(_BUTTON);
	SetActionFlags(AT_MOVER | AT_SIZER | AT_VISUAL);
}

CObjButton::~CObjButton(void)
{

}

void CObjButton::Draw(HDC dc_)
{
	if(!IsVisible())
		return; //���� ������ ���������, �� ������ �� ������

	if(!_VariableName.empty())
	{
		//�������� �������� ����������
		CVariableMenagerPtr vm;
		CComVariant v = vm->GetVariable(_VariableName);
		v.ChangeType(VT_BOOL);
		//������������� ��������� ������ � ����������� �� ��������
		_IsDown = v.boolVal?true:false;
	}

	CDCHandle dc(dc_);

	//�������� ��������� ��������� ��������
	CObjectMenagerPtr mng;
	CPoint pt;
	//������� �� ���������� ��������� � ��������
	pt = mng->GlobalToScreen(GetPosition());

	//������ ������ (�������, ������ ����, ������� ����)
	COLORREF BaseColor = GetColor().AsCOLORREF();
	int offset = 100;
	COLORREF BlackColor = RGB(GetRValue(BaseColor)-offset > 0 ? GetRValue(BaseColor)-offset : 0,
							  GetGValue(BaseColor)-offset > 0 ? GetGValue(BaseColor)-offset : 0,
							  GetBValue(BaseColor)-offset > 0 ? GetBValue(BaseColor)-offset : 0);

	COLORREF WhiteColor = RGB(GetRValue(BaseColor)+offset < 255 ? GetRValue(BaseColor)+offset : 255,
							  GetGValue(BaseColor)+offset < 255 ? GetGValue(BaseColor)+offset : 255,
							  GetBValue(BaseColor)+offset < 255 ? GetBValue(BaseColor)+offset : 255);

	//�������� � ����� "�����"
	CBrush Brush;
	Brush.CreateSolidBrush(GetColor().AsCOLORREF());

	//�������� � ����� "���������"
	CPen TopPen, BottomPen, ObjectPen;
	ObjectPen.CreatePen(PS_SOLID, 1, BaseColor);


	if(_IsDown)
	{
		//������ ������.
		TopPen.CreatePen(PS_SOLID, 2, BlackColor);
		BottomPen.CreatePen(PS_SOLID, 2, WhiteColor);
	}
	else
	{
		//������ ������.
		TopPen.CreatePen(PS_SOLID, 2, WhiteColor);
		BottomPen.CreatePen(PS_SOLID, 2, BlackColor);
	}
	

	CPenHandle pold = dc.SelectPen(ObjectPen);

	//������ ��������� ������
	sVector pos = GetPosition();
	sVector size = GetSize();
	CPoint pts[4];
	pts[0] = CPoint((int)pos.x, (int)pos.y);
	pts[1] = CPoint((int)pos.x + (int)size.x, (int)pos.y);
	pts[2] = CPoint((int)pos.x + (int)size.x, (int)pos.y + (int)size.y);
	pts[3] = CPoint((int)pos.x, (int)pos.y + (int)size.y);
	CObjectMenagerPtr om;
	for(int i=0;i<4;i++)
		pts[i] = om->GlobalToScreen(pts[i]);

	CRect rect(pts[0], pts[2]);

	//����� �������������� �� DC
	dc.SelectPen(TopPen);
	dc.FillRect(&rect, Brush);
	dc.MoveTo(pts[3]);
	dc.LineTo(pts[0]);
	dc.LineTo(pts[1]);
	dc.SelectPen(BottomPen);
	dc.LineTo(pts[2]);
	dc.LineTo(pts[3]);
	
	//������� �����
	CFont font;
	font.CreateFont(	_Font.Height,
						0,
						0,
						0,
						_Font.Bold?FW_BOLD:FW_NORMAL,
						_Font.Italic?TRUE:FALSE,
						_Font.Underline?TRUE:FALSE,
						_Font.StrikeOut?TRUE:FALSE,
						DEFAULT_CHARSET,
						OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH,
						_Font.Name.c_str());
	if(font.IsNull())
		return;

	//����������� ��������� ������
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(GetTextColor().AsCOLORREF());

	//����� ������
	CFontHandle OldFont = dc.SelectFont(font);
	dc.DrawText(_Caption.c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_EXPANDTABS);
	dc.SelectFont(OldFont);

	//������������ ������
	dc.SelectPen(pold);
}


void CObjButton::Serialize(CMemFile& file, BOOL IsLoading)
{
	CObject::Serialize(file, IsLoading);
	if(IsLoading)
	{
		//��������

		file>>_Caption;
		file>>_VariableName;
		file>>_IsDown;
		file>>_TextColor;

		_Font.Serialize(file, IsLoading);
	}
	else
	{
		//����������

		file<<_Caption;
		file<<_VariableName;
		file<<_IsDown;
		file<<_TextColor;

		_Font.Serialize(file, IsLoading);
	}
}

BOOL CObjButton::OnMouseLButtonDown(sVector Point)
{
	//������ ��������� ������
	_IsDown = !_IsDown;

	if(!_VariableName.empty())
	{
		//���� ������ ����������� ����������, ���������� � ���
		//����� ���������
		CVariableMenagerPtr vm;
		CComVariant tmp = _IsDown?TRUE:FALSE;
		VARTYPE vt = vm->GetVariable(_VariableName).vt;	//�������� ��� ����������
		tmp.ChangeType(vt); //�������� � ���� ����������
	
		//��������. ���� ��� OPC, ��������� �� ������.
		vm->SetVariable(_VariableName, tmp, true);

		return TRUE;
	}
	return FALSE;
}