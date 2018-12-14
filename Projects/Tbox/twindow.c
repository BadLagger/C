#include "tbox.h"

TWINDOW     CreateMainWindow(int x, int y, int w, int h)
{
  TWINDOW ret;
  WNDCLASSEX wincl;

  ret.owner = (HWND)GetModuleHandle(NULL);

  wincl.hInstance     = (HINSTANCE)ret.owner;
  wincl.lpszClassName = "TboxWinClass";
  wincl.lpfnWndProc   = GetTboxMainHandle();
  wincl.style         = CS_DBLCLKS;
  wincl.cbSize        = sizeof (WNDCLASSEX);

  wincl.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm       = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor       = LoadCursor (NULL, IDC_ARROW);
  wincl.lpszMenuName  = NULL;
  wincl.cbClsExtra    = 0;
  wincl.cbWndExtra    = 0;

  wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

  if (RegisterClassEx (&wincl))
  {
    ret.id   = GetNextTid();

    ret.self = CreateWindowEx (
               0,
               wincl.lpszClassName,
               NULL,
               WS_OVERLAPPED | WS_SYSMENU,
               x,
               y,
               w,
               h,
               HWND_DESKTOP,
               NULL,
               (HINSTANCE)ret.owner,
               NULL
               );

  }
  return ret;
}

void    SetNameWindow(TWINDOW w, char *txt)
{
  SendMessage(w.self, WM_SETTEXT, 0,(LPARAM)txt);
}

void SetPositionWindow(TWINDOW w, int x, int y)
{
  SetWindowPos(w.self, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

void SetSizeWindow(TWINDOW win, int w, int h)
{
  SetWindowPos(win.self, HWND_TOP, 0, 0, w, h, SWP_NOMOVE);
}

void        SetStyleWindow(TWINDOW w, int style)
{

}
