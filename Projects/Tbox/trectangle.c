#include "tbox.h"

/* Create rectangle abstraction with the Size? Coordinates & Color of Window Owner values*/
RECTANGLEFIG CreateRectangle(TWINDOW wOwner)
{
    RECTANGLEFIG ret;

    ret.owner = GetDC(wOwner.self);
    GetWindowRect(wOwner.self, &ret.ownercoordinates);
    ret.coordinate.top  = 0;
    ret.coordinate.left = 0;
    ret.coordinate.bottom = ret.ownercoordinates.bottom - ret.ownercoordinates.top;
    ret.coordinate.right  = ret.ownercoordinates.right - ret.ownercoordinates.left;
    ret.color = GetBkColor(ret.owner);

    return ret;
}

void DrawRectangle(RECTANGLEFIG rect)
{
  HBRUSH   brush;

  if(rect.owner != 0)
  {
    brush = CreateSolidBrush(rect.color);
    FillRect(rect.owner, &rect.coordinate, brush);
    DeleteObject(brush);
  }
}

void FillColorRectangle(RECTANGLEFIG *rect, int r, int g, int b)
{
  if(rect->owner != 0)
  {
    rect->color = RGB(r, g, b);
  }
}

void ChangePosRectangle(RECTANGLEFIG *rect, int x, int y)
{
  int ownW = 0,
      ownH = 0;
  if(rect->owner != 0)
  {
    ownH = rect->ownercoordinates.bottom - rect->ownercoordinates.top;
    ownW = rect->ownercoordinates.right  - rect->ownercoordinates.left;
    if((rect->coordinate.bottom + y) < ownH)
    {
      rect->coordinate.bottom += y;
      rect->coordinate.top = y;
    }
    if((rect->coordinate.right + x) < ownW)
    {
      rect->coordinate.right += x;
      rect->coordinate.left = x;
    }
  }
}

void ChangeSizeRectangle(RECTANGLEFIG *rect, int w, int h)
{
  int ownW = 0,
      ownH = 0;
  if(rect->owner != 0)
  {
    ownH = rect->ownercoordinates.bottom - rect->ownercoordinates.top;
    ownW = rect->ownercoordinates.right  - rect->ownercoordinates.left;
    if((rect->coordinate.top + h) < ownH)
    {
      rect->coordinate.bottom = h;
    }
    if((rect->coordinate.left + w) < ownW)
    {
      rect->coordinate.right = w;
    }
  }
}

/*  Main concept:

    000000000
    0       0
    0  222  0
    0 1   3 0
    0 1   3 0
    0 1   3 0
    0  444  0
    0 5   7 0
    0 5   7 0
    0 5   7 0
    0  666  0
    0       0
    000000000
*/
typedef enum
{
  BASE_SEGMENT = 0,
  TOP_SEGMENT,
  TOP_LEFT_SEGMENT,
  TOP_RIGHT_SEGMENT,
  MID_SEGMENT,
  BOT_LEFT_SEGMENT,
  BOT_RIGHT_SEGMENT,
  BOTTOM_SEGMENT,
  END_OF_SEGMENT
}segPos;

TNUMSEGMENT  CreateNumSegment(TWINDOW owner, int faceW, int faceH, int x, int y)
{
  int         tmpW = 0,
              tmpH = 0;
  int         tmpX = 0,
              tmpY = 0;
  int         r = 0, g = 0, b = 0;
  segPos      count = 0;
  TNUMSEGMENT ret;

  ret.bkColor     = GetPixel(GetDC(owner.self), 0, 0);
  ret.bkFaceColor = RGB(0, 0, 0);
  ret.faceColor   = RGB(0xFF, 0xFF, 0xFF);

  for(count = 0; count < END_OF_SEGMENT; count++)
  {
    ret.segment[count] = CreateRectangle(owner);
    if(count > BASE_SEGMENT)
    {
      r = 0xFF;
      g = 0xFF;
      b = 0xFF;
    }
    switch(count)
    {
     case   BASE_SEGMENT:      ret.bkFaceColor = RGB(r, g, b);
                               tmpW = faceW + 4*faceH;
                               tmpH = 2*faceW + 5*faceH;
                               tmpX = x;
                               tmpY = y;
       break;
     case   TOP_SEGMENT:       tmpW = faceW;
                               tmpH = faceH;
                               tmpX = x + 2*faceH;
                               tmpY = y + faceH;
       break;
     case   TOP_LEFT_SEGMENT:  tmpW = faceH;
                               tmpH = faceW;
                               tmpX = x + faceH;
                               tmpY = y + 2*faceH;
       break;
     case   TOP_RIGHT_SEGMENT: tmpW = faceH;
                               tmpH = faceW;
                               tmpX = x + 2*faceH + faceW;
                               tmpY = y + 2*faceH;
       break;
     case   MID_SEGMENT:       tmpW = faceW;
                               tmpH = faceH;
                               tmpX = x + 2*faceH;
                               tmpY = y + 2*faceH + faceW;
       break;
     case   BOT_LEFT_SEGMENT:  tmpW = faceH;
                               tmpH = faceW;
                               tmpX = x + faceH;
                               tmpY = y + 3*faceH + faceW;
       break;
     case   BOT_RIGHT_SEGMENT: tmpW = faceH;
                               tmpH = faceW;
                               tmpX = x + 2*faceH + faceW;
                               tmpY = y + 3*faceH + faceW;
       break;
     case   BOTTOM_SEGMENT:    tmpW = faceW;
                               tmpH = faceH;
                               tmpX = x + 2*faceH;
                               tmpY = y + 3*faceH + 2*faceW;
       break;
     case   END_OF_SEGMENT:    break;
       break;
    }
    ChangeSizeRectangle(&ret.segment[count], tmpW, tmpH);
    ChangePosRectangle(&ret.segment[count],  tmpX, tmpY);
    FillColorRectangle(&ret.segment[count],  r, g, b);
    DrawRectangle(ret.segment[count]);
  }

  ret.value = 8;

  return ret;
}

void         HideNumSegment(TNUMSEGMENT seg)
{
  int count = 0;

  for(count = BASE_SEGMENT; count < END_OF_SEGMENT; count++)
  {
    FillColorRectangle(&seg.segment[count],  GetRValue(seg.bkColor), GetGValue(seg.bkColor), GetBValue(seg.bkColor));
    DrawRectangle(seg.segment[count]);
  }
}

void         ShowNumSegment(TNUMSEGMENT seg)
{
  int count = 0;

  for(count = BASE_SEGMENT; count < END_OF_SEGMENT; count++)
  {
   /* if(count == BASE_SEGMENT)
    {
      FillColorRectangle(&seg.segment[count],  GetRValue(seg.bkFaceColor), GetGValue(seg.bkFaceColor), GetBValue(seg.bkFaceColor));
    }
    else
    {
      FillColorRectangle(&seg.segment[count],  GetRValue(seg.faceColor), GetGValue(seg.faceColor), GetBValue(seg.faceColor));
    }*/
    SetValueNumSegment(&seg, seg.value);
    DrawRectangle(seg.segment[count]);
  }
}

void         SetPositionNumSegment(TNUMSEGMENT seg, int x, int y)
{

}

void         SetSizeNumSegment(TNUMSEGMENT seg, int w, int h)
{

}

void         SetBkColorNumSegment(TNUMSEGMENT *seg, COLORREF color)
{
  int count = 0;

  seg->bkFaceColor = color;

  for(count = BASE_SEGMENT; count < END_OF_SEGMENT; count++)
  {
    if(count == BASE_SEGMENT)
    {
      FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
    }
    else
    {
      FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
    }
    DrawRectangle(seg->segment[count]);
  }
}

void         SetColorNumSegment(TNUMSEGMENT *seg, COLORREF color)
{
  int count = 0;

  seg->faceColor = color;

  for(count = BASE_SEGMENT; count < END_OF_SEGMENT; count++)
  {
    if(count == BASE_SEGMENT)
    {
      FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
    }
    else
    {
      FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
    }
    DrawRectangle(seg->segment[count]);
  }
}

void         SetValueNumSegment(TNUMSEGMENT *seg, int value)
{
  int count = 0;

  if(value < 10)
  {
    seg->value = value;

    for(count = BASE_SEGMENT; count < END_OF_SEGMENT; count++)
    {
      switch(count)
      {
         case   BASE_SEGMENT:    FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
           break;
         case   TOP_SEGMENT:      if((seg->value == 1) || (seg->value == 4))
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   TOP_LEFT_SEGMENT: if((seg->value == 1) || (seg->value == 2) || (seg->value == 3) || (seg->value == 7))
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   TOP_RIGHT_SEGMENT: if((seg->value == 5) || (seg->value == 6))
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   MID_SEGMENT:      if((seg->value == 1) || (seg->value == 7) || (seg->value == 0))
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   BOT_LEFT_SEGMENT: if((seg->value == 1) || (seg->value == 3) || (seg->value == 4) || (seg->value == 5) || (seg->value == 7) || (seg->value == 9))
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   BOT_RIGHT_SEGMENT:if(seg->value == 2)
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   BOTTOM_SEGMENT:   if((seg->value == 1) || (seg->value == 4) || (seg->value == 7))
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->bkFaceColor), GetGValue(seg->bkFaceColor), GetBValue(seg->bkFaceColor));
                                }
                                else
                                {
                                  FillColorRectangle(&seg->segment[count],  GetRValue(seg->faceColor), GetGValue(seg->faceColor), GetBValue(seg->faceColor));
                                }
           break;
         case   END_OF_SEGMENT:    break;
           break;
        }
        DrawRectangle(seg->segment[count]);
      }
    }
}
