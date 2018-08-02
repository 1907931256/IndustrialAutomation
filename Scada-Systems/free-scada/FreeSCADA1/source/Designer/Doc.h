#pragma once
/********************************************************************
	������:	        2005/02/09
	������:	        9.2.2005   17:09
	���� � �����: 	c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer\Doc.h
	����������:	    c:\Work\Projects\Visual Studio Projects\�-����\Source\Designer
	��� �����:	    Doc
	����������:	    h
	�����(�):	    ������
    �����(�):       CDoc
	
��������:	����� ��������� ������ � ���������-�����������, ����������� �������� 
			� �������, ����������� �������
*********************************************************************/



//������� �������� ��� ���������
enum enCreatePrimitive
{
	P_EMPTY,
	P_POLYLINE,
	P_RECTANGLE,
	P_ELLIPSE,
	P_IMAGE,
	P_TEXT,
	P_BUTTON,
	P_INPUT,
	P_SOUND,
	P_GRAPH
};



class CDoc
	: public DVF::CBaseDocument
{
public:
	enCreatePrimitive	m_CurrentCreatingPrimitive; //������� �������� ��� ���������
	CArchiveManager		m_Archive; //�����
	bool				m_ShowGrid;

	//�������� ������ ���������
	void CreateNewPrimitive(enCreatePrimitive ID, CPoint pt, BOOL UseLastSettings=FALSE);
	//�������� �������
	bool LoadProject(wstring FileName);
	//���������� �������
	bool SaveProject(wstring FileName);
	//�������� ������ �������
	bool NewProject();
	//�������� ����� �����
	bool NewSchema(wstring SchemaName);
	//�������� �� ���� ���������
	bool IsFileTemp(){ return !_TempFile.empty(); }
	
	//�������� �������� ���� ����������� ������
	bool GetImageNames(TStrings& Names);
	//�������� �������� ���� ������ ������
	bool GetSoundNames(TStrings& Names);
	//�������� �������� ���� ���� �������
	bool GetSchemaNames(TStrings& Names);
	//��������� ���������� �������
	bool LoadVariables();
	//��������� ���������� �������
	bool SaveVariables();
	//��������� ��������� �������
	bool LoadProjectSettings();
	//��������� ��������� �������
	bool SaveProjectSettings();
	//�������� �������� ������� �����
	wstring GetCurrentSchemaName(){ return _CurrentSchema; }
	//���������� �������� ������� �����
	void SetCurrentSchemaName(wstring Schema){ _CurrentSchema = Schema; }
	//������������� ������� �����
	bool RenameCurrentSchema(wstring NewSchemaName);
	//������� �����
	void DeleteSchema(wstring SchemaName);
	//��������� ������� �����
	void SaveCurrentSchema();
	//��������� ������� �����
	void LoadCurrentSchema();
	//���������� ���� ��������� �������
	void SetModifiedFlag(bool Modified = true){ _IsModified = Modified; }
	
	//�������� �������� �����
	sSchemaSettings GetSchemaSettings(){ return _Settings; }
	//���������� ��������� �����
	void SetSchemaSettings(sSchemaSettings Settings){ _Settings = Settings; }
	//�������� ��������� �������
	sProjectSettings GetProjectSettings(){return _ProjectSettings; }
	//���������� ��������� �������
	void SetProjectSettings(sProjectSettings ProjectSettings){_ProjectSettings = ProjectSettings; }

	CDoc(void);
	~CDoc(void);
protected:
	wstring _TempFile; //�������� ���������� �����
	wstring _CurrentSchema; //�������� ������� �����
	sSchemaSettings _Settings; //��������� �����
	sProjectSettings _ProjectSettings; //��������� �������

	bool _IsModified; //���� ����������� ���������

};
