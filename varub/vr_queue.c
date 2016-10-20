/* link queue */
#include "include/vr_error.h"
#include "include/vr_queue.h"

vr_queue* vr_queue_new()
{
  vr_queue* que=(vr_queue*) malloc(sizeof(vr_queue));
  if(que){
    vr_slist_init(que);
  }
  return que;
}

void vr_queue_des(vr_queue* que,vr_val_des_func des)
{
  vr_slist_cln(que,des);
  free(que);
}

void vr_queue_enq(vr_queue* que,void* val)
{
  vr_slist_apd(que,val);
}

void* vr_queue_deq(vr_queue* que)
{
  VR_QUE_EMPTY_CHK(vr_slist_size(que));
  void* val=vr_slist_get(que,0);
  vr_slist_del(que,0,NULL);
  return val;
}

void vr_queue_cln(vr_queue* que,vr_val_des_func des)
{
  vr_slist_cln(que,des);
}

int vr_queue_size(vr_queue* que){
  return vr_slist_size(que);
}
