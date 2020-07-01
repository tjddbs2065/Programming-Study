#pragma once
// ������� ������ �־�� �Ѵ�. �޸𸮿� ������ �ʴ°͵�
#include<Windows.h>
#include<tchar.h>
#include<locale.h>
#include<stdio.h>
#include<ShlObj.h> // SH �� �Լ���
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