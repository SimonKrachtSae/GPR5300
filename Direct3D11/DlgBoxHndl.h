#pragma once
#include "resource.h"
#include <d3d11.h>
#include <string>
using namespace std;

class DlgBoxHndl
{
public:
	INT init(int desc);
	BOOL run();
	void deInit();

	BOOL IsLoaded = FALSE;
	BOOL IsShapeSelected = FALSE;

	HWND getDlgWindowHandle() { return _hWnd; }
	HWND getListBoxHandle() { return hwndList; }

private:
	HWND hwndList = nullptr;
	HWND _hWnd = nullptr;
};

LRESULT CALLBACK dlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

