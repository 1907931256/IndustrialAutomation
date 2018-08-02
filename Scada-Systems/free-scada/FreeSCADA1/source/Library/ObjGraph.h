#pragma once
#include "object.h"
#include "graph/Scatter.h"

/********************************************************************
	������:	        2004/12/07
	������:	        7:12:2004   18:05
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ObjRectangle.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ObjRectangle
	����������:	    h
	�����(�):	    �������
    �����(�):       CObjRectangle
	
��������: ����� ����������� ������� "������"
*********************************************************************/
class CObjGraph
	: public CObject
{
public:
	CObjGraph(void);
	virtual ~CObjGraph(void);
	void recalcBounds();
	//���������� �������
	virtual void Draw(HDC dc);
	inline void SetGraphTime(int t){_GraphTime=t;};
	inline long GetGraphTime(){return _GraphTime;};
	void Serialize(CMemFile& file,  BOOL IsLoading = TRUE);

protected:
		CTimeGraph<double> m_Graph;
		long _GraphTime;// � ��������
	
};