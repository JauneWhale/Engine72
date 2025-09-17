#include "WindowsInput.h"
#include "../Core/MathHelper.h"

void WindowsInput::OnMouseDown(WPARAM btnState, int x, int y)
{
    mLastMousePos.x = x;
    mLastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void WindowsInput::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void WindowsInput::OnMouseMove(WPARAM btnState, int x, int y)
{
    mLastMousePos.x = x;
    mLastMousePos.y = y;
}

void DragMouseRotateInput::OnMouseMove(WPARAM btnState, int x, int y)
{
    int diffX = x - mLastMousePos.x;
    int diffY = y - mLastMousePos.y;
    WindowsInput::OnMouseMove(btnState, x, y);

    // 触发MouseDragging事件
    if ((btnState & MK_LBUTTON) != 0)
    {
        // Make each pixel correspond to a quarter of a degree.
        float dx = DirectX::XMConvertToRadians(0.25f * static_cast<float>(diffX));
        float dy = DirectX::XMConvertToRadians(0.25f * static_cast<float>(diffY));

        // Update angles based on input to orbit camera around box.
        mTheta += dx;
        mPhi += dy;

        // Restrict the angle mPhi.
        mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
    }
    else if ((btnState & MK_RBUTTON) != 0)
    {
        // Make each pixel correspond to 0.005 unit in the scene.
        float dx = mScaleUnit * static_cast<float>(diffX);
        float dy = mScaleUnit * static_cast<float>(diffY);

        // Update the camera radius based on input.
        mRadius += dx - dy;

        // Restrict the radius.
        mRadius = MathHelper::Clamp(mRadius, 3.0f, 15.0f);
    }
}