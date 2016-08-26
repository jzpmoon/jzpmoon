/* link queue */
#include "lkque.h"
#include "lscomn.h"

vr_lkque* vr_lkque_new()
{
  vr_lkque* que=(vr_lkque*) malloc(sizeof(vr_lkque));
  if(que!=NULL){
    VR_LKLS_INIT(&que->ls);
  }
  return que;
}

void vr_lkque_des(vr_lkque* que)
{
  vr_lkls_cln(&que->ls);
  free(que);
}

void vr_lkque_enq(vr_lkque* que,void* val,int size)
{
  vr_lkls_apd(&que->ls,val,size);
}

void vr_lkque_deq(vr_lkque* que,void* val,int* size)
{
  vr_lkls* ls=&que->ls;
  VR_QUE_EMPTY_CHK(vr_lkls_size(ls));
  vr_lkls_get(ls,val,size,0);
  vr_lkls_del(ls,0);
}

void vr_lkque_cln(vr_lkque* que)
{
  vr_lkls_cln(&que->ls);
}

int vr_lkque_size(vr_lkque* que){
  return vr_lkls_size(&que->ls);
}
