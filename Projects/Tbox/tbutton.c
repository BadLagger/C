#include "tbox.h"

/*TBUTTON CreateButton(TWINDOW owner, int x, int y, int w, int h, TFONT font)
{
  TBUTTON ret;

  ret.id    = GetNextTid();
  ret.owner = owner.self;
  ret.state = 0;

  ret.self = CreateWindow("BUTTON",
               NULL,
               WS_CHILD | WS_VISIBLE,
               x, y, w, h,
               ret.owner,(HMENU)ret.id,
               GetModuleHandle(NULL), NULL);

  SendMessage(ret.self, WM_SETFONT, (WPARAM)font.self, TRUE);
  return ret;
}*/

/*void    ChangeTextButton(TBUTTON bt, char *txt)
{
  if(bt.owner)
  {
    SetDlgItemText(bt.owner, bt.id, txt);
  }
}*/
