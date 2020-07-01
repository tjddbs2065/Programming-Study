#include <Windows.h>
#include <tchar.h>
#include "MySystemError.h"
#include "resource.h"

#define WM_SYNCSHAREMEMORY WM_USER+10
#define SHAREMEMORYNAME _T("ShareMemory")
#define BUF_SIZE 1024
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_SHAREMEMORY_ONE), NULL, DlgProc);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hMap;
	static HWND hEdit;
	static TCHAR* PtrInFile = 0;

	switch (iMsg)
	{
	case WM_SYNCSHAREMEMORY:
		SetWindowText(hEdit, PtrInFile);
		break;
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hwnd, IDC_EDIT);
		SetFocus(hEdit);
		
		hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, SHAREMEMORYNAME);
		if (hMap == INVALID_HANDLE_VALUE) ErrorExit(_T("CreateFileMap"));
		
		PtrInFile = (TCHAR*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
		if (!PtrInFile) ErrorMsg(_T("MapViewOfFile"));


		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT:
			if (HIWORD(wParam) == EN_CHANGE) {
				GetWindowText(hEdit, PtrInFile, BUF_SIZE);
				//프로세스의 이름으로 프로세스의 윈도우 핸들을 알아내서
				HWND hTarget;
				hTarget = FindWindow(NULL, _T("Share Memory Two"));
				if (!hTarget) ErrorMsg(_T("FindWindow"));
				
				SendMessage(hTarget, WM_SYNCSHAREMEMORY, 0, 0);

				//그 윈도우 핸들에게 WM_SYNCSHAREMEMORY를 보낸다.
			}
			break;
		case IDCANCEL:
			if (!UnmapViewOfFile(PtrInFile)) ErrorMsg(_T("UnmapViewOfFile"));
			if (!CloseHandle(hMap))ErrorMsg(_T("CloseHandle - fileMap"));
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}