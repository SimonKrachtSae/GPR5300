#pragma once
#include <Windows.h>
#include "AdvSettingsDlg.h"
#include "resource.h"
#include <string>
#include "DlgExchData.h"

INT AdvSettingsDlgHndl::init(int desc, Light::LightData* _lightData, int lightDesc)
{
	lightData = _lightData;
	HMODULE hModule = 0;

	HINSTANCE hInst = hModule;

	HRSRC hrsrc = ::FindResource(hModule,
		MAKEINTRESOURCE(desc), RT_DIALOG);

	HGLOBAL hglobal = LoadResource(hModule, hrsrc);
	_hWnd = CreateDialogIndirectParam(hInst, (LPCDLGTEMPLATE)hglobal, nullptr, (DLGPROC)dlgProc, 0);

	DrawValues(lightDesc);
	ShowWindowAsync(_hWnd, 1);

	IsLoaded = TRUE;

	return 0;
}

BOOL AdvSettingsDlgHndl::run()
{
	switch (DlgExchData::shared_instance().Val)
	{
	case IDC_EDITLIGHTINTENSITY:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITLIGHTINTENSITY));
		lightData->lightIntensity = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITSURRLIGHTINTENSITY:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITSURRLIGHTINTENSITY));
		lightData->surrLightIntensity = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITLIGHTPOSX:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, -1, 1, GetDlgItem(_hWnd, IDC_EDITLIGHTPOSX));
		lightData->lightPosition.x = DlgExchData::shared_instance().TargetVal;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITLIGHTPOSY:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, -1, 1, GetDlgItem(_hWnd, IDC_EDITLIGHTPOSY));
		lightData->lightPosition.y = DlgExchData::shared_instance().TargetVal;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITLIGHTPOSZ:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, -1, 1, GetDlgItem(_hWnd, IDC_EDITLIGHTPOSZ));
		lightData->lightPosition.z = DlgExchData::shared_instance().TargetVal;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITSURFACETEX:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 200, GetDlgItem(_hWnd, IDC_EDITSURFACETEX));
		lightData->surfaceTex= DlgExchData::shared_instance().TargetVal;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITAMBIENTX:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITAMBIENTX));
		lightData->matAmbient.x = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITAMBIENTY:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITAMBIENTY));
		lightData->matAmbient.y = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITAMBIENTZ:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITAMBIENTZ));
		lightData->matAmbient.z = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITDIFFUSEX:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITDIFFUSEX));
		lightData->matDiffuse.x = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITDIFFUSEY:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITDIFFUSEY));
		lightData->matDiffuse.y = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITDIFFUSEZ:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITDIFFUSEZ));
		lightData->matDiffuse.z = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITSPECULARX:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITSPECULARX));
		lightData->matSpecular.x = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITSPECULARY:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITSPECULARY));
		lightData->matSpecular.y = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	case IDC_EDITSPECULARZ:
		CheckRange((int)DlgExchData::shared_instance().TargetVal, 0, 100, GetDlgItem(_hWnd, IDC_EDITSPECULARZ));
		lightData->matSpecular.z = DlgExchData::shared_instance().TargetVal / 100;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	}

	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message != WM_QUIT;
}

void AdvSettingsDlgHndl::deInit()
{
	IsLoaded = FALSE;
	DestroyWindow(_hWnd);
}

void AdvSettingsDlgHndl::CheckRange(int val, int min, int max, HWND hWnd)
{
	if (val < min)
	{
		val = min;
		
		MessageBox(_hWnd, L"Value was out of range!", L"ERROR", 0);
		SetWindowText(hWnd, (LPCWSTR)to_wstring(min).c_str());
	}
	else if(val > max)
	{
		MessageBox(_hWnd, L"Value was out of range!", L"ERROR", 0);
		SetWindowText(hWnd, (LPCWSTR)to_wstring(max).c_str());
		val = max;
	}
}

void AdvSettingsDlgHndl::DrawValues(int lightDesc)
{
	HWND editLightIntensity = GetDlgItem(_hWnd, IDC_EDITLIGHTINTENSITY);
	SetWindowText(editLightIntensity, (LPCWSTR)to_wstring((int)(lightData->lightIntensity * 100)).c_str());

	if(lightDesc == IDC_PHONG || lightDesc == IDC_BLINNPHONG)
	{
		HWND editSurrLightIntensity = GetDlgItem(_hWnd, IDC_EDITSURRLIGHTINTENSITY);
		ShowWindow(editSurrLightIntensity, TRUE);
		SetWindowText(editSurrLightIntensity, (LPCWSTR)to_wstring((int)(lightData->surrLightIntensity * 100)).c_str());
	
	}

	if (lightDesc == IDC_PHONG || lightDesc == IDC_BLINNPHONG)
	{

		HWND editLightDirX = GetDlgItem(_hWnd, IDC_EDITLIGHTPOSX);
		ShowWindow(editLightDirX,TRUE);
		SetWindowText(editLightDirX, (LPCWSTR)to_wstring((int)lightData->lightPosition.x).c_str());

		HWND editLightDirY = GetDlgItem(_hWnd, IDC_EDITLIGHTPOSY);
		ShowWindow(editLightDirY,TRUE);
		SetWindowText(editLightDirY, (LPCWSTR)to_wstring((int)lightData->lightPosition.y).c_str());

		HWND editLightDirZ = GetDlgItem(_hWnd, IDC_EDITLIGHTPOSZ);
		ShowWindow(editLightDirZ,TRUE);
		SetWindowText(editLightDirZ, (LPCWSTR)to_wstring((int)lightData->lightPosition.z).c_str());
	}

	if (lightDesc == IDC_PHONG || lightDesc == IDC_BLINNPHONG)
	{
		HWND editAmbientX = GetDlgItem(_hWnd, IDC_EDITAMBIENTX);
		ShowWindow(editAmbientX, TRUE);
		SetWindowText(editAmbientX, (LPCWSTR)to_wstring((int)(lightData->matAmbient.x * 100)).c_str());

		HWND editAmbientY = GetDlgItem(_hWnd, IDC_EDITAMBIENTY);
		ShowWindow(editAmbientY, TRUE);
		SetWindowText(editAmbientY, (LPCWSTR)to_wstring((int)(lightData->matAmbient.y * 100)).c_str());

		HWND editAmbientZ = GetDlgItem(_hWnd, IDC_EDITAMBIENTZ);
		ShowWindow(editAmbientZ, TRUE);
		SetWindowText(editAmbientZ, (LPCWSTR)to_wstring((int)(lightData->matAmbient.z) * 100).c_str());

		HWND editDiffuseX = GetDlgItem(_hWnd, IDC_EDITDIFFUSEX);
		ShowWindow(editDiffuseX, TRUE);
		SetWindowText(editDiffuseX, (LPCWSTR)to_wstring((int)(lightData->matDiffuse.x * 100)).c_str());

		HWND editDiffuseY = GetDlgItem(_hWnd, IDC_EDITDIFFUSEY);
		ShowWindow(editDiffuseY, TRUE);
		SetWindowText(editDiffuseY, (LPCWSTR)to_wstring((int)(lightData->matDiffuse.y * 100)).c_str());

		HWND editDiffuseZ = GetDlgItem(_hWnd, IDC_EDITDIFFUSEZ);
		ShowWindow(editDiffuseZ, TRUE);
		SetWindowText(editDiffuseZ, (LPCWSTR)to_wstring((int)(lightData->matDiffuse.z * 100)).c_str());

		HWND editSpecularX = GetDlgItem(_hWnd, IDC_EDITSPECULARX);
		ShowWindow(editSpecularX, TRUE);
		SetWindowText(editSpecularX, (LPCWSTR)to_wstring((int)(lightData->matSpecular.x * 100)).c_str());

		HWND editSpecularY = GetDlgItem(_hWnd, IDC_EDITSPECULARY);
		ShowWindow(editSpecularY, TRUE);
		SetWindowText(editSpecularY, (LPCWSTR)to_wstring((int)(lightData->matSpecular.y * 100)).c_str());

		HWND editSpecularZ = GetDlgItem(_hWnd, IDC_EDITSPECULARZ);
		ShowWindow(editSpecularZ, TRUE);
		SetWindowText(editSpecularZ, (LPCWSTR)to_wstring((int)(lightData->matSpecular.z * 100)).c_str());
		
		HWND editSurfaceTex = GetDlgItem(_hWnd, IDC_EDITSURFACETEX);
		ShowWindow(editSurfaceTex, TRUE);
		SetWindowText(editSurfaceTex, (LPCWSTR)to_wstring((int)lightData->surfaceTex).c_str());
	}


}

std::wstring AdvSettingsDlgHndl::FLOAT_to_wstring(FLOAT fl)
{
	std::string str = std::to_string(fl);
	if (str.at(0) == '-')
	{
		str = std::to_string(fl).substr(0, 5);
	}
	else 
	{
		str = std::to_string(fl).substr(0, 4);
	}
	std::wstring widestr = std::wstring(str.begin(), str.end());
	return widestr;
}
