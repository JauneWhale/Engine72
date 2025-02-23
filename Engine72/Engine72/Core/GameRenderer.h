﻿#pragma once

#include "CommonUtil.h"
#include "GameTimer.h"
#include "Camera/CameraBase.h"

class GameRenderer
{
public:
    GameRenderer() {};
    virtual ~GameRenderer() {}

public:
    virtual bool InitializeRenderer(int clientWidth, int clientHeight, HWND targetWnd) = 0;
    virtual void OnResize(int newWidth, int newHeight) = 0;
    virtual void Render(const GameTimer& gt, const CameraBase* camera) = 0;
    virtual void MsgProcOnKeyUp(int key) = 0;
};
