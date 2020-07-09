#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>
#include <ShlObj.h>
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")
#include "resource.h"

enum{ 파일, 폴더 };
enum{ 이름, 수정날짜, 종류, 사이즈 };

typedef struct THREADPARAMS {
	HANDLE hExitEvent;
	TCHAR* pathName;
}THREADPARAMS;

void ErrorMsg(LPCTSTR str);
void ErrorExit(LPCTSTR str);

BOOL SelectFolder(TCHAR* folder);
void ChangeFileTimeToSystemTime(const FILETIME* ft, TCHAR* buffer);
void ChangeTime(const SYSTEMTIME* st, TCHAR* buffer);
void InsertColumn(HWND hListCtrl);

void TreeView_InsertRootFile(HWND hTreeCtrl, TCHAR* pathName);
void TreeView_InsertOneFile(HWND hTreeCtrl, TCHAR* directoryName);
void ListView_InsertOneFile(HWND hListCtrl, TCHAR* pathName, TCHAR* fileName, TCHAR* time, int type);
void ListView_SetItems(HWND hListCtrl);
unsigned long GetFileSizeInByte(const TCHAR* pathName);
void InitTreeByPath(HWND hwnd, HWND hTreeCtrl, HWND hListCtrl, TCHAR* pathName);
void InitListByPath(HWND hwnd, HWND hListCtrl, TCHAR* pathName);
void InitTreeByPathWhenEnterKey(WPARAM wParam, HWND hwnd, HWND hTreeCtrl, HWND hListCtrl, TCHAR* pathName);
void SelectTree(LPARAM lParam, HWND hwnd, HWND hTreeCtrl, HWND hListCtrl, TCHAR* pathName);


DWORD WINAPI ThreadFunc(LPVOID lpParam);
