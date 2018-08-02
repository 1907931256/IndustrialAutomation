#include "common.h"
#include "archivemanager.h"
#include "MemFile.h"
#include "ObjImage.h"
#include "ActionMenager.h"
#include "VariableMenager.h"


CArchiveManager::CArchiveManager()
{
}

CArchiveManager::CArchiveManager(wstring FileName)
: _FileName(FileName)
{
}

CArchiveManager::~CArchiveManager(void)
{
}

//�������� ������ �� enTypeID
wstring CArchiveManager::StringFromID(UINT id)
{
	switch(id)
	{
	case _RECTANGLE: return L"Rectangles";
	case _POLYLINE : return L"Polylines";
	case _ELLIPSE  : return L"Ellipses";
	case _IMAGE	   : return L"Images";
	case _TEXT	   : return L"Text";
	case _BUTTON   : return L"Button";
	case _INPUT	   : return L"Input";
	case _ACTION   : return L"Actions";
	case _VARIABLE : return L"Variables";
	case _SOUND	   : return L"Sounds";
	case _GRAPH	   : return L"Graphics";

	}
	return wstring();
}

//��������� �������� ��� �������� ����� SchemaName 
bool CArchiveManager::SaveActions(wstring SchemaName)
{
	try
	{
		CMemFile *file=NULL;
		//�������� ������ ���� ����� ����������� ��������
		wstring path = GetSpecialFolder(SF_SCHEMAS)+ L"\\" + SchemaName + L"\\" + StringFromID(_ACTION);
		//������� ������ CMemfile
		if(!CreateMemFile(path, &file))
			return false;
		//���������� ������ �� �ActionMenager � �MemFile
		CActionMenagerPtr mng;
		mng->Serialize(*file, FALSE);

		//���������� ������ �� �MemFile � ����� � ����������� ������ �MemFile
		//��������� � ������� CreateMemFile()
		if(!WriteAndFreeMemFile(file))
			return false;
	}
	catch(...){return false;}
	return true;
}

//��������� ���������� �������
bool CArchiveManager::LoadVariables()
{
	try
	{
		//�������� ������ ���� ����� ����������� ���������� �������
		wstring path = GetSpecialFolder(SF_VARIABLES) + L"\\" + StringFromID(_VARIABLE);
		//������� ������ CMemfile � �������� � ���� ������ �� ������
		CMemFile *file=NULL;
		if(!OpenMemFile(path, &file))
			return false;
		//��������� ���������� �� CMemFile � CVariableMenager
		CVariableMenagerPtr mng;
		mng->Serialize(*file, TRUE);

		//����������� ������ CMemFile ��������� � ������� OpenMemFile()
		if(!FreeMemFile(file))
			return false;
	}
	catch(...){return false;}
	return true;
}

//��������� ��������� �������
bool CArchiveManager::SaveVariables()
{
	try
	{
		
		CMemFile *file=NULL;
		//�������� ������ ���� � �����, ����������� ���������� �������
		wstring path = GetSpecialFolder(SF_VARIABLES)+ L"\\"  + StringFromID(_VARIABLE);

		//�������� ������� ������ CMemFile
		if(!CreateMemFile(path, &file))
			return false;
		//���������� ������ �� CVariableMenager � CMemFile
		CVariableMenagerPtr mng;
		mng->Serialize(*file, FALSE);
		
		//���������� ������ �� CMemFile � ����� � ����������� ������ CMemFile
		//�������� � CreateMemFile()
		if(!WriteAndFreeMemFile(file))
			return false;
	}
	catch(...){return false;}
	return true;

}

//�������� �������� ��� �������� �� ����� SchemaName
bool CArchiveManager::LoadActions(wstring SchemaName)
{
	try
	{
		//�������� ������ ���� � �����, ����������� ��������
		wstring path = GetSpecialFolder(SF_SCHEMAS) + L"\\" + SchemaName + L"\\" + StringFromID(_ACTION);
		//������� ������ CMemfile � �������� � ���� ������ �� ������
		CMemFile *file=NULL;
		if(!OpenMemFile(path, &file))
			return false;
		//��������� �������� �� MemFile � ActionMenager
		CActionMenagerPtr mng;
		mng->Serialize(*file);

		//����������� ������ CMemFile ��������� � ������� OpenMemFile()
		if(!FreeMemFile(file))
			return false;
	}
	catch(...){return false;}
	return true;
}


//���������� �������� �� ����� SchemaName ������� ��� TypeID
bool CArchiveManager::SaveSchemaObj(wstring SchemaName, UINT TypeID)
{
	try
	{
		typedef list<CObject*> TObjList;
		typedef TObjList::iterator TObjListIt;
		TObjList ObjList;

		//������� ������ �� �������� ������������ � CObjectMenager
		//������� ��� TypeID
		for(TObjListIt it = _Menager->_Objects.begin(); 
			it != _Menager->_Objects.end(); it++)
		{
			if((*it)->GetTypeID()==TypeID)
				ObjList.push_back(*it);
		}

		DWORD count = (DWORD)ObjList.size();
		
		wstring path = GetSpecialFolder(SF_SCHEMAS)+ L"\\" + SchemaName + L"\\" + StringFromID(TypeID);
		
		//�������� ������� CMemFile
		CMemFile *file=NULL;
		if(!CreateMemFile(path, &file))
			return false;
		//���������� ���������� �������� � CMemfile
		(*file)<<count;
		//��������� ������� � CMemFile
		for(TObjListIt it=ObjList.begin(); it!=ObjList.end(); it++)
		{
			(*it)->Serialize(*file, FALSE);
		}
		//���������� CMemFile � ����� � ����������� CMemFile
		if(!WriteAndFreeMemFile(file))
			return false;
	}
	catch(...){return false;}

	return true;
}

//���������� �������� � �������� ����� 
bool CArchiveManager::SaveSchema(wstring SchemaName, sSchemaSettings Settings)
{
	SaveSchemaSettings(SchemaName,Settings);
	SaveAllObjects(SchemaName);
	return true;
}

//�������� �������� �����
bool CArchiveManager::LoadSchemaSettings(wstring SchemaName, sSchemaSettings& Settings)
{
	try
	{
		wstring path = GetSpecialFolder(SF_SCHEMAS) + L"\\" + SchemaName + L"\\" + L"Settings";
		CMemFile *file=NULL;
		if(!OpenMemFile(path, &file))
		{
			sSchemaSettings stgs;
			Settings = stgs;
			return false;
		}

		(*file)>>Settings.FixedSize;
		(*file)>>Settings.HasBackgrd;
		(*file)>>Settings.cx;
		(*file)>>Settings.cy;
		(*file)>>Settings.BackGrdName;
		(*file)>>Settings.StretchBackGrd;
		(*file)>>Settings.BackGrdColor;


		FreeMemFile(file);
	}
	catch(...){return false;}
	return true;
}

//���������� �������� �����
bool CArchiveManager::SaveSchemaSettings(wstring SchemaName, sSchemaSettings Settings)
{
	try
	{
		wstring path = GetSpecialFolder(SF_SCHEMAS) + L"\\" + SchemaName + L"\\" + L"Settings";
		CMemFile *file=NULL;

		if(!CreateMemFile(path, &file))
			return false;

		(*file)<<Settings.FixedSize;
		(*file)<<Settings.HasBackgrd;
		(*file)<<Settings.cx;
		(*file)<<Settings.cy;
		(*file)<<Settings.BackGrdName;
		(*file)<<Settings.StretchBackGrd;
		(*file)<<Settings.BackGrdColor;

		if(!WriteAndFreeMemFile(file))
			return false;
	}
	catch(...){return false;}
	return true;
}

//�������� �������� �������
bool CArchiveManager::LoadProjectSettings(sProjectSettings& Settings)
{
	try
	{
		wstring path = L"Settings";
		CMemFile *file=NULL;
		if(!OpenMemFile(path, &file))
			return false;

		(*file)>>Settings.InitialSchema;
		(*file)>>Settings.IntervalOPC;

	}
	catch(...){return false;}
	return true;
}

//���������� �������� �������
bool CArchiveManager::SaveProjectSettings(sProjectSettings Settings)
{
	try
	{
		wstring path = L"Settings";
		CMemFile *file=NULL;

		if(!CreateMemFile(path, &file))
			return false;

		(*file)<<Settings.InitialSchema;
		(*file)<<Settings.IntervalOPC;

		if(!WriteAndFreeMemFile(file))
			return false;
	}
	catch(...){return false;}
	return true;
}

//���������� ���� �������� �����
bool CArchiveManager::SaveAllObjects(wstring SchemaName)
{
	SaveSchemaObj(SchemaName, _RECTANGLE);
	SaveSchemaObj(SchemaName, _POLYLINE);
	SaveSchemaObj(SchemaName, _ELLIPSE);
	SaveSchemaObj(SchemaName, _IMAGE);
	SaveSchemaObj(SchemaName, _TEXT);
	SaveSchemaObj(SchemaName, _BUTTON);
	SaveSchemaObj(SchemaName, _INPUT);
	SaveSchemaObj(SchemaName, _SOUND);
	SaveSchemaObj(SchemaName, _GRAPH);

	SaveActions(SchemaName);
	
	return true;
}
 
//�������� ���� �������� �� CObjectMenager � ���� �������� �� CActionMenager
bool CArchiveManager::RemoveAllObjects()
{
	_Menager->RemoveAll();
	CActionMenagerPtr mng;
	mng->RemoveAll();
	return true;
}

//�������� ������ ������
bool CArchiveManager::CreateNewArchive()
{
	if(_FileName.empty())
		return false;

	CZipArchive arch;
	arch.Open((LPCTSTR)_FileName.c_str(),  CZipArchive::zipCreate);
	arch.Close();
	return true;
}

//�������� ������ ������ �� ����� Fldr
bool CArchiveManager::GetDirectoryFileList(TStrings& Names, enSpecialFolder Fldr)
{
	if(Fldr != SF_IMAGES && Fldr != SF_SCHEMAS && Fldr != SF_SOUNDS)
		return false;

	CZipArchive arch;
	CZipMemFile mf;
	try
	{
		if(PathFileExists(_FileName.c_str()) == false)
			return false;
		//��������� �����
		arch.Open(_FileName.c_str(), CZipArchive::zipOpenReadOnly);

		//�������� ������ ���� ������ � ������
		CZipWordArray  array;
		arch.FindMatches(L"*", array, true);

		int size = array.GetSize();

		//�������� �������� �������� ������ �� ����� Fldr
		for(int i = 0; i< size; i++)
		{
			CZipFileHeader header;
			arch.GetFileInfo(header, array[i]);
			wstring str = header.GetFileName();	
			//������������� ������ ���������� ����� Fldr
			if(str.find(GetSpecialFolder(Fldr)+L"\\") != 0)
				continue; //��� ������ �����
			wstring::iterator it = str.begin();
			while(it!=str.end()&&*it != L'\\'  ) it++;
			if(it!=str.end())
				it++;
			wstring name;
			while(it!=str.end()&&*it != L'\\' )
			{
				name += *it;
				it++;
			}
			//��������� ������������
			TStrings::iterator find = 
				find_if(Names.begin(), Names.end(), sFindName(name));
			if(find == Names.end() && !name.empty()) 
			{
				Names.push_back(name);
			}
		}
		sort(Names.begin(), Names.end());
	}
	catch (...){};

	arch.Close();
	return true;
}


//�������� CMemFile
bool CArchiveManager::CreateMemFile(wstring FileName, CMemFile** file)
{
	CZipArchive arch;
	CZipMemFile mf;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;
		//
		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		int index = arch.FindFile((LPCTSTR)FileName.c_str());
		//���� ��� ���������� � ������, ������� ���
		if(index != -1) 
			arch.DeleteFileW(index);
		
		//������� ����� CMemFile
		*file = new CMemFile(FileName, this);
		if(*file == NULL)
			return false;
	}
	catch(...){return false;};

	mf.Close();
	arch.Close();

	return true;
}

//�������� ���������� �� ����  � ������
bool CArchiveManager::IsFileExists(wstring FileName)
{
	CZipArchive arch;
	CZipMemFile mf;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;

		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		int index = arch.FindFile((LPCTSTR)FileName.c_str());
		mf.Close();
		arch.Close();
		return index != -1;
	}
	catch(...){return false;};
	return false;
}

//������� CMemFile � ��������� � ���� ������ �� ������
bool CArchiveManager::OpenMemFile(wstring FileName, CMemFile** file)
{
	CZipArchive arch;
	CZipMemFile mf;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;

		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		int index = arch.FindFile((LPCTSTR)FileName.c_str());
		if(index == -1) return false;

		arch.ExtractFile(index, mf);

		*file = new CMemFile(FileName, this);
		if(*file == NULL)
			return false;

		vector<BYTE> tmp;
		tmp.resize(mf.GetLength());
		mf.Read(&tmp[0], mf.GetLength());
		(*file)->WriteBlock(&tmp[0], (UINT)tmp.size());
		(*file)->Seek(0, SEEK_SET);
	}
	catch(...){return false;};

	mf.Close();
	arch.Close();

	return true;
}

//���������� ������ �� CMemFile � ����� � ������� ������ CMemFile
bool CArchiveManager::WriteAndFreeMemFile(CMemFile* file)
{
	if(file == NULL)
		return false;

	CZipArchive arch;
	CZipMemFile mf;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;

		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		int index = arch.FindFile(file->GetFileName().c_str());
		//���� ���� � ����� ������ ��� ���� � ������, ������� ���
		if(index != -1)
			arch.DeleteFileW(index);
		
		file->Seek(0,SEEK_SET);
		vector<BYTE> tmp(file->GetSize());
        file->ReadBlock(&tmp[0], file->GetSize());
		mf.Write(&tmp[0], (UINT)tmp.size());
		//���������� ������ � �����
		arch.AddNewFile(mf, file->GetFileName().c_str(), Z_BEST_COMPRESSION);
		delete file;
		file = NULL;
	}
	catch(...)
	{
		if(file)
		{
			delete file;
			file = NULL;
		}
		return false;
	};

	mf.Close();
	arch.Close();

	return true;
}

bool CArchiveManager::FreeMemFile(CMemFile* file)
{
	if(file == NULL)
		return false;

	delete file;
	return true;
}

bool CArchiveManager::WriteAsAndFreeMemFile(wstring FileName, CMemFile* file)
{
	if(file == NULL)
		return false;

	CZipArchive arch;
	CZipMemFile mf;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;

		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		int index = arch.FindFile(FileName.c_str());
		if(index != -1)
			arch.DeleteFileW(index);

		file->Seek(0,SEEK_SET);
		vector<BYTE> tmp(file->GetSize());
		file->ReadBlock(&tmp[0], file->GetSize());
		mf.Write(&tmp[0], (UINT)tmp.size());

		arch.AddNewFile(mf, FileName.c_str(), Z_BEST_COMPRESSION);
		delete file;
		file = NULL;
	}
	catch(...)
	{
		if(file)
		{
			delete file;
			file = NULL;
		}
		return false;
	};

	mf.Close();
	arch.Close();

	return true;
}

//������� ���� �� ������
bool CArchiveManager::DeleteFile(wstring FileName)
{
	CZipArchive arch;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;

		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		int index = arch.FindFile(FileName.c_str());
		if(index != -1)
			arch.DeleteFileW(index);
	}
	catch(...)
	{
		return false;
	};

	arch.Close();
	return true;
}

//�������� ��������� �������� ����� �� �� ID
wstring CArchiveManager::GetSpecialFolder(enSpecialFolder Fldr)
{
	switch(Fldr) 
	{
	case SF_SCHEMAS: return L"Schemas";
	case SF_IMAGES: return L"Images";
	case SF_SOUNDS: return L"Sounds";
	case SF_VARIABLES: return L"Variables";
	}
	return L"";
}

//������� ����� � ������ FolderName ����������� � ����� Fldr
bool CArchiveManager::DeleteFolder(enSpecialFolder Fldr, wstring FolderName)
{
	CZipArchive arch;

	try
	{
		if(!PathFileExists(_FileName.c_str()))
			return false;
		
		FolderName =  GetSpecialFolder(Fldr) + L"\\" + FolderName;
		arch.Open((LPCTSTR)_FileName.c_str(), CZipArchive::zipOpen);
		CZipWordArray array;
		arch.FindMatches( L"*", array, false);
		int count = array.GetSize();

		TStrings Names;
		for(int i = 0; i< count; i++)
		{
			CZipFileHeader header;
			arch.GetFileInfo(header, array[i]);
			wstring str = header.GetFileName();

			if(str.substr(0, FolderName.length()) == FolderName)
			{
				Names.push_back(str);
			}
		}

		for(TStrings::iterator it = Names.begin(); it != Names.end(); it++)
		{
			int index = arch.FindFile(it->c_str());
			if(index != -1)
				arch.DeleteFileW(index);
		}
	}
	catch(...)
	{
		return false;
	}

	arch.Close();
	return true;
}

//�������� �������� 
bool CArchiveManager::GetImage(wstring ImageName, ::CImage& Image)
{
	try
	{
		wstring path = GetSpecialFolder(SF_IMAGES) + L"\\" + ImageName;

		CMemFile *file=NULL;
		if(!OpenMemFile(path, &file))
			return false;

		::CImage img;
		img.Load(*file);
		FreeMemFile(file);

		Image = img;
	}
	catch(...){return false;}

	return true;
}