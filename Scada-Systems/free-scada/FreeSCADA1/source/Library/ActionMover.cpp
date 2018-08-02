#include "common.h"
#include ".\actionmover.h"
#include "ObjectMenager.h"
#include "ObjPolyline.h"

CActionMover::CActionMover(CObject* Owner_)
	: CAction(Owner_)
	, _CurrentPos(0)
	, _PathObject(L"")
{
	//������������� �������
	_Type = AT_MOVER;
	wstring name(L"Action_Mover_");
	if(Owner_)
	{
		name.append(Owner_->GetName());	
		name.append(L"_");
	}
	SetName(GenerateUniqueActionName(name));

}

CActionMover::~CActionMover(void)
{
}

void CActionMover::Update()
{
	if(	_Owner == NULL)
		return;

	//�������� ����� ������ ��� ����. ���� �� ������ - �������
	CObjectMenagerPtr mngr;
	CObjPolyline* obj = (CObjPolyline*)mngr->FindObject(_PathObject);
	if(obj == NULL)
		return;

	//�������� ���� � ���� ������ ������
	typedef vector<sVector>::iterator it;
	vector<sVector> v = obj->GetVertexesGlobal();
	if(v.size() < 2)
		return; //����������� ������

	//���������� ����� ���� � ���������
	double length=0;
	double current_pos_tmp=0;
	vector<double> lines;
	for(it i=v.begin();i!=v.end()-1;i++)
	{
		sVector tmp;
		tmp = *(i+1) - *i;
		length += tmp.Length(); //������ ����
	}
	lines.push_back(0);
	for(it i=v.begin();i!=v.end()-1;i++)
	{
		//��������� � % �� ������ ����
		//�������� ��� ���� ������ ��� ����� ����: 0.0; 0.75; 1.0.
		sVector tmp;
		tmp = *(i+1) - *i;
		current_pos_tmp += tmp.Length();
		lines.push_back(current_pos_tmp/length); 
	}

	//���������� �� ����� ������� ������ ���������� ������
	double val = CalcControlValue();
	_CurrentPos = (float)((val - GetValueMin())/(GetValueMax()-GetValueMin()));

	//���� �������
	sVector v1,v2,NewPos;
	double k1=1,k2=1;
	for(size_t i=0;i!=lines.size()-1;i++)
	{
		if(lines[i] <= _CurrentPos && lines[i+1] >= _CurrentPos)
		{
			v1 = v[i];
			v2 = v[i+1];
			k1 = lines[i];
			k2 = lines[i+1];
			break;
		}
	}
	//����������� ������� ������� �������
	NewPos.x = (float)((v2.x - v1.x)/((k2-k1)/(_CurrentPos - k1))) + v1.x;
	NewPos.y = (float)((v2.y - v1.y)/((k2-k1)/(_CurrentPos - k1))) + v1.y;
	NewPos -= _Owner->GetSize()/2;
	_Owner->MoveTo(NewPos.x, NewPos.y);
}

void CActionMover::Serialize(CMemFile& file, BOOL IsLoading)
{
	if(IsLoading)
	{
		//��������
		file>>_CurrentPos;
		file>>_PathObject;
	}
	else
	{
		//����������
		file<<_CurrentPos;
		file<<_PathObject;
	}
	CAction::Serialize(file, IsLoading);
}


bool CActionMover::GetParamValue(wstring Name, CComVariant& Variant)
{
	//�������� �������� ��������� ������ �� ��� ����������� ��������
	BEGIN_GET_VALUE_MAP(Name, Variant)
		GET_VALUE_STRING(L"Trajectory", this->GetPathObject().c_str())
	END_GET_VALUE_MAP()

	return CAction::GetParamValue(Name, Variant);
}


bool CActionMover::SetParamValue(wstring Name, CComVariant Variant)
{
	//���������� �������� ��������� ������ �� ��� ����������� ��������
	BEGIN_SET_VALUE_MAP(Name, Variant)
		SET_VALUE_STRING(L"Trajectory", this->SetPathObject(val))
	END_SET_VALUE_MAP()
	return CAction::SetParamValue(Name, Variant);
}

void CActionMover::SetPathObject(wstring PathObject)
{
	_PathObject = PathObject;
}


wstring CActionMover::GetPathObject()
{
	return _PathObject;
}