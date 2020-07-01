#pragma once
#include<windows.h>
#include<tchar.h>
#include<locale.h>
//시스템에러처리 함수를 짜보자
void ErrorMsg(const TCHAR* str);
void ErrorExit(const TCHAR* str);