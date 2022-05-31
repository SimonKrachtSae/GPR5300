#include <Windows.h>
#include "DlgBoxHndl.h"
#include "resource.h"
#include "DlgExchData.h"
#include "AppManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{

	AppManager appManager = {};


	while (appManager.IsRunning)
	{
		appManager.Init();

		while (appManager.UpdateStartDlg())
		{
			Sleep(5);
		}

		if (!appManager.D3d.IsInitialized)
		{
			appManager.InitD3D(hInstance);
		}

		switch (DlgExchData::shared_instance().View)
		{
		case IDC_OBJECTEDITOR:
			while (appManager.Window.run() && appManager.UpdateObjEditDlg())
			{
				appManager.UpdateD3D();
			}
			break;

		case IDC_SCENEVIEW:
			appManager.InitSceneView();

			while (appManager.Window.run() && appManager.UpdateSceneView())
			{
				appManager.UpdateD3D();
			}
			break;

		default:
			break;
		}
	}
	appManager.DeInit();
	appManager.Window.deInit();

	return 0;
}