#pragma once

#include "CommonUtil.h"
#include "GameTimer.h"
#include "WindowsInput.h"

class WinApp
{
public:

    WinApp(HINSTANCE hInstance);
    WinApp(const WinApp& rhs) = delete;
    WinApp& operator=(const WinApp& rhs) = delete;
    virtual ~WinApp() {};
    virtual bool Initialize();

public:
    static WinApp* GetApp();

    void SetWindowsInputModule(WindowsInput* winInput) { mWinInput = winInput; }
    HINSTANCE AppInst()const;
    HWND      MainWnd()const;
    LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void MsgProcOnKeyUp(int key) {};

    int Run();

protected:
    virtual void Paint(const GameTimer& gt) {};
    virtual void OnResize() {};

    bool InitMainWindow();
    void CalculateFrameStats();

protected:
    static WinApp* mApp;

    HINSTANCE mhAppInst = nullptr; // application instance handle
    HWND      mhMainWnd = nullptr; // main window handle
    bool      mAppPaused = false;  // is the application paused?
    bool      mMinimized = false;  // is the application minimized?
    bool      mMaximized = false;  // is the application maximized?
    bool      mResizing = false;   // are the resize bars being dragged?
    // TODO(zrz): FullScreen Enabled State is not implemented
    bool      mFullscreenState = false;// fullscreen enabled
    bool      mIsRendererApp = false;// Tool App or Renderer App with backEnd? (DX11, DX12, Vulkan etc.)

    // Used to keep track of the �delta-time?and game time (?.4).
    GameTimer mTimer;

    // The input scheduler class for current app windows
    WindowsInput* mWinInput = nullptr;

    // Derived class should set these in derived constructor to customize starting values.
    std::wstring mMainWndCaption = L"Engine72 App";
    int mClientWidth = 800;
    int mClientHeight = 600;
};