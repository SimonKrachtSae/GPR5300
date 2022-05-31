#include "DlgBoxHndl.h"
#include "DlgExchData.h"
#include "resource.h"
#include <string>
#include <iostream>

using namespace std;

INT DlgBoxHndl::init(int desc)
{
	HMODULE hModule = 0;

	HINSTANCE hInst = hModule;

	HRSRC hrsrc = ::FindResource(hModule,
		MAKEINTRESOURCE(desc), RT_DIALOG);

	HGLOBAL hglobal = LoadResource(hModule, hrsrc);
	_hWnd = CreateDialogIndirect(hInst, (LPCDLGTEMPLATE)hglobal, 0, (DLGPROC)dlgProc);

	IsLoaded = TRUE;

	ShowWindowAsync(_hWnd, 1);

	return 0;
}

BOOL DlgBoxHndl::run()
{
	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message != WM_QUIT;
}

void DlgBoxHndl::deInit()
{
	IsLoaded = FALSE;
	DestroyWindow(_hWnd);
}

LRESULT CALLBACK dlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	BOOL succeeded;
	switch (Msg)
	{

	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
	{

		if (LOWORD(wParam) >= IDC_EDITAMBIENTX && LOWORD(wParam) <= IDC_EDITLIGHTPOSZ)
		{
			HWND hWnd = GetDlgItem(hDlg, LOWORD(wParam));

			if (!IsWindowVisible(hWnd))
				return TRUE;


			UINT val = GetDlgItemInt(hDlg, LOWORD(wParam), &succeeded, TRUE);

			if (!succeeded)
			{
				TCHAR buff[1040];

				LPWSTR text = {};
				GetDlgItemText(hDlg, LOWORD(wParam), buff,1040);
				
				wstring str = wstring(buff);

				if (str.length() == 0 || str == L"-")
					return TRUE;
				
				MessageBox(hDlg, str.c_str(), L"Error", MB_OK);
				SetDlgItemText(hDlg, LOWORD(wParam), L"0");
				return TRUE;
			}

			DlgExchData::shared_instance().TargetVal = (FLOAT)val;
		}
		DlgExchData::shared_instance().Val = LOWORD(wParam);
		return TRUE;
	}
	}

	return 0;
}