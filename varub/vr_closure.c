#include <stdlib.h>
#include "include/vr_list.h"

vr_closure* vr_closure_new()
{
  vr_closure* closure=malloc(sizeof(vr_closure));
  vr_closure_init(closure);
  return closure;
}

int vr_closure_init(vr_closure* closure)
{
  if(!closure) return -1;
  closure->head=NULL;
  closure->foot=NULL;
  closure->cmpr=NULL;
  closure->desr=NULL;
  closure->length=0;
  return 0;
}

void vr_closure_exec(vr_closure* closure,void* params,void* retval)
{
  
  vr_closure_func func=NULL;
  vr_index index=vr_list_head(closure);
  while(index)
    {
      func=vr_list_index(index);
      (*func)(params,retval);
      index=vr_list_next(closure,index);
    }
}
