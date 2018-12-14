#include "tcore.h"

static int  tBoxIdGenerator = 0x8900;
static char *strElementId[tLASTELEMENT]  =
{
  "BUTTON",
  "STATIC",
  "MAINWINDOW"
};

TBUNIT tCreate(TBUNIT owner, tBoxElement id)
{
  WNDCLASSEX mainWinClass;
  TBUNIT     ret;

  if(   (id == tBUTTON)
     || (id == tLABEL))
  {
    ret.id    = tBoxIdGenerator++;
    ret.owner = owner.self;
    ret.state = 0;
    ret.type = id;

    ret.self = CreateWindow(strElementId[id],
                            NULL,
                            WS_CHILD,
                            0, 0, 50, 100,
                            ret.owner,
                            (HMENU)ret.id,
                            GetModuleHandle(NULL),
                            NULL);
  }

  if(id == tMAINWINDOW)
  {
    ret.owner = (HWND)GetModuleHandle(NULL);

    mainWinClass.hInstance     = (HINSTANCE)ret.owner;
    mainWinClass.lpszClassName = strElementId[id];
    mainWinClass.lpfnWndProc   = GetTboxMainHandle();
    mainWinClass.style         = CS_DBLCLKS;
    mainWinClass.cbSize        = sizeof (WNDCLASSEX);

    mainWinClass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    mainWinClass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION);
    mainWinClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
    mainWinClass.lpszMenuName  = NULL;
    mainWinClass.cbClsExtra    = 0;
    mainWinClass.cbWndExtra    = 0;

    mainWinClass.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (RegisterClassEx (&mainWinClass))
    {
      ret.id   = GetNextTid();

      ret.self = CreateWindowEx (
                 0,
                 mainWinClass.lpszClassName,
                 NULL,
                 WS_OVERLAPPED | WS_SYSMENU,
                 0,
                 0,
                 0,
                 0,
                 HWND_DESKTOP,
                 NULL,
                 (HINSTANCE)ret.owner,
                 NULL
                 );

    }
  }

  return ret;
}

TBOOL  tSetSize(TBUNIT element, int width, int height)
{
  TBOOL ret = tFALSE;
  RECT  elementRect;
  RECT  ownerRect;
  RECT  ownerLocalRect;

  if(   (element.type == tBUTTON)
     || (element.type == tLABEL))
  {
    if(GetWindowRect(element.self, &elementRect) && GetWindowRect(element.owner, &ownerRect) && GetClientRect(element.owner, &ownerLocalRect))
    {
      if(MoveWindow(element.self,
                    elementRect.left - ownerRect.right + ownerLocalRect.right,
                    elementRect.top - ownerRect.bottom + ownerLocalRect.bottom,
                    width, height, TRUE))
      {
        ret = tTRUE;
      }
    }
  }

  if(  (element.type == tMAINWINDOW))
  {

  }

  return ret;
}

TBOOL tSetPosition(TBUNIT element, int x, int y)
{
  TBOOL ret = tFALSE;
  RECT  elementRect;

  if(GetClientRect(element.self, &elementRect))
  {
    if(MoveWindow(element.self, x, y, elementRect.right, elementRect.bottom, TRUE))
    {
      ret = tTRUE;
    }
  }

  return ret;
}

TBOOL tShow(TBUNIT element)
{
  TBOOL ret = tFALSE;

  if(!ShowWindow(element.self, 1))
    ret = tTRUE;

  return ret;
}

TBOOL tHide(TBUNIT element)
{
  TBOOL ret = tFALSE;

  if(ShowWindow(element.self, 0))
    ret = tTRUE;

  return ret;
}
/*TBOOL  tEnable(TBUNIT)
{

}

TBOOL  tDisable(TBUNIT)
{

}*/
