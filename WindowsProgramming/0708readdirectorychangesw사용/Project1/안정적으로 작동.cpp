#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <Strsafe.h>

DWORD WINAPI ThreadFunc(LPVOID lpParam);
HANDLE hExitEvent;

int _tmain() {
	_tsetlocale(LC_ALL, _T("korean"));
	

	SYSTEMTIME st = { 0, };
	GetLocalTime(&st);
	TCHAR time[MAX_PATH] = { 0, };
	_stprintf_s(time, MAX_PATH, _T("%04d-%02d-%02d_%02d_%02d.txt"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
	_tprintf(_T("%s\n"), time);

	HANDLE hFile = CreateFile(time, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 0;
	WORD wd = 0xFEFF;
	WriteFile(hFile, &wd, 2, NULL, NULL);

	HANDLE hDir = CreateFile(_T("E:\\test"), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL
	);

	if (hDir == INVALID_HANDLE_VALUE)
		return 0;

	CONST DWORD cbBuffer = 1024 * 1024;
	BYTE* pBuffer = (PBYTE)malloc(cbBuffer);
	DWORD dwNotifyFilter = 
		FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
		FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE |
		FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION;

	DWORD bytesReturned;

	BOOL result;
	OVERLAPPED ol = { 0, };
	ol.hEvent = CreateEvent(0, 0, 0, 0);

	while (1) {
		result = ReadDirectoryChangesW(hDir, pBuffer, cbBuffer, TRUE, dwNotifyFilter, &bytesReturned, &ol, NULL);
		if (!result)
			break;
		while (1) {
			if (GetOverlappedResult(hDir, &ol, &bytesReturned, FALSE)) {
				if (bytesReturned != 0) {
					FILE_NOTIFY_INFORMATION* pfni = (FILE_NOTIFY_INFORMATION*)pBuffer;
					if (pfni->Action != 0) {
						do {
							TCHAR buff[MAX_PATH] = { 0, };
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
							TCHAR fileName[MAX_PATH] = { 0, };
							StringCbCopyNW(fileName, sizeof(fileName), pfni->FileName, pfni->FileNameLength);

							_tcscat_s(buff, MAX_PATH, fileName);
							_tcscat_s(buff, MAX_PATH, _T("\r"));
							_tprintf(_T("%s\n"), buff);


							int len = _tcslen(buff);
							WriteFile(hFile, (TCHAR*)buff, sizeof(TCHAR) * (len + 1), NULL, NULL);
							pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + pfni->NextEntryOffset);
						} while (pfni->NextEntryOffset != 0);
					}
					Sleep(10);
					_tprintf(_T("==================\n"));
				}
				break;
			}
			Sleep(10);
		}
	}

	CloseHandle(hFile);
	CloseHandle(hExitEvent);
	CloseHandle(hDir);
	return 0;
}