#include "StdAfx.h"
#include ".\select.h"

namespace Primitives
{
	CSelect::CSelect(void)
	{
	}

	CSelect::~CSelect(void)
	{
	}

	//���������� ������� ����� ������ ����
	BOOL CSelect::OnMouseLButtonDown(sVector Point)
	{
		return CBaseObject<CSelect>::OnMouseLButtonDown(Point);
	}

	//���������� ������� ������ ������ ����
	BOOL CSelect::OnMouseRButtonDown(sVector Point)
	{
		return CBaseObject<CSelect>::OnMouseRButtonDown(Point);
	}

	//���������� ���������� ����� ������ ����
	BOOL CSelect::OnMouseLButtonUp(sVector Point)
	{
		return CBaseObject<CSelect>::OnMouseLButtonUp(Point);
	}

	//���������� ����������� ����
	BOOL CSelect::OnMouseMove(sVector Point)
	{
		return CBaseObject<CSelect>::OnMouseMove(Point);
	}

	//���������� ��������� ���������� �������
	void CSelect::OnEdit()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		//���������� ���������� ������� � ���� ������� 
		prop->RefreshProperty();
		prop->FreeInst();
	}

	//���������� �������� ������� ����� ������ ����
	BOOL CSelect::OnMouseLButtonDblClk(sVector Point)
	{
		return CBaseObject<CSelect>::OnMouseLButtonDblClk(Point);
	}

	//���������� ������� ������� ����������
	BOOL CSelect::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		return CBaseObject<CSelect>::OnKeyDown(wParam, lParam);
	}

	//��������� Selection
	void CSelect::Draw(HDC dc)
	{
		CSelection::Draw(dc);
		CBaseObject<CSelect>::Draw(dc);
	}

	//���������� ������� � Selection
	void CSelect::AddObject(CObject* obj)
	{
		//�������� ������ � CBase
		CBase* Base = GetBase(obj);
		//���� � Selection ��� �� ������ �������, ��������� ����� 
		//���������-������ sCtrlParam ����������� ����� �������
		if(_Objects.empty())
		{
			_Categories.clear();
			TCategoryList CategoryList = Base->GetCategories();
			for(TCategoryListIter it = CategoryList.begin(); it != CategoryList.end(); it++)
			{
				_Categories[*it] = Base->GetParameters(*it);
			}
			 
			CSelection::AddObject(obj);
			return;
		}


		TCategoryList ObjCategoryList = Base->GetCategories();
		TCategoryList CategoryList = GetCategories();
		TCategoryList tmp;


		//��������� ������ �� ���������, ������� ���� � � Selection, � � �������
		for(TCategoryListIter it = ObjCategoryList.begin(); it != ObjCategoryList.end(); it++)
		{
			TCategoryListIter find = find_if(CategoryList.begin(), CategoryList.end(), sFindCategory(*it));
			if(find != CategoryList.end()) tmp.push_back(*find);
		}
		CategoryList = tmp;

		TCategoryMap CategoryMap;

		//��������� ����� ���������-������ sCtrlParam �� ��������� � ����������, 
		//������� ���� � � Selection, � � �������

		for(TCategoryListIter it = CategoryList.begin(); it != CategoryList.end(); it++)
		{
			TCtrlParamList ParamList = GetParameters(*it);
			TCtrlParamList ObjParamList = Base->GetParameters(*it);
			TCtrlParamList temp;
			for(TCtrlParamListIter iter = ObjParamList.begin(); iter != ObjParamList.end(); iter++)
			{
				TCtrlParamListIter find = find_if(ParamList.begin(), ParamList.end(), sFindCtrlParam(*iter));
				if(find != ParamList.end())
				{
					if((*it == CAT_EMPTY) && (find->Param == L"Name"))
						continue;
					temp.push_back(*find);
				}
			}
			CategoryMap[*it] = temp;
		}
		_Categories.clear();
        _Categories = CategoryMap;
		CSelection::AddObject(obj);
	}

	//���������� ��������� �������� ������
	void CSelect::OnSetFocus()
	{
		CObjectPropertyWindow* prop = CObjectPropertyWindow::Instance();
		//��������� ���� ������� ����������� �������
		prop->SetObject(this);
		prop->FreeInst();
		CBaseObject<CSelect>::OnSetFocus();
	}


	void CSelect::OnLostFocus()
	{
		_Categories.clear();
		CBaseObject<CSelect>::OnLostFocus();
	}

	//�������� �������� ���������
	bool CSelect::GetParamValue(enCatID Category, wstring Name, sParam& Param )
	{
		//���������� ��������� ������� ������� �� Selection
		CBase* Base = GetBase(*_Objects.begin());
		TCategoryMapIter MapIter = _Categories.find(Category);
		if(MapIter != _Categories.end())
		{
			TCtrlParamList ParamList = MapIter->second;
			TCtrlParamListIter ParamIter = find_if(ParamList.begin(), ParamList.end(), sFindCtrl(Name));
			if(ParamIter != ParamList.end())
			{
				//����������� ���������� �� ������������� � ����������
				RelateToAbsolute(Base->GetObject());
				//�������� �������� ���������
				Base->GetParamValue(Category, Name, Param);
				//����������� ���������� �� ���������� � �������������
				AbsoluteToRelate(Base->GetObject());
			}
		}
		return true;
	}

	//���������� �������� ���������
	bool CSelect::SetParamValue(enCatID Category, wstring Name, sParam Param)
	{
		//������������� ����� �������� ��������� ��� ���� �������� � Selection
		for(list<CObject*>::iterator it = _Objects.begin(); it != _Objects.end(); it++)
		{
			CBase* Base = GetBase(*it);
			//����������� �� ������������� ��������� � ����������
			RelateToAbsolute(Base->GetObject());
			//������������� ����� �������� ���������
			Base->SetParamValue(Category, Name, Param);
			//����������� �� ���������� � ������������� ����������
			AbsoluteToRelate(Base->GetObject());
		}
		//�������� ������� � ������� Selection
		CalcSizeEndPos();
		return false;
	}
}
