#include <Windows.h>
#include <tchar.h>
#include "MySystemError.h"
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MMF_FIRST),
		NULL, DlgProc);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	TCHAR fileName[MAX][MAX_PATH] = { 0, };
	static HWND hEdit;
	switch (iMsg)
	{
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hwnd, IDC_EDIT);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_SAVE:
		{
			//1. common dialog box - save
			if (!SelectSaveFile(hwnd, fileName[WRITE]))return 0;
			HANDLE hWrite, hFileMap;
			hWrite = CreateFile(fileName[WRITE], GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hWrite == INVALID_HANDLE_VALUE)ErrorExit(_T("CreateFile - write"));
			
			//2. edit -> Get 하겠지 length -> write할때 사이즈로 잡아준다(CreateFileMapping)
			int textSize = GetWindowTextLength(hEdit);
			hFileMap = CreateFileMapping(hWrite, NULL, PAGE_READWRITE, 0, (textSize + 1) * sizeof(TCHAR), NULL);
			if (hFileMap == INVALID_HANDLE_VALUE)ErrorExit(_T("CreateFile - hFileMap"));

			//3. Pointer connected MapViewOfFile
			TCHAR* PtrInFile = 0;
			PtrInFile = (TCHAR*)MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, NULL);
			if (!PtrInFile) ErrorMsg(_T("'MapViewOfFile"));
			
			textSize = GetWindowText(hEdit, PtrInFile, (textSize + 1) * sizeof(TCHAR));
			PtrInFile[textSize] = 0;
			
			//4. CloseHandle 2개 UnViewOfFile
			if (!UnmapViewOfFile(PtrInFile))ErrorMsg(_T("UnmapViewOfFile"));
			if (!CloseHandle(hFileMap))ErrorMsg(_T("CloseHandle - fileMapping"));
			if (!CloseHandle(hWrite))ErrorMsg(_T("CloseHandle - file"));

		}
			break;
		case IDC_BUTTON_OPEN:
		{
			//1. common dialog -> open select
			if (!SelectOpenFile(hwnd, fileName[READ]))return 0;
			//2. CreateFile
			HANDLE hRead, hFileMap;
			hRead = CreateFile(fileName[READ], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hRead == INVALID_HANDLE_VALUE)ErrorExit(_T("CreateFile"));

			//3. MMF CreateFileMapping
			hFileMap = CreateFileMapping(hRead, NULL, PAGE_READONLY, 0, 0, NULL);
			if (hFileMap == INVALID_HANDLE_VALUE) ErrorExit(_T("CreateFileMapping"));
			TCHAR* PtrInFile = 0;

			//4. Pointer를 MMF에 잡아준다. MapView
			PtrInFile = (TCHAR*)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
			if (!PtrInFile) {
				ErrorMsg(_T("MapViewOfFile"));
				if (!CloseHandle(hFileMap))ErrorMsg(_T("CloseHandle - FileMapping"));
				if (!CloseHandle(hRead))ErrorMsg(_T("CloseHandle - file"));
				return 0;
			}
			//5. 읽은 파일을 Edit에 SetWindowText
			SetWindowText(hEdit, PtrInFile);
			//6. UnMap..
			if (!UnmapViewOfFile(PtrInFile))ErrorMsg(_T("UnmapViewOfFile"));
			//7. CloseHandle 두개 하나는 파일, MMF 핸들

			if (!CloseHandle(hFileMap))ErrorMsg(_T("CloseHandle - FileMapping"));
			if (!CloseHandle(hRead))ErrorMsg(_T("CloseHandle - file"));
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}