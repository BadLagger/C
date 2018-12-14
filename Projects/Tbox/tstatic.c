#include "tbox.h"

/*static struct
{
  COLORREF bkColor;
  HBRUSH   bkBrush;
}ColorSet;*/

/*TSTATIC CreateStatic(TWINDOW owner, int x, int y, int w, int h, TFONT font)
{
  TSTATIC ret;

  ret.id = GetNextTid();
  ret.owner = owner.self;
  ret.state = 0;

  ret.self = CreateWindow("STATIC",
               NULL,
               WS_CHILD | WS_VISIBLE,
               x, y, w, h,
               ret.owner,(HMENU)ret.id,
               GetModuleHandle(NULL), NULL);

  SendMessage(ret.self, WM_SETFONT, (WPARAM)font.self, TRUE);

  return ret;
}*/

void ChangeTextStatic(TSTATIC st, char *txt)
{
  if(st.owner)
  {
    SetDlgItemText(st.owner, st.id, txt);
  }
}

void    SetIntStatic(TSTATIC st, int n)
{
  char tmpBuf[16];
  if(st.owner)
  {
    sprintf(tmpBuf, "%d", n);
    SetDlgItemText(st.owner, st.id, tmpBuf);
  }
}

/*void SetStaticBkColor(COLORREF clr)
{
  ColorSet.bkColor = clr;
  ColorSet.bkBrush = CreateSolidBrush(clr);
}

int GetStaticBkColor(HDC dev)
{
  SetBkColor(dev, ColorSet.bkColor);
  return (int)ColorSet.bkBrush;
}*/
