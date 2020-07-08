#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <Strsafe.h>
VOID CALLBACK cbArchDefFileChanged(DWORD dwErrorCode,
	DWORD dwNumberOfBytesTransfered,
	LPOVERLAPPED lpOverlapped);
DWORD WINAPI ThreadFunc(LPVOID lpParam);
HANDLE hExitEvent;

int _tmain() {
	_tsetlocale(LC_ALL, _T("korean"));

	hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread;
	hThread = CreateThread(NULL, 0, ThreadFunc, NULL, CREATE_ALWAYS, NULL);


	HANDLE hDir = CreateFile(_T("G:\\"), 
		FILE_LIST_DIRECTORY | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, 
		NULL
	);
	OVERLAPPED ol = { 0, };
	ol.Internal = ol.InternalHigh = ol.Offset = ol.OffsetHigh = 0;
	ol.hEvent = hExitEvent;


	const DWORD cbBuffer = 1024 * 1024;
	BYTE* pBuffer = (PBYTE)malloc(cbBuffer);

	DWORD dwNotifyFilter = FILE_NOTIFY_CHANGE_LAST_WRITE;
		//FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME 
		/*| FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE 
		| FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_LAST_ACCESS
		| FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SECURITY*/;
	DWORD bytesReturned;
	TCHAR buffer[MAX_PATH] = { 0, };
	BOOL result;

	while(2) {
		result = ReadDirectoryChangesW(
			hDir, pBuffer, cbBuffer, TRUE, dwNotifyFilter, 
			&bytesReturned, &ol, NULL);

		if (!result) {
			result = GetLastError();
			if (result != ERROR_IO_PENDING)
				_tprintf(_T("ReadDirectoryChangesW Failed...\n"));
			break;
		}

		BOOL dwResult = GetOverlappedResult(hDir, &ol, &bytesReturned, FALSE);
		if (!dwResult) {
			if (bytesReturned != 0) {
				FILE_NOTIFY_INFORMATION* pfni = (FILE_NOTIFY_INFORMATION*)pBuffer;
				do {
					if (pfni->Action != 0) {

						_tprintf(_T("파일 이름 길이 : %d\n"), pfni->FileNameLength);

						StringCbCopyNW(buffer, sizeof(buffer), pfni->FileName, pfni->FileNameLength);

						_tprintf(_T("파일 이름 : %s\n"), buffer);
					}
					pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + ol.InternalHigh);

				} while (pfni->NextEntryOffset != 0);
			}
		}
		//do {
		//	StringCbCopyNW(buffer, sizeof(buffer), pfni->FileName, pfni->FileNameLength);

		//	//_tprintf(_T("NextEntryOffset(%d)\n"), pfni->NextEntryOffset);
		//	switch (pfni->Action)
		//	{
		//	case FILE_ACTION_ADDED:
		//		_tprintf(_T("파일이 추가되었습니다(%s).\n"), buffer);
		//		break;
		//	case FILE_ACTION_REMOVED:
		//		_tprintf(_T("파일이 제거되었습니다(%s).\n"), buffer);
		//		break;
		//	case FILE_ACTION_MODIFIED:
		//		_tprintf(_T("파일이 수정되었습니다(%s).\n"), buffer);
		//		break;
		//	case FILE_ACTION_RENAMED_OLD_NAME:
		//		_tprintf(_T("파일 이름이 바뀌었습니다(이전 이름: %s)\n"), buffer);
		//		break;
		//	case FILE_ACTION_RENAMED_NEW_NAME:
		//		_tprintf(_T("파일 이름이 바뀌었습니다(새 이름: %s).\n"), buffer);
		//		break;
		//	default:
		//		break;
		//	}
		//	//_tprintf(_T("파일 이름 길이 : %d\n"), pfni->FileNameLength);

		//	//_tcscpy_s(buffer, (pfni->FileNameLength)/sizeof(TCHAR), pfni->FileName);

		//	//_tprintf(_T("파일 이름 : %s\n"), buffer);

		//	pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + pfni->NextEntryOffset);
		//	if (WaitForSingleObject(hExitEvent, 100) == WAIT_OBJECT_0) {
		//		_tprintf(_T("q..가 눌려 종료...\n"));
		//		break;
		//	}

		//} while (pfni->NextEntryOffset > 0);
		
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hDir);
	CloseHandle(hExitEvent);
	CloseHandle(hThread);
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
	TCHAR character = 0;
	while (1) {
		character = _gettchar();
		if (character == 'q') {
			//main 함수의 while문에도 종료를 알려준다.
			SetEvent(hExitEvent);
			break;
		}
	}
	return 0;
}
VOID CALLBACK cbArchDefFileChanged(DWORD dwErrorCode,// completion code
	DWORD dwNumberOfBytesTransfered,  // number of bytes transferred
	LPOVERLAPPED lpOverlapped)        // I/O information buffer
{
	_tprintf(_T("routine"));
	//int temp = status - WAIT_OBJECT_0;
	//int temp2 = status - WAIT_ABANDONED_0;


	//if (status == WAIT_OBJECT_0)
	//{// The config directory was changed
	//	fni = (PFILE_NOTIFY_INFORMATION)&Buffer;
	//	wprintf("%s changed\n", fni->FileName);
	//}
	//else if (status == WAIT_IO_COMPLETION)
	//{
	//	printf("WAIT_IO_COMPLETION The wait was ended by one or more user-mode asynchronous procedure calls (APC) queued to the thread\n");
	//}
	//else if (status == WAIT_TIMEOUT)
	//{
	//	printf("WAIT_TIMEOUT\n");
	//}
	//else if (status == WAIT_FAILED)
	//{
	//	status = GetLastError();
	//}

	//SetEvent(hFilesChanged[ARCHDEF_FILE]);
	
}