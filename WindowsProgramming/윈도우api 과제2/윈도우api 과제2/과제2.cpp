#include "Homework.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	_tsetlocale(LC_ALL, _T("korean"));
	hInst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_HOMEWORK), NULL, DlgProc);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static TCHAR pathName[MAX_PATH] = { 0, };
	static HWND hTreeCtrl, hListCtrl;
	static HIMAGELIST hImageList;
	static BOOL onOff = FALSE;
	static HANDLE hThread;
	static THREADPARAMS tp = { 0, };
	
	switch (iMsg)
	{
	case WM_NOTIFY: 
		SelectTree(lParam, hwnd, hTreeCtrl, hListCtrl, pathName);
		break;

	case WM_INITDIALOG:
		InitCommonControls();

		hTreeCtrl = GetDlgItem(hwnd, IDC_TREE);
		hListCtrl = GetDlgItem(hwnd, IDC_LIST);
		hImageList = ImageList_LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_FOLDERS), 32, 1, RGB(255, 255, 255));


		ListView_SetImageList(hListCtrl, hImageList, LVSIL_SMALL);
		ListView_SetExtendedListViewStyle(hListCtrl, LVS_EX_FULLROWSELECT);

		TreeView_SetImageList(hTreeCtrl, hImageList, TVSIL_NORMAL);

		InsertColumn(hListCtrl);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_MONITORING:
			if (!onOff) {
				if (_tcscmp(pathName, _T("")) != 0) {
					
					tp.hExitEvent = CreateEvent(0, 0, 0, 0);
					tp.pathName = pathName;
					hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&tp, CREATE_ALWAYS, NULL);
					if (hThread == INVALID_HANDLE_VALUE) {
						ErrorMsg(_T("CreatThread"));
						break;
					}
					onOff = TRUE;
					EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_FOLDER), FALSE);
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT), FALSE);
					EnableWindow(GetDlgItem(hwnd, IDC_LIST), FALSE);
					EnableWindow(GetDlgItem(hwnd, IDC_TREE), FALSE);
					SetWindowText(GetDlgItem(hwnd, IDC_BUTTON_MONITORING), _T("STOP MONITORING"));
				}
				else
					MessageBox(hwnd, _T("경로를 지정해 주세요."), _T("!!"), MB_OK);
			}
			else {
				SetEvent(tp.hExitEvent);
				CloseHandle(hThread);
				CloseHandle(tp.hExitEvent);
				onOff = FALSE;
				EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_FOLDER), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDC_EDIT), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDC_LIST), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDC_TREE), TRUE);
				SetWindowText(GetDlgItem(hwnd, IDC_BUTTON_MONITORING), _T("MONITORING"));
				InitTreeByPath(hwnd, hTreeCtrl, hListCtrl, pathName);
			}
			break;
		case IDC_BUTTON_FOLDER:
			if (SelectFolder(pathName)) // 폴더 경로 얻어오기
			{
				InitTreeByPath(hwnd, hTreeCtrl, hListCtrl, pathName);
				SetFocus(GetDlgItem(hwnd, IDC_EDIT));
			}
			break;
		case IDC_EDIT:
			InitTreeByPathWhenEnterKey(wParam, hwnd, hTreeCtrl, hListCtrl, pathName);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}


