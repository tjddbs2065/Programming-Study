#pragma once
#include<windows.h>
#include<tchar.h>
#include<locale.h>
#include<stdio.h>
#include <ShlObj.h> //SH 쉘함수들

#define MAX 2
enum { READ, WRITE };

BOOL SelectFolder(TCHAR* folder);
void ErrorExit(LPCTSTR str);//변수 상수 ex) ErrorExit(_T("CreateFile"));
void ErrorMsg(LPCTSTR str);
const TCHAR* GetDayOfWeek(int dayOfWeek);
void TimeSet(const SYSTEMTIME st, TCHAR* buffer);
BOOL FinalTimeSet(const FILETIME ft, TCHAR* buffer);
void DIR(void);
BOOL SelectOpenFile(HWND hwnd, TCHAR* fileName);
BOOL SelectSaveFile(HWND hwnd, TCHAR* fileName);
BOOL FileRead(HWND hwnd, TCHAR* fileName);
BOOL FileWrite(HWND hwnd, TCHAR* fileName);