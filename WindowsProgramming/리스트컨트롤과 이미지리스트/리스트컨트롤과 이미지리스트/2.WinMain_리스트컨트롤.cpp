#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "resource.h"
#pragma comment (lib, "comctl32.lib")

void UpdateItem(HWND hwnd, HWND hListCtrl, int* selection);
void DeleteAllItem(HWND hListCtrl, int* selection);
void DeleteItem(HWND hListCtrl, int* selection);
void InsertItemWhenEnterKey(WPARAM wParam, HWND hwnd, HWND hListCtrl);
void InsertColumns(HWND hListCtrl);
void InsertItems(HWND hwnd, HWND hListCtrl);
void InitEditCtrl(HWND hwnd);
void SelectedItem(LPNMLISTVIEW nlv, HWND hwnd, HWND hListCtrl, int* selection);
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_LISTCTRL), NULL, DlgProc);

	return 0;
}
enum { 이름, 나이, 생년월일 };
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hListCtrl;
	static int selection = -1;
	switch (iMsg)
	{
	case WM_NOTIFY:
	{
		LPNMHDR hdr = (LPNMHDR)lParam;
		LPNMLISTVIEW nlv = (LPNMLISTVIEW)lParam;
		if (hdr->hwndFrom == hListCtrl && hdr->code == LVN_ITEMCHANGED) {
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SelectedItem(nlv, hwnd, hListCtrl, &selection);
			}
		}
	}
		break;
	case WM_INITDIALOG:
		InitCommonControls();
		hListCtrl = GetDlgItem(hwnd, IDC_LIST);
		InsertColumns(hListCtrl);

		SetFocus(GetDlgItem(hwnd, IDC_EDIT_NAME));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_UPDATE:
			UpdateItem(hwnd, hListCtrl, &selection);
			InitEditCtrl(hwnd);
			break;
		case IDC_BUTTON_DELETE:
			DeleteItem(hListCtrl, &selection);
			InitEditCtrl(hwnd);
			break;
		case IDC_BUTTON_DELETEALL:
			DeleteAllItem(hListCtrl, &selection);
			InitEditCtrl(hwnd);
			break;
		case IDC_EDIT_BIRTH:
			InsertItemWhenEnterKey(wParam, hwnd, hListCtrl);
			break;
		case IDC_BUTTON_INSERT:
			InsertItems(hwnd, hListCtrl);
			InitEditCtrl(hwnd);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}

void InsertColumns(HWND hListCtrl) {
	TCHAR column[3][MAX_PATH] = { _T("이름"), _T("나이"), _T("생년월일") };
	LVCOLUMN lvCol = { 0, };
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
	lvCol.fmt = LVCFMT_CENTER;
	lvCol.cx = 120;
	lvCol.iSubItem = 이름;
	lvCol.pszText = column[이름];
	ListView_InsertColumn(hListCtrl, 이름, &lvCol);

	lvCol.cx = 50;
	lvCol.iSubItem = 나이;
	lvCol.pszText = column[나이];
	ListView_InsertColumn(hListCtrl, 나이, &lvCol);

	lvCol.cx = 170;
	lvCol.iSubItem = 생년월일;
	lvCol.pszText = column[생년월일];
	ListView_InsertColumn(hListCtrl, 생년월일, &lvCol);
}

void InsertItems(HWND hwnd, HWND hListCtrl) {
	//edit -> buffer
	TCHAR buffer[3][MAX_PATH] = { 0, };
	GetDlgItemText(hwnd, IDC_EDIT_NAME, buffer[이름], MAX_PATH);
	GetDlgItemText(hwnd, IDC_EDIT_AGE, buffer[나이], MAX_PATH);
	GetDlgItemText(hwnd, IDC_EDIT_BIRTH, buffer[생년월일], MAX_PATH);

	//buffer -> listview
	int count = ListView_GetItemCount(hListCtrl);
	LVITEM lvItem = { 0, };
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = count;
	lvItem.iSubItem = 이름;
	lvItem.pszText = buffer[이름];
	ListView_InsertItem(hListCtrl, &lvItem); //한 줄 - 아이템

	lvItem.iSubItem = 나이;
	lvItem.pszText = buffer[나이];
	ListView_SetItem(hListCtrl, &lvItem); //한 줄 - 아이템

	lvItem.iSubItem = 생년월일;
	lvItem.pszText = buffer[생년월일];
	ListView_SetItem(hListCtrl, &lvItem); //한 줄 - 아이템

}
void InitEditCtrl(HWND hwnd) {
	//edit -> initialize
	SetDlgItemText(hwnd, IDC_EDIT_NAME, _T(""));
	SetDlgItemText(hwnd, IDC_EDIT_AGE, _T(""));
	SetDlgItemText(hwnd, IDC_EDIT_BIRTH, _T(""));
	//edit - name focusing
	SetFocus(GetDlgItem(hwnd, IDC_EDIT_NAME));
}

void InsertItemWhenEnterKey(WPARAM wParam, HWND hwnd, HWND hListCtrl) {
	if (HIWORD(wParam) != EN_CHANGE) return;
	else if (HIWORD(wParam) == EN_CHANGE) {
		TCHAR buffer[3][MAX_PATH] = { 0, };
		GetDlgItemText(hwnd, IDC_EDIT_BIRTH, buffer[생년월일], MAX_PATH);
		int len = _tcslen(buffer[생년월일]);
		if (buffer[생년월일][len - 2] == VK_RETURN) {
			buffer[생년월일][len - 2] = 0;
			GetDlgItemText(hwnd, IDC_EDIT_NAME, buffer[이름], MAX_PATH);
			GetDlgItemText(hwnd, IDC_EDIT_AGE, buffer[나이], MAX_PATH);
			GetDlgItemText(hwnd, IDC_EDIT_BIRTH, buffer[생년월일], MAX_PATH);

			//buffer -> listview
			int count = ListView_GetItemCount(hListCtrl);
			LVITEM lvItem = { 0, };
			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = count;
			lvItem.iSubItem = 이름;
			lvItem.pszText = buffer[이름];
			ListView_InsertItem(hListCtrl, &lvItem); //한 줄 - 아이템

			lvItem.iSubItem = 나이;
			lvItem.pszText = buffer[나이];
			ListView_SetItem(hListCtrl, &lvItem); //한 줄 - 아이템

			lvItem.iSubItem = 생년월일;
			lvItem.pszText = buffer[생년월일];
			ListView_SetItem(hListCtrl, &lvItem); //한 줄 - 아이템
			InitEditCtrl(hwnd);
		}
	}
}
void SelectedItem(LPNMLISTVIEW nlv, HWND hwnd, HWND hListCtrl, int* selection) {
	*selection = nlv->iItem; // 현재 선택된 아이템(한 줄)의 인덱스
	TCHAR buffer[3][MAX_PATH] = { 0 };
	//listview -> buffer
	ListView_GetItemText(hListCtrl, *selection, 이름, buffer[이름], MAX_PATH);
	ListView_GetItemText(hListCtrl, *selection, 나이, buffer[나이], MAX_PATH);
	ListView_GetItemText(hListCtrl, *selection, 생년월일, buffer[생년월일], MAX_PATH);
	
	//buffer ->edit에 안착
	SetDlgItemText(hwnd, IDC_EDIT_NAME, buffer[이름]);
	SetDlgItemText(hwnd, IDC_EDIT_AGE, buffer[나이]);
	SetDlgItemText(hwnd, IDC_EDIT_BIRTH, buffer[생년월일]);

	//edit name - focusing
	SetFocus(GetDlgItem(hwnd, IDC_EDIT_NAME));
}

void DeleteAllItem(HWND hListCtrl, int* selection) {
	ListView_DeleteAllItems(hListCtrl);
	*selection = -1;
}
void DeleteItem(HWND hListCtrl, int* selection) {

	ListView_DeleteItem(hListCtrl, *selection);
	*selection = -1;
}

void UpdateItem(HWND hwnd, HWND hListCtrl, int* selection) {
	//1. edit-> buffer
	TCHAR buffer[3][MAX_PATH] = { 0, };
	GetDlgItemText(hwnd, IDC_EDIT_NAME, buffer[이름], MAX_PATH);
	GetDlgItemText(hwnd, IDC_EDIT_AGE, buffer[나이], MAX_PATH);
	GetDlgItemText(hwnd, IDC_EDIT_BIRTH, buffer[생년월일], MAX_PATH);

	//2. buffer->listview set
	ListView_SetItemText(hListCtrl, *selection, 이름, buffer[이름]);
	ListView_SetItemText(hListCtrl, *selection, 나이, buffer[나이]);
	ListView_SetItemText(hListCtrl, *selection, 생년월일, buffer[생년월일]);

	//3. selection = -1
	*selection = -1;

	//4. InitEditCtrl
}