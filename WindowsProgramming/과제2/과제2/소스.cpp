#include <Windows.h>
#include <tchar.h>
#include "resource.h"

void FindFileList(HWND hwnd, TCHAR* path);
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DlgProc);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static TCHAR path[MAX_PATH] = _T("C:/test/");
	HWND hTree;
	switch (iMsg)
	{
	case WM_INITDIALOG:
		hTree = GetDlgItem(hwnd, IDC_TREE);
		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_FOLDSEARCH:	
			FindFileList(hwnd, path);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}

void FindFileList(HWND hwnd, TCHAR* path) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR buffer[MAX_PATH] = { 0, }, files[1000] = { 0, };
	hFind = FindFirstFile(L"C:\\test\\*.*", &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		wsprintf(buffer, _T("FindFirstFile Failed (%d)"), GetLastError());
		MessageBox(hwnd, buffer, _T("!!"), MB_OK);
		return;
	}

	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
			wsprintf(files, _T("%s %s\n"),files, FindFileData.cFileName);
		}
		else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			wsprintf(files, _T("%s %s\tDIR\n"), files, FindFileData.cFileName);
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
	MessageBox(hwnd, files, _T(""), MB_OK);
}