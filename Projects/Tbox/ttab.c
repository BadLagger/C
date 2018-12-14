#include "tbox.h"

TTAB CreateTab(HWND owner, int x, int y, int w, int h, TFONT font)
{
  TTAB ret;

  ret.id = GetNextTid();
  ret.owner = owner;

  ret.self = CreateWindow("SYSTABCONTROL32",
                          NULL,
                          WS_VISIBLE| WS_CHILD,
                          x, y, w, h, ret.owner, (HMENU)ret.id,
                          GetModuleHandle(NULL), NULL);
  /*if(!ret.self)
    MessageBox(NULL, "Err", NULL, 0);*/

  SendMessage(ret.self, WM_SETFONT, (WPARAM)font.self, TRUE);

  return ret;
}

void AddTab(TTAB tab, char *str)
{
  tab.item.mask = 3;
  tab.item.pszText = str;
  SendMessage(tab.self, (UINT)(0x1307), (WPARAM)1, (int)&tab.item);
}
