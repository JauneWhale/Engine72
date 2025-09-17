#pragma once

#include "CommonUtil.h"
#include "GameTimer.h"
#include "WindowsInput.h"

class WinApp
{
#pragma region 功能接口
public:
    virtual bool Initialize();
    virtual bool IsRendererApp() { return false; }
protected:
    virtual void MsgProcOnKeyUp(int key) {};
    virtual void Update(const GameTimer& gt) {};
    virtual void OnResize() {};
#pragma endregion
    

public:
    static WinApp* GetApp();

    WinApp(HINSTANCE hInstance);
    WinApp(const WinApp& rhs) = delete;
    WinApp& operator=(const WinApp& rhs) = delete;
    virtual ~WinApp() = default;

    void SetWindowsInputModule(WindowsInput* winInput) { mWinInput = winInput; }
    HINSTANCE AppInst()const;
    HWND      MainWnd()const;
    LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    int Run();

protected:
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

    // Used to keep track of the �delta-time?and game time (?.4).
    GameTimer mTimer;

    // The input scheduler class for current app windows
    WindowsInput* mWinInput = nullptr;

    // Derived class should set these in derived constructor to customize starting values.
    std::wstring mMainWndCaption = L"Engine72 App";
    int mClientWidth = 800;
    int mClientHeight = 600;
};