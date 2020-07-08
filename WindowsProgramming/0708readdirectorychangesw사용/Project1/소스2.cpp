#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <Strsafe.h>

DWORD WINAPI ThreadFunc(LPVOID lpParam);
HANDLE hExitEvent;

int _tmain() {
	hExitEvent = CreateEvent(0, 0, 0, 0);
	//HANDLE hThread;
	//hThread = CreateThread(NULL, 0, ThreadFunc, NULL, CREATE_ALWAYS, NULL);

	_tsetlocale(LC_ALL, _T("kor"));

	HANDLE hDir= CreateFile(_T("G:\\"), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED, NULL
	);

	if (hDir == INVALID_HANDLE_VALUE)
		return 0;

	CONST DWORD cbBuffer = 1024 * 1024;
	BYTE* pBuffer = (PBYTE)malloc(cbBuffer);
	DWORD dwNotifyFilter =
		FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME
		| FILE_NOTIFY_CHANGE_ATTRIBUTES;

	DWORD bytesReturned;
	TCHAR buff[MAX_PATH] = { 0, };

	BOOL result = FALSE;

	OVERLAPPED ol = { 0, };
	ol.hEvent = CreateEvent(0, 0, 0, 0);
	BOOL keepOff = FALSE;

	while (!keepOff) {
		result = ReadDirectoryChangesW(hDir, pBuffer, cbBuffer, TRUE, dwNotifyFilter, &bytesReturned, &ol, NULL);

		if (result == 0 && GetLastError() != ERROR_IO_PENDING){
			printf("ReadDirectoryChangesW Failed...\n");
			break;
		}

		//while (!GetOverlappedResult(hDir, &ol, &bytesReturned, FALSE)) {
		//	if (GetLastError() != ERROR_IO_INCOMPLETE)	//GetOverlappedResult() 실패
		//		return 0;
		//}
		while (GetOverlappedResult(hDir, &ol, &bytesReturned, FALSE)) {
				result = FALSE;
				if (bytesReturned != 0) {

					FILE_NOTIFY_INFORMATION* pfni = (FILE_NOTIFY_INFORMATION*)pBuffer;
					do {
						if (pfni->Action != 0) {
							switch (pfni->Action)
							{
							case FILE_ACTION_ADDED:
								wprintf(L"파일 추가\n");
								break;
							case FILE_ACTION_REMOVED:
								wprintf(L"파일 제거\n");
								break;
							case FILE_ACTION_MODIFIED:
								wprintf(L"파일 수정\n");
								break;
							case FILE_ACTION_RENAMED_OLD_NAME:
								wprintf(L"이름 변경(old)\n");
								break;
							case FILE_ACTION_RENAMED_NEW_NAME:
								wprintf(L"이름 변경(new)\n");
								break;
							}
							StringCbCopyNW(buff, sizeof(buff), pfni->FileName, pfni->FileNameLength);
							_tprintf(_T("%s\n"), buff);
						}
						pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + pfni->NextEntryOffset);

					} while (pfni->NextEntryOffset != 0);
					_tprintf(_T("==================\n"));
				}
				break;
			
			if (WaitForSingleObject(hExitEvent, 100) == WAIT_OBJECT_0) {
				keepOff = TRUE;
				_tprintf(_T("q가 눌렸음\n"));
				break;
			}
			//Sleep(100);
		}
		

		//pfni = (FILE_NOTIFY_INFORMATION*)pBuffer;

		/*do {
			switch (pfni->Action)
			{
			case FILE_ACTION_ADDED:
				wprintf(L"파일 추가\n");
				break;
			case FILE_ACTION_REMOVED:
				wprintf(L"파일 제거\n");
				break;
			case FILE_ACTION_MODIFIED:
				wprintf(L"파일 수정\n");
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:
				wprintf(L"이름 변경(old)\n");
				break;
			case FILE_ACTION_RENAMED_NEW_NAME:
				wprintf(L"이름 변경(new)\n");
				break;
			}
			StringCbCopyNW(buff, sizeof(buff), pfni->FileName, pfni->FileNameLength);
			_tprintf(_T("%s\n\n"), buff);

			pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + pfni->NextEntryOffset);
	 	} while (pfni->NextEntryOffset != 0);*/

	}
	//WaitForSingleObject(hThread, INFINITE);

	//CloseHandle(hThread);
	CloseHandle(hExitEvent);
	CloseHandle(hDir);
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
	TCHAR character = 0;
	while (1) {
		character = _gettchar();
		if (character == 'q') {
			SetEvent(hExitEvent);
			break;
		}
	}
	return 0;
}