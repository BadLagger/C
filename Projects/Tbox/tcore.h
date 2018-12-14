#ifndef TCORE_H_INCLUDED
#define TCORE_H_INCLUDED

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
#define C_CPP "C"
#else
#define C_CPP
#endif

/**< Memory managment */
#define TBOX_FONTS_ENTITY_SIZE   256 //! in entities
#define TBOX_THREADS_ENTITY_SIZE 10  //! in entities

/**< FONTS */
#define     _FONTID_          0xFAB00
#define     _FONTNAMEMAXSIZE_ 128

typedef struct
{
  int      owner;
  HFONT    id;
  int      h;
  int      w;
  COLORREF bgColor;
  COLORREF fontColor;
  HBRUSH   brush;
  char     name[_FONTNAMEMAXSIZE_];
}TBOXFONT;

typedef enum
{
  tFALSE = 0,
  tTRUE  = 0xFF
}TBOOL;

typedef enum
{
  tBUTTON = 0,
  tLABEL,
  tMAINWINDOW,
  tLASTELEMENT
}tBoxElement;

typedef enum
{
  tNOEVENT = 0,
  tMANUALRESET,
  tAUTORESET
}tBoxEventType;

typedef struct
{
  HANDLE        hndl;
  HANDLE        event;
  tBoxEventType etype;
  void (*thread)(void);
}TBOXTHREAD;

typedef struct
{
  union
  {
    HWND    owner;
  };
  union
  {
    HWND    self;
  };
  tBoxElement  type;
  union
  {
    int           fontId;
  };
  union
  {
    int  id;
    int  value;
  };
  union
  {
    int  prm;
    int  state;
  };
}TBUNIT;

typedef tBoxElement tBoxOwner;

extern C_CPP TBUNIT tCreate(TBUNIT, tBoxElement);
extern C_CPP TBOOL  tSetSize(TBUNIT, int, int);
extern C_CPP TBOOL  tSetPosition(TBUNIT, int, int);
// Fonts
extern C_CPP TBOOL  tSetFont(TBUNIT, char*);
/*extern C_CPP TBOOL  tSetFontSize(TBUNIT, int);
extern C_CPP TBOOL  tSetFontStyle(TBUNIT, tBoxFontStyle);*/
extern C_CPP TBOOL  tSetFontColor(TBUNIT, COLORREF);
extern C_CPP TBOOL  tSetBgColor(TBUNIT, COLORREF);
extern C_CPP int    tRedrawLabel(HDC dev, HWND ctrl);  //! FOR USE IN TBoxWinProcedure only
extern C_CPP void   tPrintf(TBUNIT element, const char *txt, ...);
extern C_CPP TBOOL  tSetText(TBUNIT, char*);
extern C_CPP TBOOL  tAddText(TBUNIT, char*);
extern C_CPP int    tGetText(TBUNIT, char*);
extern C_CPP TBOOL  tShow(TBUNIT);
extern C_CPP TBOOL  tHide(TBUNIT);
/*extern C_CPP TBOOL  tEnable(TBUNIT);
extern C_CPP TBOOL  tDisable(TBUNIT);*/

#endif // TCORE_H_INCLUDED
