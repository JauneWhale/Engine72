#pragma once

#include "WinApp.h"
#include "CommonUtil.h"
#include "GameRenderer.h"
#include "Camera/CameraBase.h"

class GameLoopApp : public WinApp
{
#pragma region 功能接口
public:
    virtual ~GameLoopApp() = default;
    virtual bool Initialize() final;
protected:
    virtual void Update(const GameTimer& gt) override;
    virtual void MsgProcOnKeyUp(int key) override;
    virtual void OnResize() override;
    virtual void GameLogicUpdate(const GameTimer& gt) {} // TOO(zrz): should I use "= 0"?
#pragma endregion
    
public:
    GameLoopApp(HINSTANCE hInstance, GameRenderer* gameRenderer) : 
        WinApp(hInstance), mGameRenderer(gameRenderer), mMainCamera(nullptr) { };
    GameLoopApp(HINSTANCE hInstance, GameRenderer* gameRenderer, CameraBase* mainCamera) :
        WinApp(hInstance), mGameRenderer(gameRenderer), mMainCamera(mainCamera) { };

protected:
    // Renderer
    std::unique_ptr<GameRenderer> mGameRenderer;
    // Logic
    CameraBase* mMainCamera;
};
