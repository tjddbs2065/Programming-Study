#include "MySystemError.h"
HANDLE hExitEvent[2];
DWORD WINAPI ThreadFunc(LPVOID lpParam);

int _tmain(void) {
	_tsetlocale(LC_ALL, _T("korean"));
	//FindFirstChangeNotification()
	//FindNextChangeNotification()
	//FindCloseChangeNotification()
	hExitEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread;
	hThread = CreateThread(NULL, 0, ThreadFunc, NULL, CREATE_ALWAYS, NULL);
	
	//HANDLE hChange;
	hExitEvent[1] = FindFirstChangeNotification(_T("g:\\"), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME);
	if (hExitEvent[1] == INVALID_HANDLE_VALUE)
		ErrorExit(_T("FindFirstChangeNotification"));
	DWORD dwResult = 0;

	while (1) {
		dwResult = WaitForMultipleObjects(2, hExitEvent, FALSE, INFINITE);
		if(dwResult == WAIT_OBJECT_0 + 0) {
			_tprintf(_T("q를 누르셔서 변경 감시작용을 중단합니다.\n"));
			break;
		}
		else if (dwResult == WAIT_OBJECT_0 + 1) {
			_tprintf(_T("File or Dir Name Changed.\n"));
		}
		

		/*if (WaitForSingleObject(hExitEvent, 10) == WAIT_OBJECT_0)
		{
			_tprintf(_T("q를 누르셔서 변경 감시작용을 중단합니다.\n"));
			break;
		}
		if (WaitForSingleObject(hChange, INFINITE) == WAIT_OBJECT_0) {
			_tprintf(_T("File or Dir name changed\n"));
		}*/
		if (!FindNextChangeNotification(hExitEvent[1]))
		{
			ErrorMsg(_T("FindNextChangeNotification"));
			break;
		}
	}
	WaitForSingleObject(hThread, INFINITE);
	if (!FindCloseChangeNotification(hExitEvent[1]))
		ErrorMsg(_T("FindCloseChangeNotification"));

	CloseHandle(hThread);
	CloseHandle(hExitEvent[0]);

	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
	TCHAR character = 0;
	while (1) {
		character = _gettchar();
		if (character == 'q') {
			//main 함수의 while문에도 종료를 알려준다.
			SetEvent(hExitEvent[0]);
			break;
		}
	}
	return 0;
}