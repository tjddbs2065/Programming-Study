#include "Homework.h"

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

void InsertColumn(HWND hListCtrl) {
	TCHAR column[4][20] = { _T("이름"), _T("수정날짜"), _T("종류"), _T("사이즈") };
	LVCOLUMN lvCol = { 0, };
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 200;
	lvCol.iSubItem = 이름;
	lvCol.pszText = column[이름];
	ListView_InsertColumn(hListCtrl, 이름, &lvCol);

	lvCol.cx = 150;
	lvCol.iSubItem = 수정날짜;
	lvCol.pszText = column[수정날짜];
	ListView_InsertColumn(hListCtrl, 수정날짜, &lvCol);

	lvCol.cx = 70;
	lvCol.iSubItem = 종류;
	lvCol.pszText = column[종류];
	ListView_InsertColumn(hListCtrl, 종류, &lvCol);

	lvCol.cx = 80;
	lvCol.iSubItem = 사이즈;
	lvCol.pszText = column[사이즈];
	ListView_InsertColumn(hListCtrl, 사이즈, &lvCol);
}
void ChangeTime(const SYSTEMTIME* st, TCHAR* buffer)
{
	wsprintf(buffer, _T("%d-%02d-%02d %s %02d:%02d:%02d\t")
		, st->wYear
		, st->wMonth
		, st->wDay
		, (st->wHour < 12) ? _T("오전") : _T("오후")
		, (st->wHour > 12) ? (st->wHour - 12) : (st->wHour)
		, st->wMinute
		, st->wSecond
	);
}
void ChangeFileTimeToSystemTime(const FILETIME* ft, TCHAR* buffer)
{
	FILETIME ftLocalCreateTime = { 0 };
	SYSTEMTIME stCreateTime = { 0 };
	//wData UTC -> LOCALTIME ->SYSTEMTIME
	FileTimeToLocalFileTime(ft, &ftLocalCreateTime);
	FileTimeToSystemTime(&ftLocalCreateTime, &stCreateTime);
	ChangeTime(&stCreateTime, buffer);
}
//=====================================================================================================================================
void SelectTree(LPARAM lParam, HWND hwnd, HWND hTreeCtrl, HWND hListCtrl, TCHAR* pathName) {
	{
		LPNMHDR hdr = (LPNMHDR)lParam;
		LPNMTREEVIEW ntv = (LPNMTREEVIEW)lParam;
		if (hdr->hwndFrom == hTreeCtrl && hdr->code == TVN_SELCHANGING) {
			TCHAR buffer[MAX_PATH] = { 0, };
			TVITEMEX tvEx = { 0, };
			tvEx.mask = TVIF_TEXT;
			tvEx.hItem = ntv->itemNew.hItem;
			tvEx.pszText = buffer;
			tvEx.cchTextMax = MAX_PATH;

			TreeView_GetItem(hTreeCtrl, &tvEx);

			TCHAR path[MAX_PATH] = { 0, };
			if (_tcscmp(pathName, buffer) == 0)//루트 디렉토리를 선택했을 때 
				_tcscpy_s(path, MAX_PATH, buffer);
			else //루트 디렉토리가 아닐 때
				_stprintf_s(path, MAX_PATH, _T("%s\\%s"), pathName, buffer);

			InitListByPath(hwnd, hListCtrl, path);
		}
	}
}
void InitTreeByPathWhenEnterKey(WPARAM wParam, HWND hwnd, HWND hTreeCtrl, HWND hListCtrl, TCHAR* pathName) {
	if (HIWORD(wParam) == EN_CHANGE) {
		ZeroMemory(pathName, MAX_PATH);
		GetDlgItemText(hwnd, IDC_EDIT, pathName, MAX_PATH);
		int len = _tcslen(pathName);
		if (pathName[len - 2] == VK_RETURN) {
			pathName[len - 2] = 0;

			TreeView_DeleteAllItems(hTreeCtrl);
			ListView_DeleteAllItems(hListCtrl);

			InitTreeByPath(hwnd, hTreeCtrl, hListCtrl, pathName);

			SetDlgItemText(hwnd, IDC_EDIT, _T(""));
		}
	}
}
void InitTreeByPath(HWND hwnd, HWND hTreeCtrl, HWND hListCtrl, TCHAR* pathName) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR tmpPath[MAX_PATH];

	_tcscpy_s(tmpPath, MAX_PATH, pathName);
	_tcscat_s(tmpPath, MAX_PATH, _T("\\*.*")); // 경로 안의 파일들 경로 설정 ex) C:\test\*.*
	hFind = FindFirstFile(tmpPath, &FindFileData); //첫 번째 파일 핸들 얻어오기

	if (hFind == INVALID_HANDLE_VALUE) // 파일 핸들을 얻어오지 못했을 경우 메시지 박스 - 잘못된 경로
	{
		TCHAR buffer[MAX_PATH] = { 0, };
		_stprintf_s(buffer, MAX_PATH, _T("\'%s\'을(를) 찾을 수 없습니다. 맞춤법을 확인하고 다시 시도하십시오.(%d)"), pathName, GetLastError());
		MessageBox(hwnd, buffer, _T("파일 탐색기"), MB_OK);
		return;
	}

	TreeView_DeleteAllItems(hTreeCtrl);
	ListView_DeleteAllItems(hListCtrl);
	TreeView_InsertRootFile(hTreeCtrl, pathName); //트리를 초기화 하고, 루트파일 설정.
	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // 폴더인지 확인
			TreeView_InsertOneFile(hTreeCtrl, FindFileData.cFileName); // 트리에 하위 디렉토리 추가
	} while (FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
}
void InitListByPath(HWND hwnd, HWND hListCtrl, TCHAR* pathName) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR tmpPath[MAX_PATH];

	_tcscpy_s(tmpPath, MAX_PATH, pathName);
	_tcscat_s(tmpPath, MAX_PATH, _T("\\*.*")); // 경로 안의 파일들 경로 설정 ex) C:\test\*.*
	hFind = FindFirstFile(tmpPath, &FindFileData); //첫 번째 파일 핸들 얻어오기

	if (hFind == INVALID_HANDLE_VALUE) // 파일 핸들을 얻어오지 못했을 경우 메시지 박스
	{
		TCHAR buffer[MAX_PATH] = { 0, };
		_stprintf_s(buffer, MAX_PATH, _T("FindFirstFile Failed [%d]"), GetLastError());
		MessageBox(hwnd, buffer, _T("!!"), MB_OK);
		return;
	}

	ListView_DeleteAllItems(hListCtrl);
	do {
		TCHAR time[MAX_PATH] = { 0, };
		ChangeFileTimeToSystemTime(&FindFileData.ftLastWriteTime, time); // buffer에 변환된 시간을 받는다.

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // 폴더인지 확인
			ListView_InsertOneFile(hListCtrl, pathName, FindFileData.cFileName, time, 폴더);
		else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) // 파일인지 확인
			ListView_InsertOneFile(hListCtrl, pathName, FindFileData.cFileName, time, 파일);

	} while (FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
}

//========================================================================================================================
void ListView_InsertOneFile(HWND hListCtrl, TCHAR* pathName, TCHAR* fileName, TCHAR* time, int type) {
	{
		TCHAR buffer[MAX_PATH] = { 0, };
		int count = ListView_GetItemCount(hListCtrl);

		LVITEM lvItem = { 0, };
		lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
		lvItem.iItem = count;
		lvItem.iImage = (type == 파일) ? 2 : 0;

		lvItem.iSubItem = 이름;
		lvItem.pszText = fileName;
		ListView_InsertItem(hListCtrl, &lvItem);

		lvItem.iSubItem = 수정날짜;
		lvItem.pszText = time;
		ListView_SetItem(hListCtrl, &lvItem);

		ZeroMemory(buffer, MAX_PATH);
		_tcscpy_s(buffer, MAX_PATH, (type == 폴더) ? _T("폴더") : _T("파일"));
		lvItem.iSubItem = 종류;
		lvItem.pszText = buffer;
		ListView_SetItem(hListCtrl, &lvItem);

		if (type == 파일) {
			ZeroMemory(buffer, MAX_PATH);
			_stprintf_s(buffer, MAX_PATH, _T("%s\\%s"), pathName, fileName); //buffer에 경로 복사

			TCHAR size[20] = { 0, };
			unsigned long fileSize = GetFileSizeInByte(buffer); // buffer에 경로

			if (fileSize / 1024 > 0) _stprintf_s(size, sizeof(size) / sizeof(TCHAR), _T("%lu KB"), fileSize / 1024);
			else _stprintf_s(size, sizeof(size) / sizeof(TCHAR), _T("%lu B"), fileSize);

			lvItem.iSubItem = 사이즈;
			lvItem.pszText = size;
			ListView_SetItem(hListCtrl, &lvItem);
		}
	}
}

void TreeView_InsertOneFile(HWND hTreeCtrl, TCHAR* directoryName) {
	TVINSERTSTRUCT tvs = { 0, };
	tvs.hParent = TreeView_GetRoot(hTreeCtrl);
	tvs.hInsertAfter = TVI_LAST;
	tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvs.item.pszText = directoryName;
	tvs.item.iImage = 0;
	tvs.item.iSelectedImage = 1;

	TreeView_InsertItem(hTreeCtrl, &tvs);
	TreeView_Expand(hTreeCtrl, TreeView_GetRoot(hTreeCtrl), TVE_EXPAND);
}
void TreeView_InsertRootFile(HWND hTreeCtrl, TCHAR* pathName) {
	TVINSERTSTRUCT tvs = { 0, };
	tvs.hParent = NULL;
	tvs.hInsertAfter = TVI_LAST;
	tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvs.item.pszText = pathName;
	tvs.item.iImage = 0;
	tvs.item.iSelectedImage = 1;

	TreeView_InsertItem(hTreeCtrl, &tvs);
}
void ListView_SetItems(HWND hListCtrl) {
	ListView_DeleteAllItems(hListCtrl);

}

unsigned long GetFileSizeInByte(const TCHAR* pathName) {
	HANDLE hRead;
	hRead = CreateFile(pathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 파일 핸들 생성
	if (hRead == INVALID_HANDLE_VALUE) {
		TCHAR errorMessage[MAX_PATH] = { 0, };
		_stprintf_s(errorMessage, MAX_PATH, _T("CreateFile - Invalid Handle Value (%d)"), GetLastError());
		MessageBox(NULL, errorMessage, _T("!!"), MB_OK);
		return 0;
	}

	DWORD lowByte = 0, highByte = 0;
	lowByte = GetFileSize(hRead, &highByte);// 파일 핸들로 크기 얻어오기 higByte에는 4GB이상일 때의 크기, lowByte에는 미만일 때의 크기

	CloseHandle(hRead);

	if (!lowByte)return (unsigned long)highByte;//4GB 이상일 때
	else return (unsigned long)lowByte;//4GB 미만일 때
}

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
DWORD WINAPI ThreadFunc(LPVOID lpParam) {
	SYSTEMTIME st = { 0, };
	GetLocalTime(&st);
	TCHAR time[MAX_PATH] = { 0, };
	_stprintf_s(time, MAX_PATH, _T("%04d-%02d-%02d_%02d_%02d_%02d_log.txt"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);//로그 파일 이름

	HANDLE hFile = CreateFile(time, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		ErrorMsg(_T("CreateFile"));
		return FALSE;
	}

	//유니코드 형식 지정
	WORD wd = 0xFEFF;
	WriteFile(hFile, &wd, 2, NULL, NULL);

	HANDLE hDir = CreateFile((TCHAR*)((THREADPARAMS*)lpParam)->pathName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL
	);
	if (hDir == INVALID_HANDLE_VALUE) {
		ErrorMsg(_T("CreateFile-ReadDirectoryChangesW"));
		return FALSE;
	}

	//================================== ReadDirectoryChangesW 인수 초기화
	CONST DWORD cbBuffer = 1024 * 1024;
	BYTE* pBuffer = (PBYTE)malloc(cbBuffer);
	DWORD dwNotifyFilter =
		FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
		FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE |
		FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION;;
	DWORD bytesReturned;

	OVERLAPPED ol = { 0, };
	ol.hEvent = CreateEvent(0, 0, 0, 0);

	BOOL result;
	BOOL onOff = TRUE;

	while (onOff) {
		result = ReadDirectoryChangesW(hDir, pBuffer, cbBuffer, TRUE, dwNotifyFilter, &bytesReturned, &ol, NULL);
		if (!result) {
			ErrorMsg(_T("ReadDirectoryChangesW"));
			break;
		}

		while (1) {
			if (WaitForSingleObject(((THREADPARAMS*)lpParam)->hExitEvent, 100) == WAIT_OBJECT_0) {
				//_tprintf(_T("종료...\n"));
				onOff = FALSE;
				break;
			}
			if (GetOverlappedResult(hDir, &ol, &bytesReturned, FALSE)) {
				if (bytesReturned != 0) {

					FILE_NOTIFY_INFORMATION* pfni = (FILE_NOTIFY_INFORMATION*)pBuffer;
					if (pfni->Action != 0) {
						do {
							TCHAR buff[MAX_PATH * 2] = { 0, };
							Sleep(10);
							GetLocalTime(&st);
							_stprintf_s(buff, MAX_PATH, _T("%04d-%02d-%02d_%02d:%02d:%02d\t"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

							switch (pfni->Action)
							{
							case FILE_ACTION_ADDED:
								_tcscat_s(buff, MAX_PATH, _T("파일 생성 \t"));
								break;
							case FILE_ACTION_REMOVED:
								_tcscat_s(buff, MAX_PATH, _T("파일 제거 \t"));
								break;
							case FILE_ACTION_MODIFIED:
								_tcscat_s(buff, MAX_PATH, _T("파일 수정 \t"));
								break;
							case FILE_ACTION_RENAMED_OLD_NAME:
								_tcscat_s(buff, MAX_PATH, _T("이름 변경(old)\t"));
								break;
							case FILE_ACTION_RENAMED_NEW_NAME:
								_tcscat_s(buff, MAX_PATH, _T("이름 변경(new)\t"));
								break;
							}

							//StringCbCopyNW(fileName, sizeof(fileName), pfni->FileName, pfni->FileNameLength);
							_stprintf_s(buff, MAX_PATH, _T("%s%s\\"), buff, (TCHAR*)((THREADPARAMS*)lpParam)->pathName);
							_tcsncat_s(buff, MAX_PATH, pfni->FileName, pfni->FileNameLength / sizeof(TCHAR));
							_tcscat_s(buff, MAX_PATH, _T("\r"));

							//로그 파일에 기록
							int len = _tcslen(buff);
							WriteFile(hFile, (TCHAR*)buff, sizeof(TCHAR) * (len), NULL, NULL);

							pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + pfni->NextEntryOffset);
						} while (pfni->NextEntryOffset != 0);
					}
				}
				break;
			}
		}
	}
	free(pBuffer);
	CloseHandle(ol.hEvent);
	CloseHandle(hFile);
	CloseHandle(hDir);

	return 0;
}