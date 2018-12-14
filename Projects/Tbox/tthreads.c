#include "tbox.h"

static struct
{
  int        stackSize;
  TBOXTHREAD base[TBOX_THREADS_ENTITY_SIZE];
}tThreads;
static DWORD WINAPI threadService(LPVOID param);

void tCreateThread(void (*routin)(void))
{
  if(tThreads.stackSize < TBOX_THREADS_ENTITY_SIZE)
  {
    tThreads.base[tThreads.stackSize].thread = routin;
    tThreads.base[tThreads.stackSize].event  = INVALID_HANDLE_VALUE;
    tThreads.base[tThreads.stackSize].etype  = tNOEVENT;
    tThreads.base[tThreads.stackSize].hndl   = CreateThread(NULL, 0, threadService, &tThreads.base[tThreads.stackSize], 0, NULL);
    tThreads.stackSize++;
  }
}

/*void tStartThread(TTHREAD thread, void* (*callback)(void*))
{

}*/

/*void tAddEventToThread(tBoxEventType etype, TTHREAD thread)
{

}

void tEvent(TTHREAD thread)
{

}

void tResetEvent(TTHREAD thread)
{

}*/

static DWORD WINAPI threadService(LPVOID param)
{
  TBOXTHREAD *service = param;

  while(1)
  {
    if(service->etype != tNOEVENT)
    {
      WaitForSingleObject(service->event, INFINITE);
    }
    service->thread();
    if(service->etype == tMANUALRESET)
    {
      ResetEvent(service->event);
    }
  }
}

