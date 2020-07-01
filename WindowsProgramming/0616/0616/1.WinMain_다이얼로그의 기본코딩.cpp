#include <Windows.h>
#include <tchar.h>
#include <ShlObj.h>

#include "resource.h"
BOOL SelectSaveFile(HWND hwnd, TCHAR* file);
BOOL SelectOpenFile(HWND hwnd, TCHAR* file);
BOOL SelectFolder(TCHAR* folder);
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_COMMON),NULL, DlgProc);

	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR buffer[MAX_PATH] = { 0, };

	switch (iMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_FILEOPEN:
			if (!SelectOpenFile(hwnd, buffer)) return 0;
			SetDlgItemText(hwnd, IDC_STATIC_FILEOPEN, buffer);
			break;
		case IDC_BUTTON_FILESAVE:
			if (!SelectSaveFile(hwnd, buffer)) return 0;
			SetDlgItemText(hwnd, IDC_STATIC_FILESAVE, buffer);
			break;
		case IDC_BUTTON_FOLDER:
			if (!SelectFolder(buffer)) return 0;
			SetDlgItemText(hwnd, IDC_STATIC_FOLDER, buffer);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}

BOOL SelectFolder(TCHAR* folder) {
	//folder -> shell (프로그램을 실행할 수 있는 모든 것)
	BOOL result = FALSE;
	BROWSEINFO bi = { 0, };
	bi.lpszTitle = _T("Select [FOLDER] what you want to");
	LPITEMIDLIST lpItemIDList = 0;
	lpItemIDList = SHBrowseForFolder(&bi);
	if (!lpItemIDList) return FALSE;
	result = SHGetPathFromIDList(lpItemIDList, folder);
	if (!result) return FALSE;
	result = TRUE;

	return result;
}
BOOL SelectSaveFile(HWND hwnd, TCHAR* file) {
	BOOL result = FALSE;
	OPENFILENAME of = { 0, };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("모든파일(*.*)\0*.*\0");
	of.lpstrFile = file;
	of.lpstrInitialDir = _T(".");
	of.nMaxFile = MAX_PATH;
	if (GetSaveFileName(&of))
		result = TRUE;
	return result;
}
BOOL SelectOpenFile(HWND hwnd, TCHAR* file) {
	BOOL result = FALSE;
	OPENFILENAME of = { 0, };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("모든파일(*.*)\0*.*\0");
	of.lpstrFile = file;
	of.lpstrInitialDir = _T(".");
	of.nMaxFile = MAX_PATH;
	if (GetSaveFileName(&of))
		result = TRUE;
	return result;
}