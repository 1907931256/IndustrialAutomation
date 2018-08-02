#pragma once
#include "object.h"
/********************************************************************
	������:	        2004/12/07
	������:	        7:12:2004   18:05
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ObjRectangle.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ObjRectangle
	����������:	    h
	�����(�):	    ������
    �����(�):       CObjRectangle
	
��������: ����� ����������� ������� "�������������"
*********************************************************************/

class CObjRectangle
	: public CObject
{
public:
	//Constructor/Destructor
	CObjRectangle(void);
	virtual ~CObjRectangle(void);

	//���������� �������
	virtual void Draw(HDC dc);

	//�������� ���� �����
	inline sRGB GetBorderColor(){return _BorderColor;};
	//���������� ���� �����
	inline void SetBorderColor(sRGB Color){_BorderColor = Color;};
	//���������� �������� ��� ��� �����
	inline void DrawBorder(bool Draw=true){_DrawBorder = Draw;};
	//���������� �������� ����� ��� ���
	inline bool IsDrawBorder(){return _DrawBorder;};
	void Serialize(CMemFile& file, BOOL IsLoading = TRUE);

protected:
	sRGB	_BorderColor;
	bool	_DrawBorder;
};