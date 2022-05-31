#pragma once
#include "AppManager.h"
#include "resource.h"
#include "DlgExchData.h"
#include <Windows.h>
#include "Mesh.h"
#include "DlgBoxHndl.h"
#include "Utils.h"

void AppManager::Init()
{
	startDlg.init(IDD_DIALOG1);
}

int AppManager::InitD3D(HINSTANCE hInstance)
{
	INT error = 0;
	UINT width = 1024;
	UINT height = 768;
	BOOL isFullscreen = FALSE;

	if (!Window.IsInitialized)
	{
		error = Window.init(hInstance, 1024, 768);
		CheckError(error);
	}
	else
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
	}
	error = D3d.init(Window.getWindowHandle(), 1024, 768, FALSE);
	CheckError(error);

	// 4. create camera
	error = Camera.init(width, height);
	CheckError(error);

	// 5. set up time
	error = Time.init();
	CheckError(error);


	for (int i = 0; i < 3; i++)
	{
		shapes[i]->init(&D3d);
	}

	currentShape = shapes[1];

	currentShape->InitMesh(D3d.getDevice(), 0, 0, 0);

	return 0;
}

void AppManager::InitSceneView()
{
	INT error = 0;
	DeInitMeshes();

	shapes[0]->InitMesh(D3d.getDevice(), -2.0f, 0.0f, 0.0f);
	shapes[1]->InitMesh(D3d.getDevice(), 0.0f, 0.0f, 0.0f);
	shapes[2]->InitMesh(D3d.getDevice(), 2.0f, 0.0f, 0.0f);
	DlgExchData::shared_instance().Val = 0;
}

void AppManager::UpdateD3D()
{
	// 8.1 update objects
	Time.update();
	Camera.update(Time.getDeltaTime());
	for (int i = 0; i < 3; i++)
	{
		if (shapes[i]->Mesh.IsInitialized && shapes[i]->Material.IsInitialized)
			shapes[i]->Mesh.update(Time.getDeltaTime());
	}

	// 8.2 draw objects
	D3d.beginScene(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 3; i++)
	{
		if (shapes[i]->Mesh.IsInitialized && shapes[i]->Material.IsInitialized)
		{
			shapes[i]->Material.render(D3d.getDeviceContext(), shapes[i]->Mesh.getWorldMatrix(), Camera.getViewMatrix(), Camera.getProjectionMatrix());
			shapes[i]->Light.render(D3d.getDeviceContext());
			shapes[i]->Mesh.render(D3d.getDeviceContext());
		}
	}

	D3d.endScene();
}

BOOL AppManager::UpdateStartDlg()
{
	startDlg.run();

	switch (DlgExchData::shared_instance().Val)
	{

	case IDC_QUITAPP:
		IsRunning = FALSE;
		startDlg.deInit();
		DlgExchData::shared_instance().Val = 0;
		return FALSE;

	case IDC_HELPSTART:
		DisplayResourceNAMessageBox
		(
			L"Welcome! \nClick on 'ObjEdit', to edit objects individually.\nClick on 'SceneView', to view Objects in Scene. \nClick 'Quit' to end application.",
			L"Help"
		);
		break;

	case IDC_OBJECTEDITOR:
		startDlg.deInit();
		DlgExchData::shared_instance().View = IDC_OBJECTEDITOR;
		objEditDlg.init(IDD_DIALOG2);
		DlgExchData::shared_instance().Val = 0;
		return FALSE;

	case IDC_SCENEVIEW:
		startDlg.deInit();
		sceneViewDlg.init(IDD_DIALOG3);
		DlgExchData::shared_instance().View = IDC_SCENEVIEW;
		DlgExchData::shared_instance().Val = 0;
		return FALSE;
	}
	DlgExchData::shared_instance().Val = 0;
	DlgExchData::shared_instance().View = 0;
	return TRUE;
}
BOOL AppManager::UpdateObjEditDlg()
{
	if (advSettingsDlg.IsLoaded)
	{
		UpdateAdvSettingsDlg();
		return TRUE;
	}
	else
	{
		objEditDlg.run();
	}

	switch (DlgExchData::shared_instance().Val)
	{
	case 0:
		return TRUE;

	case IDC_ADVSETTINGS:
	{
		advSettingsDlg.init(IDD_DIALOG4, &currentShape->LightData, currentShape->Shader);
		return TRUE;
	}

	case IDC_HELPOBJEDIT:
		DisplayResourceNAMessageBox
		(
			L"Instructions: \n1) Select Shape \n2) Apply Texture and /or Shader \n3) Press Back to Finish Editing \n\nControls: \nW: Zoom out \nS: Zoom in \nShift + A: Rotate Left \nShift + D: Rotate Right \nShift + W: Rotate Backwards \nShift + S: Rotate Forward",
			L"Help"
		);
		DlgExchData::shared_instance().Val = 0;
		return TRUE;

	//go back to start menu
	case IDC_BACK:
		objEditDlg.deInit();
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		DlgExchData::shared_instance().Val = 0;
		DlgExchData::shared_instance().View = 0;
		return FALSE;
	case IDC_LOADPLANE:
		DeInitMeshes();
		shapes[0]->InitMesh(D3d.getDevice(), 0, 0, 0);
		currentShape = shapes[0];
		DlgExchData::shared_instance().Val = 0;
		return TRUE;

	case IDC_LOADCUBE:
		DeInitMeshes();
		shapes[1]->InitMesh(D3d.getDevice(), 0, 0, 0);
		currentShape = shapes[1];
		DlgExchData::shared_instance().Val = 0;
		return TRUE;

	case IDC_LOADPYRAMID:
		DeInitMeshes();
		shapes[2]->InitMesh(D3d.getDevice(), 0, 0, 0);
		currentShape = shapes[2];
		DlgExchData::shared_instance().Val = 0;
		return TRUE;

	case IDC_LAMBERTIAN:
		if (currentShape->Material.IsInitialized)
			currentShape->Material.deInit();

		currentShape->Material.init(D3d.getDevice(), currentShape->Texture, IDC_LAMBERTIAN);
		currentShape->Shader = IDC_LAMBERTIAN;

		DlgExchData::shared_instance().Val = 0;

		return TRUE;

	case IDC_BLINNPHONG:
		if (currentShape->Material.IsInitialized)
			currentShape->Material.deInit();

		currentShape->Material.init(D3d.getDevice(), currentShape->Texture, IDC_BLINNPHONG);
		currentShape->Shader = IDC_BLINNPHONG;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;

	case IDC_PHONG:
		if (currentShape->Material.IsInitialized)
			currentShape->Material.deInit();

		currentShape->Material.init(D3d.getDevice(), currentShape->Texture, IDC_PHONG);
		currentShape->Shader = IDC_PHONG;

		DlgExchData::shared_instance().Val = 0;

		return TRUE;

	case IDC_STONES:
		if (currentShape->Material.IsInitialized)
			currentShape->Material.deInit();

		currentShape->Material.init(D3d.getDevice(), IDC_STONES, currentShape->Shader);
		currentShape->Texture = IDC_STONES;

		DlgExchData::shared_instance().Val = 0;

		return TRUE;

	case IDC_ALUMINIUM:
		if (currentShape->Material.IsInitialized)
			currentShape->Material.deInit();

		currentShape->Material.init(D3d.getDevice(), IDC_ALUMINIUM, currentShape->Shader);
		currentShape->Texture = IDC_ALUMINIUM;

		DlgExchData::shared_instance().Val = 0;

		return TRUE;

	case IDC_WOOD:
		if (currentShape->Material.IsInitialized)
			currentShape->Material.deInit();

		currentShape->Material.init(D3d.getDevice(), IDC_WOOD, currentShape->Shader);
		currentShape->Texture = IDC_WOOD;
		DlgExchData::shared_instance().Val = 0;
		return TRUE;
	}
	DlgExchData::shared_instance().Val = 0;
	DlgExchData::shared_instance().View = 0;
	return TRUE;
}

BOOL AppManager::UpdateSceneView()
{
	switch (DlgExchData::shared_instance().Val)
	{
	case IDC_BACK:
		sceneViewDlg.deInit();
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		DlgExchData::shared_instance().Val = 0;
		DlgExchData::shared_instance().View = 0;
		return FALSE;

	case IDC_HELPSCENEVIEW:
		DisplayResourceNAMessageBox
		(
			L"Controls: \nW: Zoom out \nS: Zoom in \nShift + A: Rotate Left \nShift + D: Rotate Right \nShift + W: Rotate Backwards \nShift + S: Rotate Forward",
			L"Help"
		);
		DlgExchData::shared_instance().Val = 0;
		break;
	}
	return TRUE;
}

BOOL AppManager::UpdateAdvSettingsDlg()
{
	advSettingsDlg.run();
	switch (DlgExchData::shared_instance().Val)
	{
	case IDC_APPLY:
		currentShape->Light.deInit();
		currentShape->Light.init(D3d.getDevice(), currentShape->LightData);

		DlgExchData::shared_instance().Val = 0;

		return TRUE;
	case IDC_FINISH:
		advSettingsDlg.deInit();
		return FALSE;
	}
	DlgExchData::shared_instance().Val = 0;
	DlgExchData::shared_instance().View = 0;
	return TRUE;
}

void AppManager::DeInit()
{
	DeInitMeshes();
	for (int i = 0; i < 3; i++)
	{
		shapes[i]->deInit();
	}

	Time.deInit();
	Camera.deInit();
	D3d.deInit();
}

void AppManager::DeInitMeshes()
{
	for (int i = 0; i < 3; i++)
	{
		shapes[i]->Mesh.deInit();
		shapes[i]->SetDefaultPos();
	}
}

int AppManager::DisplayResourceNAMessageBox(LPCWSTR text, LPCWSTR header)
{
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox

	int msgboxID = MessageBox(
		NULL,
		text,
		header,
		MB_OK
	);
	return msgboxID;
}