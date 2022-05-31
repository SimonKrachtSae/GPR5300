#include <d3d11.h>
#include <string>
#include "Light.h"

using namespace std;

class AdvSettingsDlgHndl
{
public:
	//FrameWork
	INT init(int desc, Light::LightData *_lightData, int lightDesc);
	BOOL run();
	void deInit();

	HWND getDlgWindowHandle() { return _hWnd; }

	Light::LightData* lightData = {};;

	//Custom

	/// <summary>
	/// Checks if the given input value is within a specific range. If not, it will set the value to the closest value in range. Finally it will post this value to the corresponding edit control.
	/// </summary>
	/// <param name="val">-> The Input Value</param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <param name="hWnd">->HWND of edit control</param>
	void CheckRange(int val,int min, int max, HWND hWnd);

	/// <summary>
	/// Gets called when this dialog is initialized. Gets corresponding DlgItem for each member of the current <c>Light::LightData</c>.
	/// </summary>
	void DrawValues(int lightDesc);

	/// <summary>
	/// Takes in a FLOAT value, converts it, and then returns it as a wstring.
	/// </summary>
	/// <param name="fl"></param>
	/// <returns></returns>
	wstring FLOAT_to_wstring(FLOAT fl);

	BOOL IsLoaded = FALSE;

private:
	//FrameWork
	HWND _hWnd = nullptr;
	int dwPos = 0;
};

LRESULT CALLBACK dlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);