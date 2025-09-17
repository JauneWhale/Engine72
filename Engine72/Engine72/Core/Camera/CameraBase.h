#pragma once
#include <DirectXMath.h>

#include "../CommonUtil.h"
#include "../MathHelper.h"
#include "../WindowsInput.h"

using namespace DirectX;

class CameraBase
{
    // virtual接口
public:
    virtual void UpdateCamera(float radius, float phi, float theta) = 0;

public:
    CameraBase() = default;
    virtual ~CameraBase() = default;

    XMMATRIX GetWorldViewProj() const;
    void UpdatePerpsectiveFovLH(float fovAngle, int width, int height, float nearZ, float farZ);

protected:
    int mCameraWidth;
    int mCameraHeight;

    //XMVECTOR mPosition;
    //XMVECTOR mForward;
    //XMVECTOR mUp;

    XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();
};

class RotatScaleCamera : public CameraBase
{
    // 实现接口
public:
    virtual void UpdateCamera(float radius, float phi, float theta);

public:
    RotatScaleCamera() = default;
    virtual ~RotatScaleCamera() = default;
};