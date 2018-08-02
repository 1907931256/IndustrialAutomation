#pragma once
/********************************************************************
	������:	        2004/12/08
	������:	        8.12.2004   9:57
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ObjectMenager.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ObjectMenager
	����������:	    h
	�����(�):	    �������, ������
    �����(�):       CObjectMenager
	
��������:	����� "�������� ��������" ��������� �������� �� ������������� ���������
����� ���������. �������� �������� � ������������ ������ ���� ����������. �����������
������� ��� ����������� � ������� �������� (���������).
*********************************************************************/

#include "Object.h"
#include "Selection.h"
#include "Track.h"

class CObjectMenager
	:public CSingleton<CObjectMenager>
{
friend class CArchiveManager;
public:
	//�������� ������
	inline void AddObject(CObject* obj){ATLASSERT(obj != NULL);_Objects.push_front(obj);};
	//������� ������
	void RemoveObject(CObject* obj);
	//������� ��� �������
	void RemoveAll();
	//����� ������ �� �����
	CObject* FindObject(wstring Name);
	//����� ������� ��������� ����
	list<CObject*> FindObjects(enTypeID TypeID);
	//�������� ������ ���� ��������
	list<CObject*> GetObjectsList(){return _Objects;};
	//������ ������� �� ��������� ������
	bool IsSelected(CObject* obj);

	//���������� ��� �������
	inline void DrawObjects(HDC dc){for_each(_Objects.rbegin(),_Objects.rend(), bind2nd(mem_fun(&CObject::Draw), dc));};

	//������� �� ���������� ��������� � ��������
	CPoint GlobalToScreen(sVector);
	//������� �� �������� ��������� � ����������
	sVector ScreenToGlobal(CPoint);
	//�������� ����� ���� ��������
	TStrings GetObjectNames();

	//////////////////////////////////////////////////////////////////////////
	// ��������� ���������
	BOOL ProcessMouseLButtonDown(WPARAM wParam, CPoint lParam);		//WM_LBUTTONDOWN
	BOOL ProcessMouseRButtonDown(WPARAM wParam, CPoint lParam);		//WM_RBUTTONDOWN
	BOOL ProcessMouseLButtonDblClk(WPARAM wParam, CPoint lParam);	//WM_LBUTTONDBLCLK
	BOOL ProcessMouseLButtonUp(WPARAM wParam, CPoint lParam);		//WM_LBUTTONUP
	BOOL ProcessMouseMove(WPARAM wParam, CPoint lParam);			//WM_MOUSEMOVE
	BOOL ProcessKeyDown(WPARAM wParam, LPARAM lParam);				//WM_KEYDOWN
	//////////////////////////////////////////////////////////////////////////
	
	//�������������� ��� ��������� �� ����� � �������� ������
	void CaptureMouse(CObject* obj){_ObjCaptureMouse=obj;};
	//������� ������������� "�������" ��������� � ���������� �����
	void ReleaseCaptureMouse(){_ObjCaptureMouse=NULL;};
	//�������� ������, ������� ��������� ��� "�������" ���������
	CObject* GetCaptureMouse(){return _ObjCaptureMouse;};

	//������� ������� � �������� �������
	void SelectWindow(sVector LeftTop, sVector RightBottom);
	//��������� ������� �� ������ ����������
	void MoveToSelection(CObject* obj);
	//��������� ������� �� ������ ����������
	void MoveFromSelection(CObject* obj);
	//��������� ������� �� CSelection � CObjectMenager � �������� CSelection
	void ClearSelection(CSelection::enPosition Pos);
	//��������� CSelection ������ �������
	void SetSelection(CSelection* Selection){ delete _Selection;  _Selection = Selection; }
	//�������� ��������� �� CSelection
	CSelection* GetSelection(){ return _Selection; }
	//�������� ��������� �� ���������� ������
	CObject* GetSelected(){ return _Selected; }
	//������� ������
	void SelectObject(CObject* obj);
	//�������� ������ � ����������
	void AddToSelected(CObject* obj);	
	//������������� ����� �������� ����������� ������ ������� (������������)
	DWORD GenerateOrderPos();
	//���������� ���������� �������� �������� � ������������ � ������������
	//���������� ������� (������� ����������� ������������������)
	void SetObjOrderPos();
	//������������� ������� � ������������ � ������������ ���������� �������
	void SortObjects();

	struct sViewPort
	{
		sVector TopLeft,BottomRight;
	}m_ViewPort;	//������� ������� (������� ������ � ���������� �����������)

protected:
	list<CObject*>	_Objects;			//������ ��������
	CObject*		_ObjCaptureMouse;	//������ � ������� ���������������� ��������� �� �����
	bool			_LMButtonDown;		//���� ������� ����� ������� �����
	sVector			_BeginPoint;		

	CSelection*		_Selection;
	CObject*		_Selected;			//���������� ������
	CTrack*			_Track;

protected:
	//Constructor/Destructor
	CObjectMenager(void);
	virtual ~CObjectMenager(void);
	DEF_SINGLETON(CObjectMenager);
};

typedef CSingletonPtr<CObjectMenager> CObjectMenagerPtr;