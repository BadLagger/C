#include "tbox.h"


typedef struct
{
  TBOXUNIT item;
  void     (*mHandler)(TBOXUNIT id, int x, int y);
}TMOUSEHANDLER;

typedef struct
{
  TBUTTON  btn;
  TBOXUNIT item;
  void    (*bHandler)(TBOXUNIT, TBOXUNIT*);
}TBUTTONHANDLER;

typedef struct
{
  TBOXUNIT item1;
  TBOXUNIT item2;
  void     (*rHandler)(TBOXUNIT, TBOXUNIT);
}TRESIZEHANDLER;

static struct
{
  int            mouseActionNum;
  int            buttonActionNum;
  int            resizeActionNum;
  int            removeActionNum;
  TMOUSEHANDLER  *mouseAction[_MAX_MOUSE_HANDLERS_];
  TBUTTONHANDLER *buttonAction[_MAX_BUTTON_HANDLERS_];
  TRESIZEHANDLER *resizeAction[_MAX_RESIZE_HANDLERS_];
  TRESIZEHANDLER *removeAction[_MAX_REMOVE_HANDLERS_];
}tHandler;

static void    MouseHandlersFree(void);
static void    ButtonHandlersFree(void);
static void    ResizeHandlersFree(void);
static void    RemoveHandlersFree(void);
static LRESULT CALLBACK TBoxWinProcedure(HWND, UINT, WPARAM, LPARAM);

static unsigned long tid = 0x8801;

int GetNextTid(void)
{
  return tid++;
}

WPARAM TboxRun(void)
{
  MSG ret;

  while(GetMessage (&ret, NULL, 0, 0))
  {
    TranslateMessage(&ret);
    DispatchMessage(&ret);
  }

  return ret.wParam;
}

WNDPROC GetTboxMainHandle(void)
{
  return TBoxWinProcedure;
}

LRESULT CALLBACK TBoxWinProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int count;
  int ret;

  switch (message)
  {
    case WM_DESTROY:        MouseHandlersFree();
                            ButtonHandlersFree();
                            ResizeHandlersFree();
                            RemoveHandlersFree();
                            PostQuitMessage(0);
      break;
    case WM_CTLCOLORSTATIC:
                            ret = tRedrawLabel((HDC)wParam, (HWND)lParam);
      break;
    case WM_SIZE:
                            if(tHandler.resizeActionNum > 0)
                            {
                              for(count = 0; count < tHandler.resizeActionNum; count++)
                              {
                                tHandler.resizeAction[count]->rHandler(tHandler.resizeAction[count]->item1, tHandler.resizeAction[count]->item2);
                              }
                            }
      break;
    case WM_MOVE :          if(tHandler.removeActionNum > 0)
                            {
                              for(count = 0; count < tHandler.removeActionNum; count++)
                              {
                                tHandler.removeAction[count]->rHandler(tHandler.removeAction[count]->item1, tHandler.removeAction[count]->item2);
                              }
                            }
      break;
    case WM_MOUSEMOVE:      if(tHandler.mouseActionNum > 0)
                            {
                              for(count = 0; count < tHandler.mouseActionNum; count++)
                              {
                                tHandler.mouseAction[count]->mHandler(tHandler.mouseAction[count]->item, LOWORD(lParam), HIWORD(lParam));
                              }
                            }
      break;
    case WM_COMMAND:        if(tHandler.buttonActionNum > 0)
                            {
                              for(count = 0; count < tHandler.buttonActionNum; count++)
                              {
                                if(LOWORD(wParam) == tHandler.buttonAction[count]->btn.id)
                                {
                                  tHandler.buttonAction[count]->bHandler(tHandler.buttonAction[count]->btn, &tHandler.buttonAction[count]->item);
                                }
                              }
                            }
      break;
    default:                ret = DefWindowProc (hwnd, message, wParam, lParam);
  }

  return ret;
}

void addMouseMoveHandler(TBOXUNIT item, void (*hndl)(TBOXUNIT, int, int))
{
  if(tHandler.mouseActionNum < _MAX_MOUSE_HANDLERS_)
  {
    tHandler.mouseAction[tHandler.mouseActionNum]             = (TMOUSEHANDLER*)malloc(sizeof(TMOUSEHANDLER));
    tHandler.mouseAction[tHandler.mouseActionNum]->item       = item;
    tHandler.mouseAction[tHandler.mouseActionNum++]->mHandler = hndl;
  }
}

void addButtonHandler(TBUTTON btn, TBOXUNIT item,void (*hndl)(TBUTTON, TBOXUNIT*))
{
  if(tHandler.buttonActionNum < _MAX_BUTTON_HANDLERS_)
  {
    tHandler.buttonAction[tHandler.buttonActionNum]             = (TBUTTONHANDLER*)malloc(sizeof(TBUTTONHANDLER));
    tHandler.buttonAction[tHandler.buttonActionNum]->btn        = btn;
    tHandler.buttonAction[tHandler.buttonActionNum]->item       = item;
    tHandler.buttonAction[tHandler.buttonActionNum++]->bHandler = hndl;
  }
}

void addResizeHandler(TBOXUNIT item1, TBOXUNIT item2, void (*hndl)(TBOXUNIT, TBOXUNIT))
{
if(tHandler.resizeActionNum < _MAX_RESIZE_HANDLERS_)
  {
    tHandler.resizeAction[tHandler.resizeActionNum]             = (TRESIZEHANDLER*)malloc(sizeof(TRESIZEHANDLER));
    tHandler.resizeAction[tHandler.resizeActionNum]->item1      = item1;
    tHandler.resizeAction[tHandler.resizeActionNum]->item2      = item2;
    tHandler.resizeAction[tHandler.resizeActionNum++]->rHandler = hndl;
  }
}

void addRemoveHandler(TBOXUNIT item1, TBOXUNIT item2, void (*hndl)(TBOXUNIT, TBOXUNIT))
{
if(tHandler.removeActionNum < _MAX_RESIZE_HANDLERS_)
  {
    tHandler.removeAction[tHandler.removeActionNum]             = (TRESIZEHANDLER*)malloc(sizeof(TRESIZEHANDLER));
    tHandler.removeAction[tHandler.removeActionNum]->item1      = item1;
    tHandler.removeAction[tHandler.removeActionNum]->item2      = item2;
    tHandler.removeAction[tHandler.removeActionNum++]->rHandler = hndl;
  }
}


void    MouseHandlersFree(void)
{
  int count = 0;

  for(count = 0; count < tHandler.mouseActionNum; count++)
  {
    free(tHandler.mouseAction[count]);
  }
}

void    ButtonHandlersFree(void)
{
  int count = 0;

  for(count = 0; count < tHandler.buttonActionNum; count++)
  {
    free(tHandler.buttonAction[count]);
  }
}

void    ResizeHandlersFree(void)
{
  int count = 0;

  for(count = 0; count < tHandler.resizeActionNum; count++)
  {
    free(tHandler.resizeAction[count]);
  }
}

void    RemoveHandlersFree(void)
{
  int count = 0;

  for(count = 0; count < tHandler.removeActionNum; count++)
  {
    free(tHandler.removeAction[count]);
  }
}

TFONT   SetFont(int h, char *font)
{
  TFONT ret;

  ret.self = (HWND)CreateFont(
		h, 0, 0, 0, FW_MEDIUM,
		FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, font);

  return ret;
}

TCHECKBOX   CreateCheckbox(HWND owner, int x, int y, int w, int h)
{
  TCHECKBOX ret;

  ret.id = GetNextTid();
  ret.owner = owner;

  ret.self = CreateWindow("BUTTON",
                          NULL,
                          WS_VISIBLE| WS_CHILD | BS_CHECKBOX,
                          x, y, w, h, ret.owner, (HMENU)ret.id,
                          GetModuleHandle(NULL), NULL);
  if(!ret.self)
    MessageBox(NULL, "Err", NULL, 0);


  return ret;
}

TRADIOBTN   CreateRadiobtn(HWND owner, int x, int y, int w, int h)
{
  TRADIOBTN ret;

  ret.id = GetNextTid();
  ret.owner = owner;

  ret.self = CreateWindow("BUTTON",
                          NULL,
                          WS_VISIBLE| WS_CHILD | BS_RADIOBUTTON,
                          x, y, w, h, ret.owner, (HMENU)ret.id,
                          GetModuleHandle(NULL), NULL);
  if(!ret.self)
    MessageBox(NULL, "Err", NULL, 0);

  return ret;
}

static HMENU mbid = 0; // Menu Bar Id
TMENU       CreateMenuInBar(char *name)
{
  int   i = 0;
  char  tmpName[32];
  TMENU ret;

  if(mbid == 0)
  {
    mbid = CreateMenu();
    if(!mbid) MessageBox(NULL, "Err", NULL, 0);
  }
  memset(tmpName, 0, sizeof(tmpName));
  tmpName[0] = '&';
  for(i = 0; name[i] != 0; i++)
  {
    tmpName[i+1] = name[i];
  }

  ret.id = GetNextTid();
  ret.self = CreateMenu();
  if(!ret.self) MessageBox(NULL, "Err", NULL, 0);
  if(!AppendMenuW(mbid, MF_STRING, ret.id, (LPCWSTR)tmpName)) MessageBox(NULL, "Err", NULL, 0);

  return ret;
}

void        EnableTunit(TBOXUNIT item)
{
    EnableWindow(item.self, TRUE);
}

void        DisableTunit(TBOXUNIT item)
{
    EnableWindow(item.self, FALSE);
}

