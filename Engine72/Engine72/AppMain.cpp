
#include "Core/D3DApp.h"
#include "TestApp/TestApp.h"

//using ValidateApp = WinApp;
//using ValidateApp = InitDirect3DApp;
using ValidateApp = BoxApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	CreateCRTDbgContext();

	try
	{
		ValidateApp theApp(hInstance);
		if (!theApp.Initialize())
			return 0;

		return theApp.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}