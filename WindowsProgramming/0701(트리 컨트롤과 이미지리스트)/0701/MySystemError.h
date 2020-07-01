#pragma once
// 헤더에는 선언만이 있어야 한다. 메모리에 잡히지 않는것들
#include<Windows.h>
#include<tchar.h>
#include<locale.h>
#include<stdio.h>
#include<ShlObj.h> // SH 쉘 함수들
#define MAX 2
enum { READ, WRITE };

void ErrorExit(LPCTSTR str);
void ErrorMsg(LPCTSTR str);
const TCHAR* GetDayOfWeek(int dayofweek);
void TimeSet(const SYSTEMTIME st, TCHAR* buffer);
BOOL FinalTimeSet(const FILETIME fileTime, TCHAR* buffer);
BOOL SelectFolder(TCHAR* folder);
void DIR(void);


BOOL SelectOpenFile(HWND hwnd, TCHAR* fileName);
BOOL SelectSaveFile(HWND hwnd, TCHAR* fileName);
BOOL FileRead(HWND hwnd, TCHAR* fileName);
BOOL FileWrite(HWND hwnd, TCHAR* fileName);