﻿#pragma once

#include "../GameRenderer.h"
#include "../GameTimer.h"
#include "D3DUtil.h"

// TODO(zrz): move this to make files or settings
// Link necessary d3d12 libraries.
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

class D3D12Renderer : public GameRenderer
{
public:
    D3D12Renderer() : GameRenderer() {};
    virtual ~D3D12Renderer();

public:

    bool    Get4xMsaaState()const;
    void    Set4xMsaaState(bool value);

    //virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
    virtual bool InitializeRenderer(int clientWidth, int clientHeight, HWND targetWnd) override;
    virtual void OnResize(int newWidth, int newHeight) override;
    virtual void Render(const GameTimer& gt, const CameraBase* camera) override;
    virtual void MsgProcOnKeyUp(int key) override;

    virtual void CreateRtvAndDsvDescriptorHeaps();

protected:
    HWND mLastTargetWnd; // TODO(zrz): get rid of it
    bool InitDirect3D(HWND targetWnd);
    void CreateCommandObjects();
    void CreateSwapChain(HWND targetWnd);

    void FlushCommandQueue();

    ID3D12Resource* CurrentBackBuffer()const;
    D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
    D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

#ifdef _DEBUG
    void LogAdapters();
    void LogAdapterOutputs(IDXGIAdapter* adapter);
    void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);
#endif

protected:
    int       mWindowsWidth = 0;
    int       mWindowsHeight = 0;
    // Set true to use 4X MSAA (?.1.8).  The default is false.
    bool      m4xMsaaState = false;    // 4X MSAA enabled
    UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

    // Low level devices
    ComPtr<IDXGIFactory4> mdxgiFactory;
    ComPtr<IDXGISwapChain> mSwapChain;
    ComPtr<ID3D12Device> md3dDevice;

    // Fence for Sync between CPU and GPU
    ComPtr<ID3D12Fence> mFence;
    UINT64 mCurrentFence = 0;

    // Command Queue & List
    ComPtr<ID3D12CommandQueue> mCommandQueue;
    ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
    ComPtr<ID3D12GraphicsCommandList> mCommandList;

    // Swapchain Buffer
    static const int SwapChainBufferCount = 2;
    int mCurrBackBuffer = 0;
    ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
    ComPtr<ID3D12Resource> mDepthStencilBuffer;

    // DescriptroHeap
    ComPtr<ID3D12DescriptorHeap> mRtvHeap;
    ComPtr<ID3D12DescriptorHeap> mDsvHeap;

    UINT mRtvDescriptorSize = 0;
    UINT mDsvDescriptorSize = 0;
    UINT mCbvSrvUavDescriptorSize = 0;

    // Viewport and Scissor Cut
    D3D12_VIEWPORT mScreenViewport;
    D3D12_RECT mScissorRect;

    // Format Declaration
    D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
    DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
};
