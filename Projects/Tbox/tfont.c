#include "tcore.h"

static struct
{
  int      stackSize;
  TBOXFONT base[TBOX_FONTS_ENTITY_SIZE];
}tFonts;

TBOOL  tSetFont(TBUNIT element, char *font)
{
  TBOXFONT *fontPtr = NULL;
  int      i = 0;
  TBOOL    ret = tFALSE;

  if(tFonts.stackSize > 0)     //! scanning all font stack for already defined
  {
    for(i = 0; i < tFonts.stackSize; i++)
    {
      if(tFonts.base[i].owner == element.id)
      {
        fontPtr = &tFonts.base[i];
        break;
      }
    }
  }

  if(fontPtr)                  //! if after scanning font stack some font for this element was find
  {                            //! than destroy this object before new font sets
    DeleteObject(fontPtr->id);
    for(i = 0; i < _FONTNAMEMAXSIZE_; i++)    //! Clear font name field
    {
      fontPtr->name[i] = 0;
    }
  }
  else                         //! if this element has no font yet than create it in stack
  {
    if(tFonts.stackSize < TBOX_FONTS_ENTITY_SIZE)
    {
      fontPtr = &tFonts.base[tFonts.stackSize++];
      fontPtr->h = 15;
    }
    else                       //! if font stack is full than stack works like a FIFO: First created font destroyed, all other fonts shifted & in last stack sell should be created a new font
    {
      DeleteObject(tFonts.base[0].id);
      for(i = 0; i < _FONTNAMEMAXSIZE_; i++)    //! Clear font name field
      {
        tFonts.base[0].name[i] = 0;
      }
      for(i = 0; i < (TBOX_FONTS_ENTITY_SIZE - 1); i++)
      {
        tFonts.base[i] = tFonts.base[i + 1];
      }
      fontPtr = &tFonts.base[TBOX_FONTS_ENTITY_SIZE - 1];
      fontPtr->h = 15;
    }
  }

  if((element.type == tBUTTON)
  || (element.type == tLABEL))                 //! In this line should be checking for correct type of element
  {
    ret = tTRUE;
    fontPtr->owner = element.id;
    fontPtr->brush = NULL;
    for(i = 0; i < _FONTNAMEMAXSIZE_; i++)    //! Checking for length of requested font & copy its name to structure
    {
      if(font[i] != 0)                        //! Maybe exloyed
      {
        fontPtr->name[i] = font[i];
      }
      else
      {
        break;
      }
    }

    fontPtr->id = CreateFont(fontPtr->h, 0, 0, 0, FW_MEDIUM,
		                     FALSE, FALSE, FALSE, ANSI_CHARSET,
		                     OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		                     DEFAULT_QUALITY,
		                     DEFAULT_PITCH | FF_DONTCARE, fontPtr->name);

    SendMessage(element.self, WM_SETFONT, (WPARAM)fontPtr->id, TRUE);
  }
  return ret;
}

/*TBOOL  tSetFontSize(TBUNIT element, int size)
{

}

TBOOL  tSetFontStyle(TBUNIT element, tBoxFontStyle id)
{

}*/

TBOOL  tSetFontColor(TBUNIT element, COLORREF color)
{
  TBOOL    ret      = tFALSE;
  int      i        = 0;
  TBOXFONT *fontPtr = NULL;

  if(element.type == tLABEL)
  {
    for(i = 0; i < tFonts.stackSize; i++)
    {
      if(tFonts.base[i].owner == element.id)
      {
        fontPtr = &tFonts.base[i];
        break;
      }
    }
    if(fontPtr)
    {
      ret = tTRUE;
      fontPtr->fontColor = color;
      SendMessage(element.owner, WM_CTLCOLORSTATIC, (WPARAM)GetDC(element.self), (LPARAM)element.self);
    }
  }
  return ret;
}

TBOOL tSetBgColor(TBUNIT element, COLORREF color)
{
  TBOOL    ret      = tFALSE;
  int      i        = 0;
  TBOXFONT *fontPtr = NULL;

  if(element.type == tLABEL)
  {
    for(i = 0; i < tFonts.stackSize; i++)
    {
      if(tFonts.base[i].owner == element.id)
      {
        fontPtr = &tFonts.base[i];
        break;
      }
    }
    if(fontPtr)
    {
      ret = tFALSE;
      if(fontPtr->brush)
      {
        DeleteObject(fontPtr->brush);
      }
      fontPtr->bgColor = color;
      fontPtr->brush   = CreateSolidBrush(color);
      SendMessage(element.owner, WM_CTLCOLORSTATIC, (WPARAM)GetDC(element.self), (LPARAM)element.self);
    }
  }
  return ret;
}

int tRedrawLabel(HDC dev, HWND ctrl)
{
  int      ret      = 0;
  int      i        = 0;

  for(i = 0; i < tFonts.stackSize; i++)
  {
    if(tFonts.base[i].owner == (int)GetMenu(ctrl))
    {
      SetTextColor(dev, tFonts.base[i].fontColor);
      SetBkColor(dev, tFonts.base[i].bgColor);
      ret = (int)tFonts.base[i].brush;
      break;
    }
  }

  return ret;
}


TBOOL  tSetText(TBUNIT element, char *txt)
{
  TBOOL ret = tFALSE;
  if(   (element.type == tBUTTON)
     || (element.type == tLABEL))
  {
    ret = tTRUE;
    SetDlgItemText(element.owner, element.id, txt);
  }
  return ret;
}

void tPrintf(TBUNIT element, const char *txt, ...)
{
  char    *buf;
  int     txtLen = 0;
  va_list args;

  if(   (element.type == tBUTTON)
     || (element.type == tLABEL))
  {
      txtLen = strlen(txt);
      buf    = (char*)malloc(txtLen*2);
      va_start(args, txt);
      vsprintf(buf, txt, args);
      va_end(args);
      SetDlgItemText(element.owner, element.id, buf);
   // ret = tTRUE;
   // SetDlgItemText(element.owner, element.id, txt);
  }
}

