/* link stack */
#include "lscomn.h"
#include "lkstk.h"

vr_lkstk* vr_lkstk_new()
{
  vr_lkstk* stk=(vr_lkstk*) malloc(sizeof(vr_lkstk));
  if(stk!=NULL){
    VR_LKLS_INIT(&stk->ls);
  }
  return stk;
}

void vr_lkstk_des(vr_lkstk* stk)
{
  vr_lkls_cln(&stk->ls);
  free(stk);
}

void vr_lkstk_pull(vr_lkstk* stk,void* val,int size)
{
  vr_lkls_ins(&stk->ls,val,size,0);
}

void vr_lkstk_pop(vr_lkstk* stk,void* val,int* size)
{
  vr_lkls* ls=&stk->ls;
  VR_STK_EMPTY_CHK(vr_lkls_size(ls));
  vr_lkls_get(ls,val,size,0);
  vr_lkls_del(ls,0);
}
void vr_lkstk_cln(vr_lkstk* stk)
{
  vr_lkls_cln(&stk->ls);
}
int vr_lkstk_size(vr_lkstk* stk)
{
  return vr_lkls_size(&stk->ls);
}
