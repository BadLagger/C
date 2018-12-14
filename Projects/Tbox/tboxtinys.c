#include "tboxtinys.h"
#include "trectangle.h"
#include "tbox.h"
#include <stdlib.h>


static struct
{
  int          TinyNum;
  RECTANGLEFIG *TinyTab;
  RECTANGLEFIG *tmpTab;
}tiny;

void CreateNewTiny(int x, int y)
{
  if(tiny.TinyNum != 0)
  {

  }
  tiny.TinyNum++;
  tiny.TinyTab = malloc(sizeof(RECTANGLEFIG) * tiny.TinyNum);
}

int  GetTinysNumber(void)
{
  return 0;
}

int  CheckTinyPos(int x, int y)
{
  return 0;
}

void DestroyTinyById(int id)
{

}
