#include"MySystemError.h"
//GetLastError()의 에러코드를 한국어 말로 바꿔주는 함수
void ErrorMsg(const TCHAR* str)
{
	LPVOID lpMsgBuf;
	int error = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		, NULL
		, error
		, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
		, (TCHAR*)&lpMsgBuf
		, 0
		, NULL);
	_tprintf(_T("[%s(%d)]%s\n"), str, error, (TCHAR*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
void ErrorExit(const TCHAR* str)
{
	LPVOID lpMsgBuf;
	int error = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		, NULL
		, error
		, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
		, (TCHAR*)&lpMsgBuf
		, 0
		, NULL);
	_tprintf(_T("[%s(%d)]%s\n"), str, error, (TCHAR*)lpMsgBuf);
	LocalFree(lpMsgBuf);
	exit(0);
}