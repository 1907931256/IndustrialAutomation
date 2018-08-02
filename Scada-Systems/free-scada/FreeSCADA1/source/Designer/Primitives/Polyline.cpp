#include "StdAfx.h"
#include ".\polyline.h"
#include "ManipulatorVertex.h"

namespace Primitives
{
	CPolyline::CPolyline(void)
	{
		_EditVertex = FALSE;
	}

	CPolyline::~CPolyline(void)
	{
	}

	//���������� ������� ����� ������ ����
	BOOL CPolyline::OnMouseLButtonDown(sVector Point)
	{
		return CBaseObject<CPolyline>::OnMouseLButtonDown(Point);
	}

	//���������� ������� ������ ������ ����
	BOOL CPolyline::OnMouseRButtonDown(sVector Point)
	{
		return CBaseObject<CPolyline>::OnMouseRButtonDown(Point);
	}

	//���������� ���������� ����� ������ ����
	BOOL CPolyline::OnMouseLButtonUp(sVector Point)
	{
		return CBaseObject<CPolyline>::OnMouseLButtonUp(Point);
	}

	//���������� ����������� ����
	BOOL CPolyline::OnMouseMove(sVector Point)
	{
		return CBaseObject<CPolyline>::OnMouseMove(Point);
	}

	//���������� �������� ������� ����� ������ ����
	BOOL CPolyline::OnMouseLButtonDblClk(sVector Point)
	{
		CObjectMenagerPtr om;
		if(!om->IsSelected(this)) return FALSE;

		//������� ��� ������������
		OnLostFocus();

		//������� ����������� ����� ���������
		CManipulatorVertex	*vertex = new CManipulatorVertex(this);

		_Manipulators.push_front(vertex);
		_EditVertex = TRUE;
		return CBaseObject<CPolyline>::OnMouseLButtonDblClk(Point);
	}

	//���������� ������� ������� ����������
	BOOL CPolyline::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		UINT key = (UINT)wParam;
		// ���� ������ Esc ������� �� ������ �������������� �����
		if (key == 27)
		{
			//	_EditVertex = FALSE;

			OnLostFocus();
			OnSetFocus();
		}
		return CBaseObject<CPolyline>::OnKeyDown(wParam, lParam);
	}

	//���������� ��������� ������ ��������
	void CPolyline::OnSetFocus()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		//������������ � ���� ������� ��������� ����� ������� 
		prop->SetObject(this);
		prop->FreeInst();
	//	CObjPolyline::OnSetFocus();
		return CBaseObject<CPolyline>::OnSetFocus();
		//������� ����������� ����� ���������
		//CManipulatorVertex	*vertex = new CManipulatorVertex(GetObject());

		//_Manipulators.push_front(vertex);
		//_EditVertex = TRUE;
	}

	//���������� ������ ������ ��������
	void CPolyline::OnLostFocus()
	{
		CObjPolyline::OnLostFocus();
		CBaseObject<CPolyline>::OnLostFocus();
	}

	//���������� ��������� �������
	void CPolyline::OnEdit()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		//��������� ��������� � ���� �������
		prop->RefreshProperty();
		prop->FreeInst();

		return CObjPolyline::OnEdit();
	}

	//��������� ���������
	void CPolyline::Draw(HDC dc) 
	{
		const bool Visible = IsVisible();
		//� ��������� ������ ������ �������
		SetVisible(true);

		CObjPolyline::Draw(dc);
		//������ ��� ������������ ������� � ������ ������ ������� � �������
		for_each(_Manipulators.begin(),_Manipulators.end(), bind2nd(mem_fun(&CObject::Draw), dc));
		//��������������� �������� �������� ���������
		SetVisible(Visible);
	}

	//�������� �������� �� point �� ������
	bool CPolyline::HitTest(sVector point)
	{
		if(CBaseObject<CPolyline>::HitTest(point))
			return true;

		sVector pos		= GetObject()->GetPosition();
		sVector size	= GetObject()->GetSize();

		sVector center;
		if(size.x < MOVE_BLOCK_SIZE)
			center.x = MOVE_BLOCK_SIZE/2;
		else
			center.x = size.x/2;

		if(size.y < MOVE_BLOCK_SIZE)
			center.y = MOVE_BLOCK_SIZE/2;
		else
			center.y = size.y/2;



		sVector points[4];
		points[0] = sVector(-center.x, -center.y);
		points[1] = sVector(+center.x, -center.y);
		points[2] = sVector(+center.x, +center.y);
		points[3] = sVector(-center.x, +center.y);

		for(int i=0;i<4;i++)
		{
			points[i].Rotate(GetObject()->GetAngle());
			points[i] += pos+center;
		}

		CGraphic graph(NULL);
		return graph.TestPtInRect(point, points);
	}
	
}
