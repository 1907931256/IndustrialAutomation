#include "common.h"
#include "ObjectMenager.h"
#include "graphic.h"
#include "ObjRectangle.h"
#include "Action.h"

CObjRectangle::CObjRectangle(void)
	: _BorderColor(RGB(0,0,0))
	, _DrawBorder(true)
	
{
	//���������� ���������� ��� ��� �������
	SetName(GenerateUniqueObjectName(L"Rectangle_"));
	SetTypeID(_RECTANGLE);
	SetActionFlags(AT_ALL_VISUAL);
}

CObjRectangle::~CObjRectangle(void)
{
}

//��������� �������
void CObjRectangle::Draw(HDC dc_)
{
	if(!IsVisible())
		return;

	CDCHandle dc(dc_);

	//�������� ��������� ��������� ��������
	CObjectMenagerPtr mng;
	CPoint pt;
	//������� �� ���������� ��������� � ��������
	pt = mng->GlobalToScreen(GetPosition());

	//�������� � ����� "�����"
	CBrush Brush;
	Brush.CreateSolidBrush(GetColor().AsCOLORREF());

	CBrushHandle bold = dc.SelectBrush(Brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, _DrawBorder?_BorderColor.AsCOLORREF():GetColor().AsCOLORREF());
	CPenHandle pold = dc.SelectPen(pen);
	
	//������ ������ �������������� (��� ��������)
	sVector points[4];
	points[0] = GetSize() / -2;
	points[1] = sVector(GetSize().x / -2, GetSize().y / 2);
	points[2] = GetSize() / 2;
	points[3] = sVector(GetSize().x / 2, GetSize().y / -2);
	for(int i=0;i<4;i++)
	{
		//������� � ����������� ������
		points[i].Rotate(GetAngle());
		points[i] += GetPosition()+GetSize()/2;
		points[i] = mng->GlobalToScreen(points[i]);
	}

	//����� �������������� �� �����
	CGraphic graph(dc_);
	graph.Rectangle(points[0], points[1], points[2], points[3]);

	//������������ ������
	dc.SelectBrush(bold);
	dc.SelectPen(pold);
}


void CObjRectangle::Serialize(CMemFile& file, BOOL IsLoading)
{
	CObject::Serialize(file, IsLoading);

	if(IsLoading)
	{
		file>>_DrawBorder;
		file>>_BorderColor;
	}
	else
	{
		file<<_DrawBorder;
		file<<_BorderColor;
	}


}