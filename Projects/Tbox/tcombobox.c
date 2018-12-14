#include "tbox.h"

TCOMBOBOX   CreateCombobox(HWND owner, int x, int y, int w, int h, TFONT font)
{
  TCOMBOBOX ret;

  ret.id = GetNextTid();
  ret.owner = owner;

  ret.self = CreateWindow("COMBOBOX",
                          NULL,
                          WS_CHILD | WS_VISIBLE | CBS_SORT | CBS_DROPDOWNLIST,
                          x, y, w, h, ret.owner, (HMENU)ret.id,
                          GetModuleHandle(NULL), NULL);
  if(!ret.self)
    MessageBox(NULL, "Err", NULL, 0);

  SendMessage(ret.self, WM_SETFONT, (WPARAM)font.self, TRUE);

  return ret;
}

void AddToCombobox(TCOMBOBOX cb, char *str)
{
    SendMessage(cb.self, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)str);
}
