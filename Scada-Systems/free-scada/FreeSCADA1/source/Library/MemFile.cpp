#include "common.h"
#include "memfile.h"


size_t CMemFile::ReadBlock(void* Buffer, size_t Count)
{
	size_t ReadBytes; //������� ���� ������
	
	if(_Pos >= _Size)
		return 0; //�� ��������� � ����� �����

	//�� ��������� ������������� ����� ���� ���������� ������ �����
	if((_Pos + Count) <= _Size)
		ReadBytes = Count; //��� ���������. ������.
	else
		ReadBytes = _Size - _Pos; // ������ ������� �� ����� �����

	//�������� � ������
	memcpy(Buffer, &_Buffer[_Pos], ReadBytes);

	//���������� ������ �������
	_Pos += ReadBytes;

	//���������� ���-�� ����������� ����
	return ReadBytes;
}

void CMemFile::WriteBlock(void* Buffer, size_t Count)
{
	//�� ���� �� ��������� �����?
	if(_Pos + Count >= _Size)
	{
		//����. �����������.
		_Buffer.resize(_Pos+Count + 1);
		_Size = _Pos+Count;
	}

	//�������� �� ����������� ������ � �������� �����
	memcpy(&_Buffer[_Pos], Buffer, Count);

	//�������� ������� �������
	_Pos += Count;
}

void CMemFile::Seek(UINT Offset, UINT From)
{
	if(From == SEEK_SET)
		_Pos = Offset; //�������� ������������ ������
	if(From == SEEK_CUR)
		_Pos += Offset; //�������� ������� �������
	if(From == SEEK_END)
		_Pos = _Size - Offset - 1; //�������� ������������ �����

	//�� ����������� �� �� �� ������� �����?
	if(_Pos >= _Size && _Size != 0)
		_Pos = _Size - 1;
}

CMemFile& CMemFile::operator<<(const std::wstring& str)
{
	size_t count = str.size();
	WriteBlock(static_cast<void*>(&count), sizeof(size_t));
	WriteBlock((void*)str.c_str(), count*sizeof(std::wstring::value_type));
	return *this;
}

CMemFile& CMemFile::operator>>(std::wstring& str)
{
	size_t count;
	ReadBlock(static_cast<void*>(&count), sizeof(size_t));
	std::wstring::value_type *tmp = new std::wstring::value_type[count+1];
	tmp[count] = 0;
	ReadBlock((void*)tmp, count*sizeof(std::wstring::value_type));
	str = tmp;
	delete[] tmp;
	return *this;
}