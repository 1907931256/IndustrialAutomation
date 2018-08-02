#include "common.h"
#include "ObjectMenager.h"
#include "graphic.h"
#include "ObjEllipse.h"
#include "Action.h"


CObjEllipse::CObjEllipse(void)
{
	//�������� "���������"
	_DrawBorder = false;
	_BorderColor = sRGB(0,0,0);

	_Pen.CreatePen(PS_SOLID, 1, GetColor().AsCOLORREF());
	//���������� ���������� ��� ��� �������
	SetName(GenerateUniqueObjectName(L"Ellipse_"));
	SetTypeID(_ELLIPSE);
	SetActionFlags(AT_ALL_VISUAL);
}

CObjEllipse::~CObjEllipse(void)
{
	//������� "��������"
	_Pen.DeleteObject();
}

void CObjEllipse::Draw(HDC dc_)
{
	if(!IsVisible())
		return;

	CDCHandle dc(dc_);

	//�������� ��������� ��������� ��������
	CObjectMenagerPtr mng;

	sVector pos = GetPosition();
	sVector size = GetSize();
	float a = size.x/2;
	float b = size.y/2;
	sVector center = pos + size/2;
	

	

	//�������� � ����� "�����"
	CBrush Brush;
	Brush.CreateSolidBrush(GetColor().AsCOLORREF());

	_Pen.DeleteObject();
	if(_DrawBorder)
	{
		_Pen.CreatePen(PS_SOLID, 1, _BorderColor.AsCOLORREF());
	}
	else
	{
		_Pen.CreatePen(PS_SOLID, 0, GetColor().AsCOLORREF());
	}

	CBrushHandle bold = dc.SelectBrush(Brush);
	CPenHandle pold = dc.SelectPen(_Pen);
	
	//������ ������ �� ��������� ������
	POINT points[360]; 
	
	//������ ������
	for(int Fi = 0; Fi < 360; Fi++)
	{
		float angle = PI*Fi/180 - GetAngle();
		float r = a*b/sqrt((pow(a*sin(angle),2) + pow(b*cos(angle),2)));
		points[Fi].x = (LONG)(center.x + cos(PI*Fi/180)*r);
		points[Fi].y = (LONG)(center.y + sin(PI*Fi/180)*r);
		//������� �� ���������� ��������� � ��������
		points[Fi] = mng->GlobalToScreen(sVector(points[Fi]));
	}
	
	//����� ������ �� �����
	::Polygon(dc, (LPPOINT)points, 360);

	//������������ ������
	dc.SelectBrush(bold);
	dc.SelectPen(pold);
}


void CObjEllipse::Serialize(CMemFile& file, BOOL IsLoading)
{
	if(IsLoading)
	{
		file>>_BorderColor;
		file>>_DrawBorder;
	}
	else
	{
		file<<_BorderColor;
		file<<_DrawBorder;
	}
	CObject::Serialize(file, IsLoading);
}



