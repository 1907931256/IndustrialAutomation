#pragma once
#include "BaseModule.h"
#include "resource.h"

//�����, ������������ ������ �������
typedef CWinTraitsOR<TVS_HASBUTTONS  | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVIF_STATE/*| TVS_DISABLEDRAGDROP*/ > CTreeTraits;
class CModuleTreeView
	: public CWindowImpl<CModuleTreeView, CTreeViewCtrl, CTreeTraits>
{
protected:
	HTREEITEM _RootItem;
	sNode* _ParentNode;
	TNodes _ModuleNodes;//������ � "�������" �������

	HTREEITEM _DragItem; //��������������� ����

	CImageList m_DragImageList; // 
	void FillTree(HTREEITEM Parent, sNode* Node); //���������� ������
	

public:


	BEGIN_MSG_MAP(CModuleTreeView)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_BEGINDRAG, OnBeginDrag)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	
	CModuleTreeView() : _ParentNode(NULL){}

	void InitialUpdate(void);//�������� CImageList ��� ������ � ���������� ������
	void Update(sNode* Selected);//������� � ���������� ������
	void AddModuleNode(sNode* Node){
		_ModuleNodes.push_back(Node); 
	}
	void MoveItem(HTREEITEM From, HTREEITEM To);//��������� ��� From � �������� �������� ��
	bool IsValidToMove(HTREEITEM From, HTREEITEM To);//�������� ����� �� �� ���� ��������� From

	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnBeginDrag(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/); //DragAndDrop
	
};
