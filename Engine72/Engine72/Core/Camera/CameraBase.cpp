#include "CameraBase.h"


void CameraBase::UpdatePerpsectiveFovLH(float fovAngle, int width, int height, float nearZ, float farZ)
{
    if (width != mCameraWidth || height != mCameraHeight)
    {
        XMMATRIX P = XMMatrixPerspectiveFovLH(fovAngle * MathHelper::Pi, GetAspectRatio(width, height), nearZ, farZ);
        XMStoreFloat4x4(&mProj, P);
    }
}

XMMATRIX CameraBase::GetWorldViewProj() const
{
    XMMATRIX view = XMLoadFloat4x4(&mView);
    XMMATRIX world = XMLoadFloat4x4(&mWorld);
    XMMATRIX proj = XMLoadFloat4x4(&mProj);
    return world * view * proj;
}


void RotatScaleCamera::UpdateCamera(float radius, float phi, float theta)
{
    // Convert Spherical to Cartesian coordinates.
    mEyePos.x = radius * sinf(phi) * cosf(theta);
    mEyePos.z = radius * sinf(phi) * sinf(theta);
    mEyePos.y = radius * cosf(phi);

    // Build the view matrix.
    XMVECTOR pos = XMVectorSet(mEyePos.x, mEyePos.y, mEyePos.z, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&mView, view);
}