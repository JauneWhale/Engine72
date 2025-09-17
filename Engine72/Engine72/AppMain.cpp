#include "Core/GameLoopApp.h"
#include "TestApp/TestApp.h"

/// <summary>
/// �˴��������������е�Ψһ��ڣ�����App�ֻ࣬��Ҫ������Initialize->Run
/// </summary>
/// <param name="hInstance"></param>
/// <param name="prevInstance"></param>
/// <param name="cmdLine"></param>
/// <param name="showCmd"></param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	CreateCRTDbgContext();

	try
	{
		// WinApp, InitDirect3DApp, BoxApp
		std::unique_ptr<WinApp> theApp = std::make_unique<BoxApp::BoxApp>(hInstance);
		if (!theApp->Initialize())
			return 0;

		return theApp->Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}