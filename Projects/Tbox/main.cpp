#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tbox.h"
/*  Declare Windows procedure  */
//LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
/*  Make the class name into a global variable  */
//TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

//int MainWindowWidth  = 500;
//int MainWindowHeight = 500;
// TREADS
/*DWORD WINAPI sendTimeEvent(PVOID pParam);
HANDLE       timeThread;
HWND         hwnd1;                This is the handle for our window */

/*TSTATIC staticWinH;
TSTATIC staticWinW;
TSTATIC staticMouseX;
TSTATIC staticMouseY;
TSTATIC WinH;
TSTATIC WinW;
TSTATIC MouseX;
TSTATIC MouseY;
TSTATIC Enable;
TSTATIC Disable;
TBUTTON ClearButton;
TCOMBOBOX ComboxNew;
RECTANGLEFIG lineBorder;
TTAB         tabEdit;
TCHECKBOX CheckB;
TRADIOBTN RadBtn1;
TRADIOBTN RadBtn2;

TFONT mainFont;
TMENU FileMenu;*/

/*static void MouseMoveXHandle(TBOXUNIT item, int x, int y);
static void MouseMoveYHandle(TBOXUNIT item, int x, int y);
static void IncreaseMainWindowSize(TBOXUNIT b, TBOXUNIT *wmItem);
static void DecreaseMainWindowSize(TBOXUNIT b, TBOXUNIT *wmItem);
static void ShowMainWindowH(TBOXUNIT staticItem, TBOXUNIT windItem);
static void ShowMainWindowW(TBOXUNIT staticItem, TBOXUNIT windItem);
static void ShowMainWindowX(TBOXUNIT staticItem, TBOXUNIT windItem);
static void ShowMainWindowY(TBOXUNIT staticItem, TBOXUNIT windItem);
static void ShowHideSegment(TBOXUNIT b,  TBOXUNIT *windItem);
static void IncrementSegment(TBOXUNIT b, TBOXUNIT *windItem);
static void DecrementSegment(TBOXUNIT b, TBOXUNIT *windItem);
static void ActivateDisactivateButton(TBOXUNIT b, TBOXUNIT *windItem);*/

/*TNUMSEGMENT fistHourNum;
TNUMSEGMENT secondHourNum;
TBOXUNIT    counter;*/

void HelloThread(void);
void BuyThread(void);

   TBUNIT  dbgLabel1,
           dbgLabel2;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
   int      tMainW;
   int      tMainH;
//   COLORREF tMainColor;
   TWINDOW  tMainWin;
//  TFONT    mainFont;
   RECT     desktopSize;
//   TSTATIC desktopHeightField;
//   TSTATIC desktopWeightField;
//   TSTATIC desktopHeight;
//   TSTATIC desktopWeight;
//   TSTATIC mouseXPosField,
//           mouseYPosField;
//  TSTATIC mouseXPos,
//           mouseYPos;
 //  TSTATIC mWinH,
 //          mWinW;
 /*  TSTATIC mWinHField,
           mWinWField;
   TSTATIC mWinCoordinatesXField,
           mWinCoordinatesYField;
   TSTATIC mWinCoordinatesX,
           mWinCoordinatesY;
   TBUTTON resizePlusBtn,
           resizeMinusBtn;
   TBUTTON segmentButton,
           segmentAddButton,
           segmentSubButton;*/

   TBUNIT  dbgUnit1,
           dbgUnit2;



   GetClientRect(GetDesktopWindow(), &desktopSize);  //! Init for sizer of main window
   tMainW = desktopSize.right/2;
   tMainH = desktopSize.bottom/2;

   tMainWin  = CreateMainWindow(0, 0, 0, 0);
               SetNameWindow(tMainWin, (char*)"tBox->main window");
               SetPositionWindow(tMainWin, (desktopSize.right - tMainW)/2, (desktopSize.bottom - tMainH)/2);
               SetSizeWindow(tMainWin, tMainW, tMainH);

/*    dbgUnit1 = tCreate(tMainWin, tBUTTON);
               tSetSize(dbgUnit1, 70, 20);
               tSetPosition(dbgUnit1, 10, 10);
               tShow(dbgUnit1);
               tSetFont(dbgUnit1, (char*)"Verdana");
               tSetText(dbgUnit1, (char*)"Button 1");

    dbgUnit2 = tCreate(tMainWin, tBUTTON);
               tSetSize(dbgUnit2, 70, 20);
               tSetPosition(dbgUnit2, 90, 10);
               tShow(dbgUnit2);
               tSetFont(dbgUnit2, (char*)"Times New Roman");
               tSetText(dbgUnit2, (char*)"Button 2");*/

    dbgLabel1 = tCreate(tMainWin, tLABEL);
                tSetSize(dbgLabel1, 150, 200);
                tSetPosition(dbgLabel1, 200, 10);
                tShow(dbgLabel1);
                tSetFont(dbgLabel1, (char*)"Times New Roman");
                tSetBgColor(dbgLabel1, RGB(0, 200, 0));
                tSetFontColor(dbgLabel1, RGB(0, 0, 200));
                //tSetText(dbgLabel1, (char*)"Debug screen 1:");
                //tPrintf(dbgLabel1, "Printf %d", 12);

    dbgLabel2 = tCreate(tMainWin, tLABEL);
                tSetSize(dbgLabel2, 150, 200);
                tSetPosition(dbgLabel2, 400, 10);
                tShow(dbgLabel2);
                tSetFont(dbgLabel2, (char*)"Arial");
                tSetBgColor(dbgLabel2, RGB(0, 0, 100));
                tSetFontColor(dbgLabel2, RGB(250, 0, 0));
               /* tSetText(dbgLabel2, (char*)"Debug screen 2:");*/

 /*  mainFont   = SetFont(15, (char*)"Open Sans");

   desktopHeightField = CreateStatic(tMainWin, 10, 10, 140, 17, mainFont);
                        ChangeTextStatic(desktopHeightField, (char*)"Ширина рабочего стола: ");
   desktopWeightField = CreateStatic(tMainWin, 10, 30, 140, 17, mainFont);
                        ChangeTextStatic(desktopWeightField, (char*)"Высота рабочего стола: ");

   desktopHeight = CreateStatic(tMainWin, 150, 10, 30, 17, mainFont);
                   SetIntStatic(desktopHeight, desktopSize.right);
   desktopWeight = CreateStatic(tMainWin, 150, 30, 30, 17, mainFont);
                   SetIntStatic(desktopWeight, desktopSize.bottom);
   mouseXPosField = CreateStatic(tMainWin, 10, 50, 140, 17, mainFont);
                    ChangeTextStatic(mouseXPosField, (char*)"Мышь ось Х: ");
   mouseYPosField = CreateStatic(tMainWin, 10, 70, 140, 17, mainFont);
                    ChangeTextStatic(mouseYPosField , (char*)"Мышь ось У: ");

   mouseXPos = CreateStatic(tMainWin, 150, 50, 30, 17, mainFont);
               SetIntStatic(mouseXPos, 0);
   mouseYPos = CreateStatic(tMainWin, 150, 70, 30, 17, mainFont);
               SetIntStatic(mouseYPos, 0);

   mWinHField = CreateStatic(tMainWin, 10, 90, 140, 17, mainFont);
                ChangeTextStatic(mWinHField, (char*)"Ширина главного окна: ");
   mWinWField = CreateStatic(tMainWin, 10, 110, 140, 17, mainFont);
                ChangeTextStatic(mWinWField, (char*)"Высота главного окна: ");
   mWinH     = CreateStatic(tMainWin, 150, 90, 30, 17, mainFont);
               SetIntStatic(mWinH, tMainH);
   mWinW     = CreateStatic(tMainWin, 150, 110, 30, 17, mainFont);
               SetIntStatic(mWinW, tMainW);
   mWinCoordinatesXField = CreateStatic(tMainWin, 10, 130, 140, 17, mainFont);
                           ChangeTextStatic(mWinCoordinatesXField, (char*)"X главного окна: ");
   mWinCoordinatesYField = CreateStatic(tMainWin, 10, 150, 140, 17, mainFont);
                           ChangeTextStatic(mWinCoordinatesYField, (char*)"Y главного окна: ");
   mWinCoordinatesX = CreateStatic(tMainWin, 150, 130, 30, 17, mainFont);
                      SetIntStatic(mWinCoordinatesX, 0);
   mWinCoordinatesY = CreateStatic(tMainWin, 150, 150, 30, 17, mainFont);
                      SetIntStatic(mWinCoordinatesY, 0);

   resizePlusBtn   = CreateButton(tMainWin, 200, 10, 50, 17, mainFont);
                     ChangeTextButton(resizePlusBtn, (char*)"+");

   resizeMinusBtn   = CreateButton(tMainWin, 250, 10, 50, 17, mainFont);
                      ChangeTextButton(resizeMinusBtn, (char*)"-");
   segmentButton    = CreateButton(tMainWin, 10, 170, 125, 17, mainFont);
                      ChangeTextButton(segmentButton, (char*)"Скрыть наброски");
   segmentSubButton = CreateButton(tMainWin, 10, 190, 17, 65, mainFont);
                      ChangeTextButton(segmentSubButton, (char*)"<");
   segmentAddButton = CreateButton(tMainWin, 117, 190, 17, 65, mainFont);
                      ChangeTextButton(segmentAddButton, (char*)">");

   addMouseMoveHandler(mouseXPos,  MouseMoveXHandle);
   addMouseMoveHandler(mouseYPos,  MouseMoveYHandle);
   addButtonHandler(resizePlusBtn, tMainWin, IncreaseMainWindowSize);
   addButtonHandler(resizeMinusBtn,tMainWin, DecreaseMainWindowSize);
   addButtonHandler(segmentButton, tMainWin, ShowHideSegment);
   addButtonHandler(segmentButton, segmentSubButton, ActivateDisactivateButton);
   addButtonHandler(segmentButton, segmentAddButton, ActivateDisactivateButton);
   addButtonHandler(segmentButton, resizePlusBtn,    ActivateDisactivateButton);
   addButtonHandler(segmentButton, resizeMinusBtn,   ActivateDisactivateButton);
   addButtonHandler(segmentButton, desktopHeightField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, desktopWeightField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, desktopHeight, ActivateDisactivateButton);
   addButtonHandler(segmentButton, desktopWeight, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mouseXPosField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mouseYPosField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mouseXPos, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mouseYPos, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinHField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinWField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinH, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinW, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinCoordinatesXField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinCoordinatesYField, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinCoordinatesX, ActivateDisactivateButton);
   addButtonHandler(segmentButton, mWinCoordinatesY, ActivateDisactivateButton);
   counter.value = 0;
   addButtonHandler(segmentAddButton, tMainWin,    IncrementSegment);
   addButtonHandler(segmentSubButton, tMainWin,    DecrementSegment);
   addResizeHandler(mWinH, tMainWin,  ShowMainWindowH);
   addResizeHandler(mWinW, tMainWin,  ShowMainWindowW);
   addRemoveHandler(mWinCoordinatesX, tMainWin, ShowMainWindowX);
   addRemoveHandler(mWinCoordinatesY, tMainWin, ShowMainWindowY);*/

   ShowWindow(tMainWin.self,   1);               // ALL GRAPHICAL ELEMENTS SHOULD BE PLACED AFTER THIS FUNCTION

   tCreateThread(HelloThread);
   tCreateThread(BuyThread);

  /* fistHourNum = CreateNumSegment(tMainWin, 20, 5, 27, 190);
   SetBkColorNumSegment(&fistHourNum, RGB(0, 0, 0));
   SetColorNumSegment(&fistHourNum, RGB(0, 255, 0));

   secondHourNum = CreateNumSegment(tMainWin, 20, 5, 77, 190);
   SetBkColorNumSegment(&secondHourNum, RGB(0, 0, 0));
   SetColorNumSegment(&secondHourNum, RGB(0, 255, 0));

   tMainColor = GetPixel(GetDC(tMainWin.self), 0, 0);
                SetStaticBkColor(tMainColor);*/

   return TboxRun();
}

void HelloThread(void)
{
  static clock_t bgnClkVal     = clock();
         clock_t currentClkVal = clock();
  tPrintf(dbgLabel1, "Second timer: %d", (currentClkVal - bgnClkVal)/CLOCKS_PER_SEC);
  Sleep(1000);
}

void BuyThread(void)
{
  static clock_t bgnClkVal     = clock();
         clock_t currentClkVal = clock();
  tPrintf(dbgLabel2, "Ms timer: %d", (currentClkVal - bgnClkVal));
  Sleep(1);
}

/*void MouseMoveXHandle(TBOXUNIT item, int x, int y)
{
  SetIntStatic(item,  x);
}

void MouseMoveYHandle(TBOXUNIT item, int x, int y)
{
  SetIntStatic(item,  y);
}

void IncreaseMainWindowSize(TBOXUNIT b, TBOXUNIT *wmItem)
{
  RECT localSize;

  GetWindowRect(wmItem->self, &localSize);
  SetSizeWindow(*wmItem, ((localSize.right - localSize.left) + 5), ((localSize.bottom - localSize.top) + 5));
}

void DecreaseMainWindowSize(TBOXUNIT b, TBOXUNIT *wmItem)
{
  RECT localSize;

  GetWindowRect(wmItem->self, &localSize);
  SetSizeWindow(*wmItem, (localSize.right - localSize.left - 5), (localSize.bottom - localSize.top - 5));
}

void ShowMainWindowH(TBOXUNIT staticItem, TBOXUNIT windItem)
{
  RECT localSize;

  GetWindowRect(windItem.self, &localSize);
  SetIntStatic(staticItem,  localSize.right - localSize.left);
}

void ShowMainWindowW(TBOXUNIT staticItem, TBOXUNIT windItem)
{
  RECT localSize;

  GetWindowRect(windItem.self, &localSize);
  SetIntStatic(staticItem,  localSize.bottom - localSize.top);
}

void ShowMainWindowX(TBOXUNIT staticItem, TBOXUNIT windItem)
{
  RECT localSize;

  GetWindowRect(windItem.self, &localSize);
  SetIntStatic(staticItem,  localSize.left);
}

void ShowMainWindowY(TBOXUNIT staticItem, TBOXUNIT windItem)
{
  RECT localSize;

  GetWindowRect(windItem.self, &localSize);
  SetIntStatic(staticItem,  localSize.top);
}

void ShowHideSegment(TBOXUNIT b, TBOXUNIT *windItem)
{
  static char state = 0;

  if(!state)
  {
    state = 1;
    ChangeTextButton(b, (char*)"Показать наброски");
    HideNumSegment(fistHourNum);
    HideNumSegment(secondHourNum);
  }
  else
  {
    state = 0;
    ChangeTextButton(b, (char*)"Скрыть наброски");
    ShowNumSegment(fistHourNum);
    ShowNumSegment(secondHourNum);
  }
}

void ActivateDisactivateButton(TBOXUNIT b, TBOXUNIT *windItem)
{
  if(!windItem->state)
  {
    windItem->state = 1;
    DisableTunit(*windItem);
    ShowWindow(windItem->self, 0);
  }
  else
  {
    windItem->state = 0;
    EnableTunit(*windItem);
    ShowWindow(windItem->self, 1);
  }
}

void IncrementSegment(TBOXUNIT b, TBOXUNIT *windItem)
{

  if(counter.value < 99)
    counter.value++;
  else
    counter.value = 0;

  SetValueNumSegment(&fistHourNum,   counter.value/10);
  SetValueNumSegment(&secondHourNum, counter.value%10);
}

void DecrementSegment(TBOXUNIT b, TBOXUNIT *windItem)
{

  if(counter.value > 0)
    counter.value--;
  else
    counter.value = 99;

  SetValueNumSegment(&fistHourNum,   counter.value/10);
  SetValueNumSegment(&secondHourNum, counter.value%10);
}
*/
/*  This function is called by the Windows function DispatchMessage()  */

/*LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECTANGLEFIG tmpRect;
    RECT         WindowRect;
    int          ret = 0;
    time_t       Time;
    tm           *tTm;

    switch (message)resizePlusBtn
    {
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        case WM_CREATE:mWinHField = CreateStatic(tMainWin, 10, 90, 140, 17, mainFont);
                ChangeTextStatic(mWinHField, "Ширина главного окна: ");

            break;
        case WM_SIZE:        GetClientRect(hwnd1, &WindowRect);
                             SetIntStatic(WinH, WindowRect.right);
                             SetIntStatic(WinW, WindowRect.bottom);
                             lineBorder = CreateRectangle(hwnd1);
                             lineBorder.color = RGB(0, 0, 0);
                             ChangeSizeRectangle(&lineBorder, 1,   (WindowRect.bottom - 20));
                             ChangePosRectangle(&lineBorder,  125, 10);
                             DrawRectangle(lineBorder);

            break;
        case WM_COMMAND:     if(LOWORD(wParam) == ClearButton.id)
                             {
                               tmpRect = CreateRectangle(hwnd);
                               tmpRect.color = GetPixel(GetDC(hwnd1), 0, 0);
                               GetClientRect(hwnd1, &WindowRect);
                               ChangeSizeRectangle(&tmpRect, (WindowRect.right - 126), WindowRect.bottom);
                               ChangePosRectangle(&tmpRect, 126 , 0);
                               DrawRectangle(tmpRect);
                             }
                             if(LOWORD(wParam) == CheckB.id)
                             {
                               if(HIWORD(wParam) == BN_CLICKED)
                               {
                                 if (IsDlgButtonChecked(hwnd, CheckB.id))
                                 {
                                   CheckDlgButton(hwnd, CheckB.id, BST_UNCHECKED);
                                   EnableWindow(ClearButton.self, FALSE);
                                 }
                                 else
                                 {
                                   CheckDlgButton(hwnd, CheckB.id, BST_CHECKED);
                                   EnableWindow(ClearButton.self, TRUE);
                                 }
                               }
                             }
                             if(LOWORD(wParam) == RadBtn1.id)
                             {
                               if(HIWORD(wParam) == BN_CLICKED)
                               {
                                 if (!IsDlgButtonChecked(hwnd, RadBtn1.id))
                                 {
                                   CheckDlgButton(hwnd, RadBtn1.id, BST_CHECKED);
                                   CheckDlgButton(hwnd, RadBtn2.id, BST_UNCHECKED);
                                   EnableWindow(ComboxNew.self, FALSE);
                                 }
                               }
                             }
                             if(LOWORD(wParam) == RadBtn2.id)
                             {
                               if(HIWORD(wParam) == BN_CLICKED)
                               {
                                 if (!IsDlgButtonChecked(hwnd, RadBtn2.id))
                                 {
                                   CheckDlgButton(hwnd, RadBtn2.id, BST_CHECKED);
                                   CheckDlgButton(hwnd, RadBtn1.id, BST_UNCHECKED);
                                   EnableWindow(ComboxNew.self, TRUE);
                                 }
                               }
                             }
            break;
         case WM_LBUTTONDOWN: if(LOWORD(lParam) > 126)
                              {
                                tmpRect = CreateRectangle(hwnd);
                                tmpRect.color = RGB((rand() % 255), (rand() % 255), (rand() % 255));
                                ChangeSizeRectangle(&tmpRect, 20, 20);
                                ChangePosRectangle(&tmpRect,  LOWORD(lParam), HIWORD(lParam));
                                DrawRectangle(tmpRect);
                              }
          break;
         case WM_LBUTTONUP:

          break;
         case WM_MOUSEMOVE:  SetIntStatic(MouseX,  LOWORD(lParam));
                             SetIntStatic(MouseY,  HIWORD(lParam));
            break;
        case WM_USER:        Time = time(NULL);
                             tTm = localtime(&Time);
                             SendMessage(hwnd1, WM_SETTEXT,0,(LPARAM)asctime(tTm));
            break;

        case WM_CTLCOLORSTATIC: ret = GetStaticBkColor((HDC)wParam);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return ret;
}*/
// Tread handlers
/*DWORD WINAPI sendTimeEvent(PVOID pParam)
{
  while(1)
  {
    SendMessage(hwnd1, WM_USER, 0, 0);
    Sleep(1000);
  }
}*/

