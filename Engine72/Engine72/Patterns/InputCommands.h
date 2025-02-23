#pragma once

#include "../Core/CommonUtil.h"
#include <DirectXMath.h>

template<typename... Args>
class InputCommand
{
public:
    virtual void Process(Args ... data) = 0;
};

class DragMouseRotateCommand : public InputCommand<WPARAM, int, int>
{
protected:
    float mScaleUnit = 0.005f;
public:
    DragMouseRotateCommand(float scaleUnit = 0.005f) : mScaleUnit(scaleUnit) {}
    virtual void Process(WPARAM btnState, int x, int y) override;

    float mTheta = 1.5f * DirectX::XM_PI;
    float mPhi = DirectX::XM_PIDIV4;
    float mRadius = 5.0f;
};