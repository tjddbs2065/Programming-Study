#include"MySystemError.h"


void ErrorExit(LPCTSTR str)//변수 상수 ex) ErrorExit(_T("CreateFile"));
{
	LPVOID lpMsgBuf;
	DWORD errorCode = GetLastError();
	//GetLastError의 번호를 가지고 제어판에 설정된 언어셋으로 
	//문자열을 바꾸어 lpMsgBuf에 넣어준다.
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		, NULL
		, errorCode
		, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
		, (LPTSTR)&lpMsgBuf
		, 0
		, NULL);
	TCHAR buffer[MAX_PATH] = { 0 };
	wsprintf(buffer,_T("[%s:errorCode:%d]%s"), str, errorCode, (LPTSTR)lpMsgBuf);
	MessageBox(NULL, buffer, str, MB_OK);
	//_tprintf(_T("[%s:errorCode:%d]%s\n"), str, errorCode, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
	exit(0);
}
void ErrorMsg(LPCTSTR str)
{
	LPVOID lpMsgBuf;
	DWORD errorCode = GetLastError();
	//GetLastError의 번호를 가지고 제어판에 설정된 언어셋으로 
	//문자열을 바꾸어 lpMsgBuf에 넣어준다.
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		, NULL
		, errorCode
		, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
		, (LPTSTR)&lpMsgBuf
		, 0
		, NULL);
	TCHAR buffer[MAX_PATH] = { 0 };
	wsprintf(buffer, _T("[%s:errorCode:%d]%s"), str, errorCode, (LPTSTR)lpMsgBuf);
	MessageBox(NULL, buffer, str, MB_OK);

	//_tprintf(_T("[%s:errorCode:%d]%s\n"), str, errorCode, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
const TCHAR* GetDayOfWeek(int dayOfWeek)
{
	const TCHAR str[7][MAX_PATH] = { _T("일요일")
		,_T("월요일")
		,_T("화요일")
		,_T("수요일")
		,_T("목요일")
		,_T("금요일")
		,_T("토요일") };

	return str[dayOfWeek];
}
void TimeSet(const SYSTEMTIME st, TCHAR* buffer)
{
	const TCHAR str[7][MAX_PATH] = { _T("일요일")
		,_T("월요일")
		,_T("화요일")
		,_T("수요일")
		,_T("목요일")
		,_T("금요일")
		,_T("토요일") };

	_stprintf_s(buffer, MAX_PATH, _T("%d년 %d월 %d일 %s [%s] %d시 %d 분 %d초(%dmsec)")
		, st.wYear
		, st.wMonth
		, st.wDay
		, str[st.wDayOfWeek]
		, (st.wHour < 12) ? _T("AM") : _T("PM")
		, (st.wHour <= 12 ? st.wHour : st.wHour - 12)
		, st.wMinute
		, st.wSecond
		, st.wMilliseconds);
}
BOOL FinalTimeSet(const FILETIME ft, TCHAR* buffer)
{
	BOOL result = FALSE;
	//UTC FILETIME - Local FILETIME - SYSTEMTIME
	FILETIME ftLocalCreateTime = { 0 };
	SYSTEMTIME stCreateTime = { 0 };
	result = FileTimeToLocalFileTime(&ft, &ftLocalCreateTime);
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
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("SELECT [FOLDER] What you want to");
	//PIDLIST_ABSOLUTE
	lpItemIDList = SHBrowseForFolder(&bi);
	if (!lpItemIDList)
		return result;

	result = SHGetPathFromIDList(lpItemIDList, folder);
	if (!result) return result;
	result = TRUE;

	return result;
}
void DIR(void)
{
	TCHAR folder[MAX_PATH] = { 0 };
	if (!SelectFolder(folder))
	{
		_tprintf(_T("제대로좀 할래"));
		return;
	}
	wsprintf(folder, _T("%s\\*.*"), folder);
	BOOL result = FALSE;
	HANDLE hFind;
	WIN32_FIND_DATA wData = { 0 };
	hFind = FindFirstFile(folder, &wData);
	if (hFind == INVALID_HANDLE_VALUE)
		ErrorExit(_T("FindFirstFile"));

	_tprintf(_T("---------------------------------------\n"));
	_tprintf(_T("            select folder:[%s]\n"), folder);
	_tprintf(_T("         made by Seol Shin,06.19,20\n"));
	_tprintf(_T("---------------------------------------\n\n"));

	TCHAR buffer[MAX_PATH] = { 0 };
	do
	{
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
	OPENFILENAME of = { 0 };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("소스파일(*.cpp)\0*.cpp\0모든파일(*.*)\0*.*\0");
	of.lpstrFile = fileName;
	of.lpstrInitialDir = _T(".");
	of.nMaxFile = MAX_PATH;
	if (GetOpenFileName(&of))
		result = TRUE;
	return result;

}
//파일을 저장할때 확장자명을 붙이지 않는다.
BOOL SelectSaveFile(HWND hwnd, TCHAR* fileName)
{
	BOOL result = FALSE;
	OPENFILENAME of = { 0 };
	of.lStructSize = sizeof(of);
	of.hwndOwner = hwnd;
	of.lpstrFilter = _T("소스파일(*.cpp)\0*.cpp\0모든파일(*.*)\0*.*\0");
	of.lpstrFile = fileName;
	of.lpstrInitialDir = _T(".");
	of.lpstrDefExt = _T("txt");//모든파일에 대해서는 .txt 확장자명이 붙고, 그렇지 않으면 선택된 확장자가 붙는다.
	of.nMaxFile = MAX_PATH;
	if (GetSaveFileName(&of))
		result = TRUE;
	return result;

}
BOOL FileRead(HWND hwnd, TCHAR* fileName)
{
	BOOL result = FALSE;
	HANDLE hRead;
	DWORD lowDWord = 23, highDWord = 0;

	hRead = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hRead == INVALID_HANDLE_VALUE)
	{
		ErrorMsg(_T("CreateFile-read"));
		return result;
	}

	lowDWord = GetFileSize(hRead, &highDWord);
	if (lowDWord == INVALID_FILE_SIZE)
		ErrorMsg(_T("GetFileSize"));

	TCHAR* buffer = 0;
	buffer = new TCHAR[lowDWord / sizeof(TCHAR) + 1];
	memset(buffer, 0, lowDWord);
	DWORD realReadByte = 0;

	result = ReadFile(hRead, (TCHAR*)buffer, lowDWord, &realReadByte, NULL);
	if (!result) ErrorMsg(_T("ReadFile"));
	buffer[lowDWord / sizeof(TCHAR)] = 0;
	// 하나의 함수를 써서 에디트 컨트롤에 쓰겠다.
	SetWindowText(hwnd, buffer);
	result = CloseHandle(hRead);
	if (!result) ErrorMsg(_T("CloseHandle-Read"));
	else result = TRUE;

	delete[] buffer;

	return result;
}
BOOL FileWrite(HWND hwnd, TCHAR* fileName)
{
	BOOL result = FALSE;
	HANDLE hWrite;
	hWrite = CreateFile(fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hWrite == INVALID_HANDLE_VALUE)
	{
		ErrorMsg(_T("CreateFile-write"));
		return result;
	}

	DWORD realWriteByte = 0;
	//TCHAR buffer[] = _T("Hello API");
	TCHAR* buffer = 0;
	int textSize = -1;
	// edit -> length -> buffer, text -> buffer, write
	textSize = GetWindowTextLength(hwnd);
	buffer = new TCHAR[(textSize + 1)];
	memset(buffer, 0, sizeof(TCHAR) * (textSize + 1));
	textSize = GetWindowText(hwnd, buffer, textSize + 1);
	buffer[textSize] = 0;
	//int length = _tcslen(buffer);
	//_tprintf(_T("unicode = %d\n"), length);

#ifdef UNICODE
	WORD word = 0xFEFF;
	result = WriteFile(hWrite, (WORD*)&word, 2, &realWriteByte, NULL);
	if (!result) ErrorMsg(_T("WriteFile-unicode"));

#endif
	result = WriteFile(hWrite, (TCHAR*)buffer,
		sizeof(TCHAR) * (textSize + 1), &realWriteByte, NULL);
	if (!result) ErrorMsg(_T("WriteFile"));

	result = CloseHandle(hWrite);
	if (!result) ErrorMsg(_T("CloseHandle-write"));
	else result = TRUE;

	delete[] buffer;

	return result;
}