#pragma once
#include "Light.h"
#include "Material.h"
#include "Time.h"
#include "Camera.h"
#include "Mesh.h"
#include "D3D.h"
#include "Window.h"
#include "DlgBoxHndl.h"
#include "Shape.h"
#include "AdvSettingsDlg.h"

/// <summary>
/// Manages the Application and its main Components.
/// Main Tasks: Managing dialogs and main window, Managing Dialog Control Commands
/// </summary>
class AppManager
{
public:
	//Original FrameWork:
	Window Window = {};
	D3D D3d = {};
	Camera Camera = {};
	Time Time = {};

	//CUSTOMS:

	BOOL IsRunning = TRUE;

	/// <summary>
	/// Opens the start dialog.
	/// </summary>
	void Init();

	/// <summary>
	/// Init graphics rendering components for all Objects.
	/// </summary>
	/// <param name="hInstance"></param>
	int InitD3D(HINSTANCE hInstance);

	/// <summary>
	/// Initializes the mesh for each object in our scene.
	/// </summary>
	void InitSceneView();

	/// <summary>
	/// Update graphics rendering components for currently initialized objects.
	/// </summary>
	void UpdateD3D();

	/// <summary>
	/// Updates the start Dialog at runtime.
	/// </summary>
	/// <returns>
	/// Returns true, if nothing has been selected.
	/// Returns false, if a button has been clicked (except for "Help").
	/// </returns>
	BOOL UpdateStartDlg();

	/// <summary>
	/// Updates the object editor dialog at runtime.
	/// </summary>
	/// <returns>
	/// Returns true, except, when the "Back" button has been clicked.
	/// </returns>
	BOOL UpdateObjEditDlg();

	/// <summary>
	/// Update scene view at runtime.
	/// </summary>
	/// <returns>
	/// Returns true, except, when the "Back" button has been clicked.
	/// </returns>
	BOOL UpdateSceneView();


	/// <summary>
	/// Updates the Advanced Settings Dialog at runtima
	/// </summary>
	/// <returns>Returns FALSE, if back button has been pressed.</returns>
	BOOL UpdateAdvSettingsDlg();

	/// <summary>
	/// Deinitializes graphics rendering components, when quitting the application.
	/// </summary>
	void DeInit();

private:

	Plane plane = {};
	Cube cube = {};
	Pyramid pyramid = {};

	Shape* shapes[3] = { &plane,&cube,&pyramid };
	Shape* currentShape = nullptr;

	//Custom:

	/// <summary>
	/// Used for editing objects individually.
	/// </summary>
	DlgBoxHndl objEditDlg = {};

	/// <summary>
	/// Manages Startup menu.
	/// </summary>
	DlgBoxHndl startDlg = {};

	/// <summary>
	/// Manages the sceneview menu.
	/// <see cref="AppManager::RunSceneView"/>
	/// </summary>
	DlgBoxHndl sceneViewDlg = {};

	/// <summary>
	/// Used for setting specific data on Object.
	/// </summary>
	AdvSettingsDlgHndl advSettingsDlg = {};

	/// <summary>
	/// Deinitializes the mesh for each object.
	/// </summary>
	void DeInitMeshes();

	/// <summary>
	/// Generic method for displaying informational messageboxes.
	/// </summary>
	/// <param name="text">Text to be displayed.</param>
	/// <param name="header">Header at the top of the Box.</param>
	/// <returns>Returns the ID of the messagebox.</returns>
	int DisplayResourceNAMessageBox(LPCWSTR text, LPCWSTR header);
};