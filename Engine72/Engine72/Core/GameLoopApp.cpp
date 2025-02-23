#include "GameLoopApp.h"

using namespace std;

GameLoopApp::~GameLoopApp()
{
	assert(mGameRenderer);
	delete mGameRenderer;
}

bool GameLoopApp::Initialize()
{
	if (!WinApp::Initialize())
		return false;

	assert(mGameRenderer);
	mIsRendererApp = true;

	if (!mGameRenderer->InitializeRenderer(mClientWidth, mClientHeight, mhMainWnd))
		return false;

	return true;
}

void GameLoopApp::Paint(const GameTimer& gt)
{
	// Game Logic Update
	Update(mTimer);

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