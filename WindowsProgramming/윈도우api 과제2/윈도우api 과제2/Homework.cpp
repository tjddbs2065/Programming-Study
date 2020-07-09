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
	TCHAR column[4][20] = { _T("�̸�"), _T("������¥"), _T("����"), _T("������") };
	LVCOLUMN lvCol = { 0, };
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 200;
	lvCol.iSubItem = �̸�;
	lvCol.pszText = column[�̸�];
	ListView_InsertColumn(hListCtrl, �̸�, &lvCol);

	lvCol.cx = 150;
	lvCol.iSubItem = ������¥;
	lvCol.pszText = column[������¥];
	ListView_InsertColumn(hListCtrl, ������¥, &lvCol);

	lvCol.cx = 70;
	lvCol.iSubItem = ����;
	lvCol.pszText = column[����];
	ListView_InsertColumn(hListCtrl, ����, &lvCol);

	lvCol.cx = 80;
	lvCol.iSubItem = ������;
	lvCol.pszText = column[������];
	ListView_InsertColumn(hListCtrl, ������, &lvCol);
}
void ChangeTime(const SYSTEMTIME* st, TCHAR* buffer)
{
	wsprintf(buffer, _T("%d-%02d-%02d %s %02d:%02d:%02d\t")
		, st->wYear
		, st->wMonth
		, st->wDay
		, (st->wHour < 12) ? _T("����") : _T("����")
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
			if (_tcscmp(pathName, buffer) == 0)//��Ʈ ���丮�� �������� �� 
				_tcscpy_s(path, MAX_PATH, buffer);
			else //��Ʈ ���丮�� �ƴ� ��
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
	_tcscat_s(tmpPath, MAX_PATH, _T("\\*.*")); // ��� ���� ���ϵ� ��� ���� ex) C:\test\*.*
	hFind = FindFirstFile(tmpPath, &FindFileData); //ù ��° ���� �ڵ� ������

	if (hFind == INVALID_HANDLE_VALUE) // ���� �ڵ��� ������ ������ ��� �޽��� �ڽ� - �߸��� ���
	{
		TCHAR buffer[MAX_PATH] = { 0, };
		_stprintf_s(buffer, MAX_PATH, _T("\'%s\'��(��) ã�� �� �����ϴ�. ������� Ȯ���ϰ� �ٽ� �õ��Ͻʽÿ�.(%d)"), pathName, GetLastError());
		MessageBox(hwnd, buffer, _T("���� Ž����"), MB_OK);
		return;
	}

	TreeView_DeleteAllItems(hTreeCtrl);
	ListView_DeleteAllItems(hListCtrl);
	TreeView_InsertRootFile(hTreeCtrl, pathName); //Ʈ���� �ʱ�ȭ �ϰ�, ��Ʈ���� ����.
	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �������� Ȯ��
			TreeView_InsertOneFile(hTreeCtrl, FindFileData.cFileName); // Ʈ���� ���� ���丮 �߰�
	} while (FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
}
void InitListByPath(HWND hwnd, HWND hListCtrl, TCHAR* pathName) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR tmpPath[MAX_PATH];

	_tcscpy_s(tmpPath, MAX_PATH, pathName);
	_tcscat_s(tmpPath, MAX_PATH, _T("\\*.*")); // ��� ���� ���ϵ� ��� ���� ex) C:\test\*.*
	hFind = FindFirstFile(tmpPath, &FindFileData); //ù ��° ���� �ڵ� ������

	if (hFind == INVALID_HANDLE_VALUE) // ���� �ڵ��� ������ ������ ��� �޽��� �ڽ�
	{
		TCHAR buffer[MAX_PATH] = { 0, };
		_stprintf_s(buffer, MAX_PATH, _T("FindFirstFile Failed [%d]"), GetLastError());
		MessageBox(hwnd, buffer, _T("!!"), MB_OK);
		return;
	}

	ListView_DeleteAllItems(hListCtrl);
	do {
		TCHAR time[MAX_PATH] = { 0, };
		ChangeFileTimeToSystemTime(&FindFileData.ftLastWriteTime, time); // buffer�� ��ȯ�� �ð��� �޴´�.

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �������� Ȯ��
			ListView_InsertOneFile(hListCtrl, pathName, FindFileData.cFileName, time, ����);
		else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) // �������� Ȯ��
			ListView_InsertOneFile(hListCtrl, pathName, FindFileData.cFileName, time, ����);

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
		lvItem.iImage = (type == ����) ? 2 : 0;

		lvItem.iSubItem = �̸�;
		lvItem.pszText = fileName;
		ListView_InsertItem(hListCtrl, &lvItem);

		lvItem.iSubItem = ������¥;
		lvItem.pszText = time;
		ListView_SetItem(hListCtrl, &lvItem);

		ZeroMemory(buffer, MAX_PATH);
		_tcscpy_s(buffer, MAX_PATH, (type == ����) ? _T("����") : _T("����"));
		lvItem.iSubItem = ����;
		lvItem.pszText = buffer;
		ListView_SetItem(hListCtrl, &lvItem);

		if (type == ����) {
			ZeroMemory(buffer, MAX_PATH);
			_stprintf_s(buffer, MAX_PATH, _T("%s\\%s"), pathName, fileName); //buffer�� ��� ����

			TCHAR size[20] = { 0, };
			unsigned long fileSize = GetFileSizeInByte(buffer); // buffer�� ���

			if (fileSize / 1024 > 0) _stprintf_s(size, sizeof(size) / sizeof(TCHAR), _T("%lu KB"), fileSize / 1024);
			else _stprintf_s(size, sizeof(size) / sizeof(TCHAR), _T("%lu B"), fileSize);

			lvItem.iSubItem = ������;
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
	hRead = CreateFile(pathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // ���� �ڵ� ����
	if (hRead == INVALID_HANDLE_VALUE) {
		TCHAR errorMessage[MAX_PATH] = { 0, };
		_stprintf_s(errorMessage, MAX_PATH, _T("CreateFile - Invalid Handle Value (%d)"), GetLastError());
		MessageBox(NULL, errorMessage, _T("!!"), MB_OK);
		return 0;
	}

	DWORD lowByte = 0, highByte = 0;
	lowByte = GetFileSize(hRead, &highByte);// ���� �ڵ�� ũ�� ������ higByte���� 4GB�̻��� ���� ũ��, lowByte���� �̸��� ���� ũ��

	CloseHandle(hRead);

	if (!lowByte)return (unsigned long)highByte;//4GB �̻��� ��
	else return (unsigned long)lowByte;//4GB �̸��� ��
}

void ErrorExit(LPCTSTR str) {
	LPVOID lpMsgBuf; //�ѱ�ȭ�� ���ڿ��� ������ ��
	DWORD error = GetLastError();
	//GetLastError() ��ȣ�� -> ���� -> OS�� �´� (������ ���ڼ�)���ڿ��� ��ȯ���ִ� �Լ�
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
	LPVOID lpMsgBuf; //�ѱ�ȭ�� ���ڿ��� ������ ��
	DWORD error = GetLastError();
	//GetLastError() ��ȣ�� -> ���� -> OS�� �´� (������ ���ڼ�)���ڿ��� ��ȯ���ִ� �Լ�
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
	_stprintf_s(time, MAX_PATH, _T("%04d-%02d-%02d_%02d_%02d_%02d_log.txt"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);//�α� ���� �̸�

	HANDLE hFile = CreateFile(time, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		ErrorMsg(_T("CreateFile"));
		return FALSE;
	}

	//�����ڵ� ���� ����
	WORD wd = 0xFEFF;
	WriteFile(hFile, &wd, 2, NULL, NULL);

	HANDLE hDir = CreateFile((TCHAR*)((THREADPARAMS*)lpParam)->pathName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL
	);
	if (hDir == INVALID_HANDLE_VALUE) {
		ErrorMsg(_T("CreateFile-ReadDirectoryChangesW"));
		return FALSE;
	}

	//================================== ReadDirectoryChangesW �μ� �ʱ�ȭ
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
				//_tprintf(_T("����...\n"));
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
								_tcscat_s(buff, MAX_PATH, _T("���� ���� \t"));
								break;
							case FILE_ACTION_REMOVED:
								_tcscat_s(buff, MAX_PATH, _T("���� ���� \t"));
								break;
							case FILE_ACTION_MODIFIED:
								_tcscat_s(buff, MAX_PATH, _T("���� ���� \t"));
								break;
							case FILE_ACTION_RENAMED_OLD_NAME:
								_tcscat_s(buff, MAX_PATH, _T("�̸� ����(old)\t"));
								break;
							case FILE_ACTION_RENAMED_NEW_NAME:
								_tcscat_s(buff, MAX_PATH, _T("�̸� ����(new)\t"));
								break;
							}

							//StringCbCopyNW(fileName, sizeof(fileName), pfni->FileName, pfni->FileNameLength);
							_stprintf_s(buff, MAX_PATH, _T("%s%s\\"), buff, (TCHAR*)((THREADPARAMS*)lpParam)->pathName);
							_tcsncat_s(buff, MAX_PATH, pfni->FileName, pfni->FileNameLength / sizeof(TCHAR));
							_tcscat_s(buff, MAX_PATH, _T("\r"));

							//�α� ���Ͽ� ���
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