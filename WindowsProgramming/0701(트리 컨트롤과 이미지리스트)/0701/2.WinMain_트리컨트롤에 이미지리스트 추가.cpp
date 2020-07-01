#include"MySystemError.h"
#include <CommCtrl.h>
#include"resource.h"
#pragma comment (lib, "comctl32.lib")

void InsertItemRoot(HWND hTreeCtrl);
void InsertItem(HWND hwnd, HWND hTreeCtrl);
void SelectItem(LPARAM lParam, HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect);
void UpdateItem(HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect);
void DeleteItem(HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect);
void DeleteAllItem(HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect);

HINSTANCE hInst;

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	hInst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hTreeCtrl;
	static HTREEITEM hSelect;
	static HIMAGELIST hImageList;

	switch (iMsg)
	{
	case WM_NOTIFY:
		SelectItem(lParam, hwnd, hTreeCtrl, &hSelect);
		break;
	case WM_INITDIALOG:
		InitCommonControls();
		hTreeCtrl = GetDlgItem(hwnd, IDC_TREE_CTRL);

		hImageList = ImageList_LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP), 16, 1, RGB(255,255,255));
		TreeView_SetImageList(hTreeCtrl, hImageList, TVSIL_NORMAL);

		InsertItemRoot(hTreeCtrl);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_UPDATE:
			UpdateItem(hwnd, hTreeCtrl, &hSelect);
			break;
		case IDC_BUTTON_DELETE:
			DeleteItem(hwnd, hTreeCtrl, &hSelect);
			break;
		case IDC_BUTTON_DELETEALL:
			DeleteAllItem(hwnd, hTreeCtrl, &hSelect);
			break;

		case IDC_BUTTON_INSERT:
			InsertItem(hwnd, hTreeCtrl);
			break;

		case IDCANCEL:
			ImageList_Destroy(hImageList);
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}
void InsertItemRoot(HWND hTreeCtrl) {
	//루트노드 "Root"를 만들어 준 int i = 100; i = i;
	TCHAR root[] = { _T("ROOT") };
	TVINSERTSTRUCT tvs = { 0, };
	tvs.hParent = NULL;
	tvs.hInsertAfter = TVI_LAST;
	tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvs.item.pszText = root;
	tvs.item.iImage = 11;
	tvs.item.iSelectedImage = 0;
	TreeView_InsertItem(hTreeCtrl, &tvs);
}
void InsertItem(HWND hwnd, HWND hTreeCtrl) {
	//1. edit -> buffer -> item insert
	TCHAR buffer[MAX_PATH] = { 0, };
	GetDlgItemText(hwnd, IDC_EDIT, buffer, MAX_PATH);
	if (!_tcslen(buffer)) return;
	TVINSERTSTRUCT tvs = { 0, };
	tvs.hParent = TreeView_GetRoot(hTreeCtrl);
	tvs.hInsertAfter = TVI_LAST;
	tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvs.item.pszText = buffer;
	tvs.item.iImage = 3;
	tvs.item.iSelectedImage = 7;
	TreeView_InsertItem(hTreeCtrl, &tvs);
	TreeView_Expand(hTreeCtrl, TreeView_GetRoot(hTreeCtrl), TVE_EXPAND);

	//2. edit -> "", focusing edit
	SetDlgItemText(hwnd, IDC_EDIT, _T(""));
	SetFocus(GetDlgItem(hwnd, IDC_EDIT));
}
void SelectItem(LPARAM lParam, HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect) {
	LPNMHDR hdr = (LPNMHDR)lParam;
	LPNMTREEVIEW ntv = (LPNMTREEVIEW)lParam;
	if (hdr->hwndFrom == hTreeCtrl && hdr->code == TVN_SELCHANGING) {
		//static HTREEITEM hSelect -> 선택된 아이템을 저장
		//이 아이템을 Get해서 -> eidt에 넣어준다.
		TCHAR buffer[MAX_PATH] = { 0, };
		TVITEMEX tvEx = { 0, };
		tvEx.mask = TVIF_TEXT;
		tvEx.hItem = ntv->itemNew.hItem; // 선택된 아이템의 핸들이 넘어온다.
		*hSelect = ntv->itemNew.hItem;
		tvEx.pszText = buffer;
		tvEx.cchTextMax = MAX_PATH;

		TreeView_GetItem(hTreeCtrl, &tvEx);
		SetDlgItemText(hwnd, IDC_EDIT, buffer);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
	}
}

void UpdateItem(HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect) {
	if (!(*hSelect) || *hSelect == TreeView_GetRoot(hTreeCtrl)) {
		MessageBox(hwnd, _T("no 선택 or 루트는 삭제 불가"), _T("Error"), MB_OK);
		return;
	}
	TCHAR buffer[MAX_PATH] = { 0, };
	//1. edit->buffer -> TVITEMEX 데이터를 넣고 hSelect의 핸들까지 넣고
	GetDlgItemText(hwnd, IDC_EDIT, buffer, MAX_PATH);
	//2. TreeView SetItem
	TVITEMEX tvEx = { 0, };
	tvEx.hItem = *hSelect;
	tvEx.mask = TVIF_TEXT;
	tvEx.pszText = buffer;
	tvEx.cchTextMax = MAX_PATH;
	TreeView_SetItem(hTreeCtrl, &tvEx);
	*hSelect = 0;
	//3. edit init, Focusing
	SetDlgItemText(hwnd, IDC_EDIT, _T(""));
	SetFocus(GetDlgItem(hwnd, IDC_EDIT));

}

void DeleteItem(HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect) {
	//HTREEITEM hSelection;
	//hSelection = TreeView_GetSelection(hTreeCtrl);

	//if (!hSelection || hSelection == TreeView_GetRoot(hTreeCtrl)) 
	if (!*hSelect || *hSelect == TreeView_GetRoot(hTreeCtrl))
	{
		MessageBox(hwnd, _T("no 선택 or 루트는 삭제 불가"), _T("Error"), MB_OK);
		return;
	}
	//TreeView_DeleteItem(hTreeCtrl, hSelection);
	TreeView_DeleteItem(hTreeCtrl, *hSelect);
	SetFocus(GetDlgItem(hwnd, IDC_EDIT));
	SetDlgItemText(hwnd, IDC_EDIT, _T(""));
}

void DeleteAllItem(HWND hwnd, HWND hTreeCtrl, HTREEITEM* hSelect) {
	TreeView_DeleteAllItems(hTreeCtrl);
	hSelect = 0;
	InsertItemRoot(hTreeCtrl);
	SetFocus(GetDlgItem(hwnd, IDC_EDIT));
	SetDlgItemText(hwnd, IDC_EDIT, _T(""));
}