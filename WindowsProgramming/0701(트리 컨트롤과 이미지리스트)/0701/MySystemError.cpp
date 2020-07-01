#include"MySystemError.h"
// source 파일에는 메모리에 잡히는 것들은 넣어둔다.
void ErrorExit(LPCTSTR str)
{
	LPVOID lpMsgBuf;
	// GetLastError의 번호를 가지고 제어판에 설정된 언어셋으로
	// 문자열을 바꾸어 lpMsgBuf에 넣어준다.
	DWORD errorCode = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	// 에러 결과는 파일로 저장하는 것도 좋다.
	//_tprintf(_T("[%s: errorCode %d]%s\n"), str, errorCode, (LPTSTR)lpMsgBuf);
	TCHAR buffer[MAX_PATH] = { 0 };
	wsprintf(buffer, _T("[%s:Error Code %d] %s\n"), str, errorCode, (LPSTR)lpMsgBuf);
	MessageBox(NULL, buffer, str, MB_OK);
	LocalFree(lpMsgBuf);
	exit(0);

}
void ErrorMsg(LPCTSTR str)
{
	LPVOID lpMsgBuf;
	// GetLastError의 번호를 가지고 제어판에 설정된 언어셋으로
	// 문자열을 바꾸어 lpMsgBuf에 넣어준다.
	DWORD errorCode = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	// 에러 결과는 파일로 저장하는 것도 좋다.
	//_tprintf(_T("[%s: errorCode %d]%s\n"), str, errorCode, (LPTSTR)lpMsgBuf);
	TCHAR buffer[MAX_PATH] = { 0 };
	wsprintf(buffer, _T("[%s:Error Code %d] %s\n"), str, errorCode, (LPSTR)lpMsgBuf);
	MessageBox(NULL, buffer, str, MB_OK);
	LocalFree(lpMsgBuf);
}
const TCHAR* GetDayOfWeek(int dayofweek)
{
	const TCHAR str[7][MAX_PATH] = { _T("일요일"),
		_T("월요일"),
		_T("화요일"),
		_T("수요일"),
		_T("목요일"),
		_T("금요일"),
		_T("토요일") };

	return str[dayofweek];

}
void TimeSet(const SYSTEMTIME st, TCHAR* buffer)
{

	_stprintf_s(buffer, MAX_PATH, _T("%d년 %d월 %d일 %s [%s] %d시 %d분 %d초(%dmsec)"), st.wYear,
		st.wMonth,
		st.wDay,
		GetDayOfWeek(st.wDayOfWeek),
		(st.wHour > 11) ? _T("PM") : _T("AM"),
		(st.wHour > 12) ? st.wHour - 12 : st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds
	);

}
BOOL FinalTimeSet(const FILETIME fileTime, TCHAR* buffer)
{
	FILETIME ftLocalCreateTime = { 0, };
	SYSTEMTIME stCreateTime = { 0, };
	BOOL result = FALSE;
	result = FileTimeToLocalFileTime(&fileTime, &ftLocalCreateTime);
	if (!result)
	{
		ErrorMsg(_T("FileTimeToLocalFileTime"));
		return result;
	}
	result = FileTimeToSystemTime(&ftLocalCreateTime, &stCreateTime);
	if (!result)
	{
		ErrorMsg(_T("FileTimeToSystemTime"));
		return result;
	}
	TimeSet(stCreateTime, buffer);
	result = TRUE;
	return result;
}
BOOL SelectFolder(TCHAR* folder)
{
	BOOL result = FALSE;

	LPITEMIDLIST lpItemIDList = 0;
	BROWSEINFO bi = { 0, };
	bi.lpszTitle = _T("SELETE [FORDER] What you want to");
	lpItemIDList = SHBrowseForFolder(&bi);
	if (!lpItemIDList)
		return result;

	result = SHGetPathFromIDList(lpItemIDList, folder);
	if (!result)	return result;
	result = TRUE;
}
void DIR(void)
{
	TCHAR folder[MAX_PATH];
	BOOL result = FALSE;
	HANDLE hFind;
	WIN32_FIND_DATA wData = { 0, };
	if (!SelectFolder(folder))
	{
		_tprintf(_T("제대로 해라"));
		return;
	}
	wsprintf(folder, _T("%s\\*.*"), folder);
	hFind = FindFirstFile(folder, &wData);
	if (hFind == INVALID_HANDLE_VALUE)
		ErrorExit(_T("FindFirstFile"));
	_tprintf(_T("---------------------------------------------------\n"));
	_tprintf(_T("Select Folder : [%s]\n"), folder);
	_tprintf(_T(" made by JSH, 06.19.20\n"));
	_tprintf(_T("---------------------------------------------------\n\n"));
	//_tprintf(_T("%s\n"), wData.cFileName);
	// UTC FILETIME -> Local FILETIME -> SYSTEMTIME
	//_tprintf(buffer);
	TCHAR buffer[MAX_PATH] = { 0, };
	do {
		memset(buffer, 0, sizeof(TCHAR) * MAX_PATH);
		FinalTimeSet(wData.ftCreationTime, buffer);
		if (wData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			_tprintf(_T("%s\t<DIR>\t%s\n"), buffer, wData.cFileName);
		else _tprintf(_T("%s\t%s\n"), buffer, wData.cFileName);
	} while (FindNextFile(hFind, &wData));

	result = FindClose(hFind);
	if (!result) ErrorMsg(_T("FindClose"));
}

BOOL SelectOpenFile(HWND hwnd, TCHAR* fileName)
{
	BOOL result = FALSE;
	OPENFILENAME of = { 0, };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("소스파일(*.cpp)\0*.cpp\0모든파일(*.*)\0*.*\0");
	of.lpstrFile = fileName;
	of.lpstrInitialDir = _T("");
	of.nMaxFile = MAX_PATH;
	if (GetOpenFileName(&of))
		result = TRUE;
	return result;
}

// 파일을 저장할 때 화장자명을 붙이지 않는다.
BOOL SelectSaveFile(HWND hwnd, TCHAR* fileName)
{
	BOOL result = FALSE;
	OPENFILENAME of = { 0, };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("소스파일(*.cpp)\0*.cpp\0모든파일(*.*)\0*.*\0");
	of.lpstrFile = fileName;
	of.lpstrInitialDir = _T("");
	of.lpstrDefExt = _T(".txt"); // 모든 파일에 대해서는 .txt 확장자명이 붙고, 그렇지 않으면 선택된 확장자가 붙는다.
	of.nMaxFile = MAX_PATH;
	if (GetSaveFileName(&of))
		result = TRUE;
	return result;
}
BOOL FileRead(HWND hwnd, TCHAR* fileName)
{
	HANDLE hRead;
	DWORD lowDWord = 123, highDWord = 43;
	BOOL result = FALSE;

	hRead = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hRead == INVALID_HANDLE_VALUE)
	{
		ErrorMsg(_T("CreateFile-read"));
		return FALSE;
	}

	lowDWord = GetFileSize(hRead, &highDWord);
	if (lowDWord == INVALID_FILE_SIZE)
		ErrorMsg(_T("GetFileSize"));
	TCHAR* buffer = 0;
	buffer = new TCHAR[lowDWord / sizeof(TCHAR) + 1];
	memset(buffer, 0, lowDWord);
	//memset(buffer, 0, (lowDWord / sizeof(TCHAR) + 1) * sizeof(TCHAR));

	DWORD realReadByte = 0;
	result = ReadFile(hRead, (TCHAR*)buffer, lowDWord, &realReadByte, NULL);
	if (!result)ErrorMsg(_T("ReadFile"));

	buffer[lowDWord / sizeof(TCHAR)] = 0;
	// 하나의 함수를 써서 에디트 컨트롤에 쓴다.
	SetWindowText(hwnd, buffer);

	result = CloseHandle(hRead);
	if (!result)ErrorMsg(_T("CloseHandle"));
	else result = TRUE;
	delete[]buffer;

	return result;
}
BOOL FileWrite(HWND hwnd, TCHAR* fileName)
{
	HANDLE hWrite;
	BOOL result = FALSE;
	hWrite = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hWrite == INVALID_HANDLE_VALUE)
	{
		ErrorMsg(_T("CreateFile-save"));
		return FALSE;
	}
	DWORD realWriteByte = 0;
	//TCHAR buffer[] = _T("Hello API한글");
	TCHAR* buffer = 0;
	int textSize = -1;
	//edit -> length -> buffer, text->buffer, write
	textSize = GetWindowTextLength(hwnd);
	buffer = new TCHAR[(textSize + 1)];
	memset(buffer, 0, sizeof(TCHAR) * (textSize + 1));
	textSize = GetWindowText(hwnd, buffer, textSize + 1);
	buffer[textSize] = 0;
	//int length = _tcslen(buffer);
	//_tprintf(_T("unicode = %d\n"), length);

#ifdef UNICODE
	WORD word = 0xFEFF;
	result = WriteFile(hWrite, (WORD*)&word,
		2, &realWriteByte, NULL);
	if (!result) ErrorMsg(_T("WriteFile - UNICODE"));
#endif
	result = WriteFile(hWrite, (TCHAR*)buffer, sizeof(TCHAR) * (textSize + 1), &realWriteByte, NULL);
	if (!result) ErrorMsg(_T("WriteFile"));

	result = CloseHandle(hWrite);
	if (!result) ErrorMsg(_T("CloseHandle - Write"));
	else result = TRUE;
	delete[]buffer;

	return result;
}