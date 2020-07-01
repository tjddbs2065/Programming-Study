#include <Windows.h>
#include <tchar.h>
#include <ShlObj.h>
#include <time.h>

#include "resource.h"
BOOL SelectSaveFile(HWND hwnd, TCHAR* file);
BOOL SelectOpenFile(HWND hwnd, TCHAR* file);
BOOL SelectFolder(TCHAR* folder);
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_COLOR), NULL, DlgProc);

	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR buffer[MAX_PATH] = { 0, };
	HDC hdc;
	PAINTSTRUCT ps = { 0, };
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static COLORREF brushColor = RGB(192, 192, 192);
	RECT rect = { 10, 10, 450, 100 };
	static int r =0, g = 0, b=0;
	switch (iMsg)
	{
	case WM_TIMER:
		if (r < 255) { r += 5; }
		else if (g < 255) { g += 5; }
		else if (r > 0) { 
			r -= 5; 
		}

		else {
			r = g = b = 0;
			KillTimer(hwnd, 1);
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_START), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_STOP), FALSE);
		}brushColor = RGB(r, g, b);
		InvalidateRect(hwnd, &rect, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(brushColor);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		hPen = CreatePen(PS_SOLID, 5, RGB(192, 192, 192));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);

		EndPaint(hwnd, &ps);
		break;
	case WM_INITDIALOG:
		srand((unsigned int)time(NULL));
		EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_STOP), FALSE);
		EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_START), TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_STOP:
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_START), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_STOP), FALSE);
			KillTimer(hwnd, 1);
			break;
		case IDC_BUTTON_START:
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_START), FALSE);
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_STOP), TRUE);
			SetTimer(hwnd, 1, 70, NULL);

			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}
