#include "GameLoopApp.h"

using namespace std;

/// <summary>
/// 初始化入口，这里作为LoopApp的实现，需要做到
/// - 调用基类代码初始化窗口
/// - 初始化Renderer
/// </summary>
/// <returns></returns>
bool GameLoopApp::Initialize()
{
	if (!WinApp::Initialize())
		return false;

	assert(mGameRenderer);

	if (!mGameRenderer->InitializeRenderer(mClientWidth, mClientHeight, mhMainWnd))
		return false;

	return true;
}

void GameLoopApp::Update(const GameTimer& gt)
{
	// Game Logic Update
	LogicUpdate(mTimer);

	// Renderer Update
	mGameRenderer->Render(mTimer, mMainCamera);
}

void GameLoopApp::MsgProcOnKeyUp(int key)
{
	// TODO(zrz):
	// Logic part for input msg parsing

	// Renderer Debug Input
	// TODO(zrz): Input system can only control the logci part, then the data will be passed to the renderer
	mGameRenderer->MsgProcOnKeyUp(key);
}

void GameLoopApp::OnResize()
{
	// Renderer Update
	mGameRenderer->OnResize(mClientWidth, mClientHeight);
}