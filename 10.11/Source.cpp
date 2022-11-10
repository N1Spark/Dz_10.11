#include <windows.h>
#include <tchar.h>
#include <windowsX.h>
#include "resource.h"
#include "Time.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND hList, hButton, hEdit, hVar1, hVar2, hVar3;
int sum = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		static int count_num = rand() % 10 + 10;
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		hVar1 = GetDlgItem(hWnd, IDC_RADIO1);
		hVar2 = GetDlgItem(hWnd, IDC_RADIO2);
		hVar3 = GetDlgItem(hWnd, IDC_RADIO3);
		for (int i = 0; i < count_num;)
		{
			int buf = rand() % (-10 - 10) - 10;
			if (buf != 0)
			{
				TCHAR BUF[10];
				wsprintf(BUF, TEXT("%d"), buf);
				SendMessage(hList, LB_ADDSTRING, 0, LPARAM(BUF));
				i++;
			}
		}
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			LRESULT result1, result2, result3;
			result1 = SendMessage(hVar1, BM_GETCHECK, 0, 0);
			result2 = SendMessage(hVar2, BM_GETCHECK, 0, 0);
			result3 = SendMessage(hVar3, BM_GETCHECK, 0, 0);
			if (result1 == BST_CHECKED)
			{
				int nCount = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
				int* p = new int[nCount];
				SendMessage(hList, LB_GETSELITEMS, nCount, LPARAM(p));
				for (int i = 0; i < nCount; i++)
				{
					int length = SendMessage(hList, LB_GETTEXTLEN, p[i], 0);
					TCHAR* pBuffer = new TCHAR[length + 1];
					SendMessage(hList, LB_GETTEXT, p[i], LPARAM(pBuffer));
					sum += _ttoi(pBuffer);
					delete[] pBuffer;
				}
				TCHAR buf[50];
				wsprintf(buf, TEXT("%d"), sum);
				SetWindowText(hEdit, buf);
				sum = 0;
			}
			if (result2 == BST_CHECKED)
			{
				sum = 1;
				int nCount = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
				int* p = new int[nCount];
				SendMessage(hList, LB_GETSELITEMS, nCount, LPARAM(p));
				for (int i = 0; i < nCount; i++)
				{
					int length = SendMessage(hList, LB_GETTEXTLEN, p[i], 0);
					TCHAR* pBuffer = new TCHAR[length + 1];
					SendMessage(hList, LB_GETTEXT, p[i], LPARAM(pBuffer));
					sum *= _ttoi(pBuffer);
					delete[] pBuffer;
				}
				TCHAR buf[50];
				wsprintf(buf, TEXT("%d"), sum);
				SetWindowText(hEdit, buf);
				sum = 0;
			}
			if (result3 == BST_CHECKED)
			{
				int nCount = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
				int* p = new int[nCount];
				SendMessage(hList, LB_GETSELITEMS, nCount, LPARAM(p));
				for (int i = 0; i < nCount; i++)
				{
					int length = SendMessage(hList, LB_GETTEXTLEN, p[i], 0);
					TCHAR* pBuffer = new TCHAR[length + 1];
					SendMessage(hList, LB_GETTEXT, p[i], LPARAM(pBuffer));
					sum += _ttoi(pBuffer);
					delete[] pBuffer;
				}
				sum /= nCount;
				TCHAR buf[50];
				wsprintf(buf, TEXT("%d"), sum);
				SetWindowText(hEdit, buf);
				sum = 0;
			}


		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}