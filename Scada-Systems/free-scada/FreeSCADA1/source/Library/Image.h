#pragma once
/********************************************************************
	������:	        2004/12/08
	������:	        8.12.2004   11:38
	���� � �����: 	d:\Work\Projects\�-����\Source\Library\Image.h
	����������:	    d:\Work\Projects\�-����\Source\Library
	��� �����:	    Image
	����������:	    h
	�����(�):	    ������
    �����(�):       CImage
	
��������:	����� �������� ������� ��� �������� � ���������� ����������� ��/� CMemFile
*********************************************************************/



#include "MemFile.h"

#define IMAGE_FILE_VER			1
#define IMAGE_ID				(DWORD)(((0x30+IMAGE_FILE_VER)<<24)|(0x47<<16)|(0x4D<<8)|0x49)
#define DECODE_IMAGE_VER(val)	(BYTE)(((val>>24) & 0xff)-0x30)


class CImage
{
	friend class CObjImage;
public:
	//Constructor/Destructor
	CImage(void);
	CImage(const CImage& src);
	virtual ~CImage(void);
	CImage& operator=(CImage& src);

	//��������� �����������
	bool Load(CMemFile& file);
	//��������� �����������
	bool Save(CMemFile& file);
	//��������� ����������� ������������ �������
	bool LoadFromStdFile(wstring FileName);

	//���������� ����������� �� DC
	void DrawOnDC(HDC dc);
	//����������� ����������� �� DC � ����������� ������
	void CopyFromDC(HDC dc, CRect& rc);

	inline WORD GetWidth(){return _Width;};
	inline WORD GetHeight(){return _Height;};

protected:
	typedef vector<sRGB> TImgData;
	typedef vector<COLORREF> TColorVector;

	WORD		_Width;		//������
	WORD		_Height;	//������
	TImgData	_Data;		//������
};