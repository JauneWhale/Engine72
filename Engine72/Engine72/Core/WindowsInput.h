#pragma once

#include "CommonUtil.h"
#include <DirectXMath.h>

/// <summary>
/// 输入处理，控制了所有窗口允许的逻辑输入，
/// 使用代理托管的形式管理触发事件，目前通过继承扩展
/// </summary>
class WindowsInput
{
protected:
    HWND mhMainWnd;
    POINT mLastMousePos;

public:
    WindowsInput(HWND targetWnd) : mhMainWnd(targetWnd), mLastMousePos() {}
    WindowsInput(WindowsInput&&) = delete;

    // Convenience overrides for handling mouse input.
    virtual void OnMouseDown(WPARAM btnState, int x, int y);
    virtual void OnMouseUp(WPARAM btnState, int x, int y);
    virtual void OnMouseMove(WPARAM btnState, int x, int y);
};

class DragMouseRotateInput : public WindowsInput
{
protected:
    float mScaleUnit = 0.005f;

public:
    float mTheta = 1.5f * DirectX::XM_PI;
    float mPhi = DirectX::XM_PIDIV4;
    float mRadius = 5.0f;

    DragMouseRotateInput(HWND targetWnd) : WindowsInput(targetWnd) {}

    // Convenience overrides for handling mouse input.
    virtual void OnMouseMove(WPARAM btnState, int x, int y) override;
};