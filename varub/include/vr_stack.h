/* link stack include */
#ifndef VR_STACK_H
#define VR_STACK_H

#include "vr_common.h"
#include "vr_slist.h"

#define vr_stack_init(stk)			\
  vr_slist_init(stk)

typedef struct vr_slist vr_stack;

VR_DECLARE_EXPORT
vr_stack* vr_stack_new();
VR_DECLARE_EXPORT
void vr_stack_des(vr_stack* stk,vr_val_des_func des);
VR_DECLARE_EXPORT
void vr_stack_push(vr_stack* stk,void* val);
VR_DECLARE_EXPORT
void* vr_stack_pop(vr_stack* stk,vr_val_des_func des);
VR_DECLARE_EXPORT
void vr_stack_cln(vr_stack* stk,vr_val_des_func des);
VR_DECLARE_EXPORT
int vr_stack_size(vr_stack* stk);

#endif
