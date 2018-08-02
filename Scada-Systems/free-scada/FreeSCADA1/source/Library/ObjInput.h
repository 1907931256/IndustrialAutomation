#pragma once
/********************************************************************
	������:	        2005/02/07
	������:	        7.2.2005   14:06
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\ObjInput.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    ObjInput
	����������:	    h
	�����(�):	    �������, ������
    �����(�):       CObjInput
	
	  ������ "���� �����". ����������� � �����-���� ����������. ��� �������
	������������� �� ������ (� ������ ����� ���������) ������������ ���������
	OnBtnDown, ������� ����� ���� ���������� � �����������.
*********************************************************************/

#include "object.h"

class CObjInput
	: public CObject
{
public:
	CObjInput(void);
	~CObjInput(void);

	//���������� �������
	virtual void Draw(HDC dc);

	//����������/�������� 
	virtual void Serialize(CMemFile& file, BOOL IsLoading=TRUE);
	
	//���������� ����������� ����������
	inline void SetControlVariable(wstring Var){_VariableName = Var;};
	
	inline wstring GetControlVariable(){return _VariableName;};

	//���������� ������ ������ �������� ���������� 
	//(������ �������� �� �������� printf. ��������: %d, %.3f)
	inline void SetFormat(wstring Format){ _Format = Format; }
	//�������� ������� �������� �������
	inline wstring GetFormat(){ return _Format; }

	//���������� ���� ������
	inline void SetTextColor(sRGB Color){SetColor(Color);};
	//�������� ���� ������
	inline sRGB GetTextColor(){return GetColor();};

	//���������� ������(������) ������
	inline int GetHeight(){ return _Font.Height; }
	//�������� ������(������) ������
	inline void SetHeight(int Height){ _Font.Height = Height;}

	//���������� �������� ������ (������, ������, �������������, ������������)
	inline void SetBold(bool Bold) { _Font.Bold = Bold; }
	inline void SetItalic(bool Italic) {_Font.Italic	= Italic; }
	inline void SetStrikeOut(bool StrikeOut) { _Font.StrikeOut	= StrikeOut; }
	inline void SetUnderline(bool Underline) {_Font.Underline	= Underline; }

	//�������� �������� ������ (������, ������, �������������, ������������)
	inline bool GetBold() { return _Font.Bold; }
	inline bool GetItalic() { return _Font.Italic; }
	inline bool GetStrikeOut() { return _Font.StrikeOut; }
	inline bool GetUnderline() { return _Font.Underline; }

	//���������� ��� ������ (��������: Arial, Times New Roman)
	void SetFontName(wstring FontName){_Font.Name = FontName;};
	//�������� ��� ������
	wstring GetFontName(){return _Font.Name;};

	//���������� ����� ��� ��������� ������
	void SetFont(sFont Font){_Font = Font;};
	//�������� ������ �� ���������, ����������� ������������ �����
	sFont& GetFont(){return _Font;};

	//���������
	virtual BOOL OnMouseLButtonUp(sVector Point);
	virtual BOOL OnBtnDown(){return FALSE;};

protected:
	wstring	_VariableName;
	sFont	_Font;
	CRect	_ButtonRect;
	wstring	_Format;
};
