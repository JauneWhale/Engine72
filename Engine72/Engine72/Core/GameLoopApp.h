#pragma once

#include "WinApp.h"
#include "CommonUtil.h"
#include "GameRenderer.h"
#include "Camera/CameraBase.h"

class GameLoopApp : public WinApp
{
public:
    GameLoopApp(HINSTANCE hInstance, GameRenderer* gameRenderer) : 
        WinApp(hInstance), mGameRenderer(gameRenderer), mMainCamera(nullptr) { };
    GameLoopApp(HINSTANCE hInstance, GameRenderer* gameRenderer, CameraBase* mainCamera) :
        WinApp(hInstance), mGameRenderer(gameRenderer), mMainCamera(mainCamera) { };
    virtual ~GameLoopApp();
    virtual bool Initialize() final;

protected:
    // Renderer
    GameRenderer* mGameRenderer;
    // Logic
    CameraBase* mMainCamera;

    virtual void Paint(const GameTimer& gt) override;
    virtual void MsgProcOnKeyUp(int key) override;
    virtual void OnResize() override;
    virtual void Update(const GameTimer& gt) {} // TOO(zrz): should I use "= 0"?
};
