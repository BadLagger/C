#ifndef TBOX_H_INCLUDED
#define TBOX_H_INCLUDED

#include "tcore.h"

#ifdef __cplusplus
#define C_CPP "C"
#else
#define C_CPP
#endif

#define _MAX_MOUSE_HANDLERS_  2
#define _MAX_BUTTON_HANDLERS_ 25
#define _MAX_RESIZE_HANDLERS_ 2
#define _MAX_REMOVE_HANDLERS_ 2
/*typedef enum
{
  winDefault = 0,

}winStyle;*/

typedef struct {
  UINT   mask;
  DWORD  dwState;
  DWORD  dwStateMask;
  LPTSTR pszText;
  int    cchTextMax;
  int    iImage;
  LPARAM lParam;
} TCITEM;

/*typedef struct
{
  union
  {
    int  id;
    int  value;
  };
  HWND owner;
  HWND self;
  union
  {
    int  prm;
    int  state;
  };
}TBOXUNIT;*/

typedef TBUNIT   TBOXUNIT;
typedef TBOXUNIT TSTATIC;
typedef TBOXUNIT TWINDOW;
typedef TBOXUNIT TBUTTON;
typedef TBOXUNIT TCOMBOBOX;
typedef TBOXUNIT TCHECKBOX;
typedef TBOXUNIT TRADIOBTN;
typedef struct   TTAB
{
  int    id;
  HWND   owner;
  HWND   self;
  TCITEM item;
}TTAB;

typedef struct
{
  HWND self;
  int  h;
}TFONT;

typedef struct
{
  int   id;
  HMENU self;
}TMENU;

typedef struct
{
  HDC      owner;
  COLORREF color;
  RECT     coordinate;
  RECT     ownercoordinates;
}RECTANGLEFIG;

typedef struct
{
  int           value;
  COLORREF      bkColor;
  COLORREF      bkFaceColor;
  COLORREF      faceColor;
  RECTANGLEFIG  segment[8];
}TNUMSEGMENT;
// General processes
extern C_CPP int         GetNextTid(void);;
extern C_CPP WNDPROC     GetTboxMainHandle(void);
extern C_CPP WPARAM      TboxRun(void);
extern C_CPP void        EnableTunit(TBOXUNIT);
extern C_CPP void        DisableTunit(TBOXUNIT);
// windows
extern C_CPP TWINDOW     CreateMainWindow(int x, int y, int w, int h);
extern C_CPP void        SetNameWindow(TWINDOW w, char *txt);
extern C_CPP void        SetPositionWindow(TWINDOW w, int x, int y);
extern C_CPP void        SetSizeWindow(TWINDOW win, int w, int h);
extern C_CPP void        SetStyleWindow(TWINDOW w, int style);
// statics
//extern C_CPP TSTATIC     CreateStatic(TWINDOW owner, int x, int y, int w, int h, TFONT font);
extern C_CPP void        ChangeTextStatic(TSTATIC st, char *txt);
extern C_CPP void        SetIntStatic(TSTATIC st, int n);
extern C_CPP void        SetStaticBkColor(COLORREF clr);
extern C_CPP int         GetStaticBkColor(HDC dev);
// buttons
//extern C_CPP TBUTTON     CreateButton(TWINDOW owner, int x, int y, int w, int h, TFONT font);
//extern C_CPP void        ChangeTextButton(TBUTTON bt, char *txt);
// fonts
extern C_CPP TFONT       SetFont(int h, char *font);
// combobox
extern C_CPP TCOMBOBOX   CreateCombobox(HWND owner, int x, int y, int w, int h, TFONT font);
extern C_CPP void        AddToCombobox(TCOMBOBOX cb, char *str);
// tabcontrol
extern C_CPP TTAB        CreateTab(HWND owner, int x, int y, int w, int h, TFONT font);
extern C_CPP void        AddTab(TTAB tab, char *str);
// checkbox
extern C_CPP TCHECKBOX   CreateCheckbox(HWND owner, int x, int y, int w, int h);
// radio button
extern C_CPP TRADIOBTN   CreateRadiobtn(HWND owner, int x, int y, int w, int h);
// menu
extern C_CPP TMENU       CreateMenuInBar(char *name);
extern C_CPP void        AddMenuTo(TMENU mid);
// events

// handlers
extern C_CPP void        addMouseMoveHandler(TBOXUNIT item, void (*hndl)(TBOXUNIT, int, int));
extern C_CPP void        addButtonHandler(TBUTTON btn, TBOXUNIT item,void (*hndl)(TBUTTON, TBOXUNIT*));
extern C_CPP void        addResizeHandler(TBOXUNIT item1, TBOXUNIT item2, void (*hndl)(TBOXUNIT, TBOXUNIT));
extern C_CPP void        addRemoveHandler(TBOXUNIT item1, TBOXUNIT item2, void (*hndl)(TBOXUNIT, TBOXUNIT));
// rectangles
extern C_CPP RECTANGLEFIG CreateRectangle(TWINDOW);
extern C_CPP void         DrawRectangle(RECTANGLEFIG rect);
extern C_CPP void         FillColorRectangle(RECTANGLEFIG *rect, int r, int g, int b);
extern C_CPP void         ChangePosRectangle(RECTANGLEFIG *rect, int x, int y);
extern C_CPP void         ChangeSizeRectangle(RECTANGLEFIG *rect, int w, int h);
extern C_CPP TNUMSEGMENT  CreateNumSegment(TWINDOW owner, int faceW, int faceH, int x, int y);
extern C_CPP void         SetPositionNumSegment(TNUMSEGMENT, int x, int y);
extern C_CPP void         SetSizeNumSegment(TNUMSEGMENT, int w, int h);
extern C_CPP void         SetBkColorNumSegment(TNUMSEGMENT*, COLORREF);
extern C_CPP void         SetColorNumSegment(TNUMSEGMENT*, COLORREF);
extern C_CPP void         DrawNumSegment(TNUMSEGMENT);
extern C_CPP void         HideNumSegment(TNUMSEGMENT);
extern C_CPP void         ShowNumSegment(TNUMSEGMENT);
extern C_CPP void         SetValueNumSegment(TNUMSEGMENT*, int);
// threads
extern C_CPP void tCreateThread(void (*routin)(void));
#endif // TBOX_H_INCLUDED
