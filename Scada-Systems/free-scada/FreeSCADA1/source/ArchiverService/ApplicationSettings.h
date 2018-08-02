#pragma once

#ifdef GetUserName
	#undef GetUserName
#endif

namespace Helpers
{
	class CApplicationSettings
		: public CSingleton<CApplicationSettings>
	{
	public:
		//��������� �������� � ������� � �������������� ����
		CString GetDBUserName();	//�������� ����� ������������ ��� ����� � ��
		CString GetDBUserPass();	//�������� ������ ������������ ��� ����� � ��

	protected:
		//������ � �������
		struct sUserPass
		{
			wchar_t User[128];
			wchar_t Password[128];
		};
		HelpersLib::CCfgReg _reg;

	protected:
		CApplicationSettings(void);
		~CApplicationSettings(void);
		DEF_SINGLETON(CApplicationSettings);

		//������������ ���������
		BOOL EncodeUserPass(sUserPass SrcData, vector<BYTE> &DstData);
		//������������ ���������
		BOOL DecodeUserPass(vector<BYTE> &SrcData, sUserPass& DstData);
	};
}