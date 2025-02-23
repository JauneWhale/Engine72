#pragma once

#include "CommonUtil.h"
#include "../Patterns/InputCommands.h"

class WindowsInput
{
protected:
    HWND mhMainWnd;
public:
    WindowsInput(HWND targetWnd): mhMainWnd(targetWnd) {}
    // Convenience overrides for handling mouse input.
    virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
    virtual void OnMouseUp(WPARAM btnState, int x, int y) {}
    virtual void OnMouseMove(WPARAM btnState, int x, int y) {}
};

class MouseDraggingInput : public WindowsInput
{
    InputCommand<WPARAM, int, int>* mInputCommand;
public:
    MouseDraggingInput(HWND targetWnd, InputCommand<WPARAM, int, int>* inputCommand)
        : WindowsInput(targetWnd), mInputCommand(inputCommand)  {}
    // Convenience overrides for handling mouse input.
    virtual void OnMouseDown(WPARAM btnState, int x, int y) override;
    virtual void OnMouseUp(WPARAM btnState, int x, int y) override;
    virtual void OnMouseMove(WPARAM btnState, int x, int y) override;
private:
    POINT mLastMousePos;

};