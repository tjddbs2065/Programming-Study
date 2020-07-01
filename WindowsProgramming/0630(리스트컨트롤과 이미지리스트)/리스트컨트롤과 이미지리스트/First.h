#pragma once
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <ShlObj.h>

enum KIND { READ, WRITE }; //C++ 
#define MAX 2

void ErrorExit(LPCTSTR str);
void ErrorMsg(LPCTSTR str);

BOOL SelectOpenFile(HWND hwnd, TCHAR* fileName);
BOOL SelectSaveFile(HWND hwnd, TCHAR* fileName);
BOOL SelectFolder(TCHAR* folder);

void FileRead(HWND hwnd, TCHAR* fileName);
void FileWrite(HWND hwnd, TCHAR* fileName);