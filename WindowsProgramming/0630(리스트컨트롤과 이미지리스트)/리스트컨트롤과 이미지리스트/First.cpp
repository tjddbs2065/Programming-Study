#include "First.h"

void ErrorExit(LPCTSTR str) {
	LPVOID lpMsgBuf; //한글화된 문자열을 저장할 곳
	DWORD error = GetLastError();
	//GetLastError() 번호를 -> 영어 -> OS에 맞는 (제어판 문자셋)문자열을 변환해주는 함수
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	TCHAR buffer[MAX_PATH] = { 0, };
	wsprintf(buffer, _T("[%s - %d]%s\n"), str, error, (LPTSTR)lpMsgBuf);
	MessageBox(NULL, buffer, str, MB_OK);
	//_tprintf(_T("[%s - %d]%s\n"), str, error, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
	exit(0);
}
void ErrorMsg(LPCTSTR str) {
	LPVOID lpMsgBuf; //한글화된 문자열을 저장할 곳
	DWORD error = GetLastError();
	//GetLastError() 번호를 -> 영어 -> OS에 맞는 (제어판 문자셋)문자열을 변환해주는 함수
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	TCHAR buffer[MAX_PATH] = { 0, };
	wsprintf(buffer, _T("[%s - %d]%s\n"), str, error, (LPTSTR)lpMsgBuf);
	MessageBox(NULL, buffer, str, MB_OK);
	//_tprintf(_T("[%s - %d]%s\n"), str, error, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

BOOL SelectFolder(TCHAR* folder) {
	BOOL result = FALSE;
	LPITEMIDLIST lpItemIDList = 0;
	BROWSEINFO bi = { 0, };
	bi.lpszTitle = _T("SELECT [FOLDER] what you want to");
	lpItemIDList = SHBrowseForFolder(&bi);
	if (!lpItemIDList) {
		return result;
	}
	result = SHGetPathFromIDList(lpItemIDList, folder);
	if (!result)return result;
	result = TRUE;
	return result;
}
BOOL SelectSaveFile(HWND hwnd, TCHAR* fileName) {
	BOOL result = FALSE;
	OPENFILENAME of = { 0, };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("소스파일(*.cpp)\0*.cpp\0텍스트파일(*.txt)\0*.cpp\0모든파일(*.*)\0*.*");
	of.lpstrFile = fileName;
	of.lpstrInitialDir = _T(".");
	of.nMaxFile = MAX_PATH;
	of.lpstrDefExt = _T(".txt");
	result = GetSaveFileName(&of);
	if (!result) return result;
	result = TRUE;
	return result;
}
BOOL SelectOpenFile(HWND hwnd, TCHAR* fileName) {
	BOOL result = FALSE;
	OPENFILENAME of = { 0, };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("소스파일(*.cpp)\0*.cpp\0모든파일(*.*)\0*.*");
	of.lpstrFile = fileName;
	of.lpstrInitialDir = _T(".");
	of.nMaxFile = MAX_PATH;
	result = GetOpenFileName(&of);
	if (!result) return result;
	result = TRUE;
	return result;

}

void FileRead(HWND hwnd, TCHAR* fileName) {
	//UTF-16 Le의 유니코드는 깨지지 않고 열린다. 한글도
	//UTF-8 x, multibyte
	//1. CreateFile
	HANDLE hRead;
	hRead = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hRead == INVALID_HANDLE_VALUE) return;
	//2. GetFileSize - alloc
	DWORD totalSize = GetFileSize(hRead, NULL);
	if (totalSize == INVALID_FILE_SIZE) return;
	//3. ReadFile
	TCHAR* buffer = 0;
	DWORD realReadByte = 0;
	buffer = new TCHAR[totalSize / sizeof(TCHAR) + 1];
	memset(buffer, 0, totalSize / sizeof(TCHAR) + 1);
	if (!ReadFile(hRead, (TCHAR*)buffer, totalSize, &realReadByte, NULL)) return;
	buffer[totalSize / sizeof(TCHAR)] = 0;
	//4. 저장된 문자열을 edit control에 넣어준다.
	SetWindowText(hwnd, buffer);
	//5. CloseHandle
	if (!CloseHandle(hRead)) return;
	//6. delete[]
	delete[] buffer;
}
void FileWrite(HWND hwnd, TCHAR* fileName) {

	BOOL result = FALSE;
	HANDLE hWrite;

	DWORD textSize = 0, realWriteByte = 0;
	textSize = GetWindowTextLength(hwnd);
	TCHAR* buffer = 0;
	buffer = new TCHAR[textSize + 1];
	memset(buffer, 0, (textSize + 1) * sizeof(TCHAR));

	textSize = GetWindowText(hwnd, buffer, textSize + 1);

	//CreateFile
	buffer[textSize] = 0;
	hWrite = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hWrite == INVALID_HANDLE_VALUE) ErrorExit(_T("CreateFile-write"));

	//WriteFile
#ifdef UNICODE
	WORD word = 0xFEFF;
	result = WriteFile(hWrite, (WORD*)&word, 2, &realWriteByte, NULL);
	if (!result) ErrorMsg(_T("WriteFile-Uicode"));
#endif

	result = WriteFile(hWrite, (TCHAR*)buffer, sizeof(TCHAR) * textSize, &realWriteByte, NULL);
	if (!result) ErrorMsg(_T("WriteFile"));
	//CloseHandle
	delete[] buffer;
	result = CloseHandle(hWrite);
	if (!result) ErrorMsg(_T("CloseHandle-write"));
}