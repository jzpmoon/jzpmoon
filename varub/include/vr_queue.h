/* link queue include */
#ifndef VR_QUEUE_H
#define VR_QUEUE_H

#include "vr_common.h"
#include "vr_slist.h"

#define vr_queue_init(que)			\
  vr_slist_init(que)

typedef struct vr_slist vr_queue;

vr_queue* vr_queue_new();
void vr_queue_des(vr_queue* que,vr_val_des_func des);
void vr_queue_enq(vr_queue* que,void* val);
void* vr_queue_deq(vr_queue* que);
void vr_queue_cln(vr_queue* que,vr_val_des_func des);
int vr_queue_size(vr_queue* que);

#endif
