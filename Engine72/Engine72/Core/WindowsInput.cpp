#include "WindowsInput.h"


void MouseDraggingInput::OnMouseDown(WPARAM btnState, int x, int y)
{
    mLastMousePos.x = x;
    mLastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void MouseDraggingInput::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void MouseDraggingInput::OnMouseMove(WPARAM btnState, int x, int y)
{
    mInputCommand->Process(btnState, x - mLastMousePos.x, y - mLastMousePos.y);

    mLastMousePos.x = x;
    mLastMousePos.y = y;
}