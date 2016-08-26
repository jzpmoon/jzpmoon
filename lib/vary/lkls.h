/**
 *link list
 */
#ifndef VR_LKLS_H
#define VR_LKLS_H

typedef struct vr_lkls_nd {
  struct vr_lkls_nd* next;
  void* val;
  int size;
} vr_lkls_nd;

typedef struct vr_lkls {
  vr_lkls_nd* head;
  vr_lkls_nd* foot;
  int size;
} vr_lkls;

vr_lkls* vr_lkls_init();
int vr_lkls_des(vr_lkls* ls);
int vr_lkls_ins(vr_lkls* ls,void* val,int size,int pos);
int vr_lkls_upd(vr_lkls* ls,void* val,int size,int pos);
int vr_lkls_get(vr_lkls* ls,void* val,int* size,int pos);
int vr_lkls_del(vr_lkls* ls,int pos);
int vr_lkls_size(vr_lkls* ls);
#endif
