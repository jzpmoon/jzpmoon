/* link stack */
#include "include/vr_error.h"
#include "include/vr_stack.h"

vr_stack* vr_stack_new()
{
  vr_stack* stk=(vr_stack*) malloc(sizeof(vr_stack));
  if(stk){
    vr_slist_init(stk);
  }
  return stk;
}

void vr_stack_des(vr_stack* stk,vr_val_des_func des)
{
  vr_slist_cln(stk,des);
  free(stk);
}

void vr_stack_push(vr_stack* stk,void* val)
{
  vr_slist_ins(stk,val,0);
}

void* vr_stack_pop(vr_stack* stk)
{
  void* val=NULL;
  VR_STK_EMPTY_CHK(vr_slist_size(stk));
  val=vr_slist_get(stk,0);
  vr_slist_del(stk,0,NULL);
  return val;
}

void vr_stack_cln(vr_stack* stk,vr_val_des_func des)
{
  vr_slist_cln(stk,des);
}

int vr_stack_size(vr_stack* stk)
{
  return vr_slist_size(stk);
}
