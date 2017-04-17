/**
 *single link list include
 */
#ifndef VR_SLIST_H
#define VR_SLIST_H

#include "vr_common.h"
#include "vr_type.h"

#define vr_slist_init(ls)			\
  do						\
    {						\
      (ls)->head=NULL;				\
      (ls)->foot=NULL;				\
      (ls)->size=0;				\
    } while(0)

typedef struct vr_slist_nd vr_slist_nd;
typedef struct vr_slist vr_slist;

struct vr_slist_nd {
  struct vr_slist_nd* next;
  void* val;
};

struct vr_slist {
  vr_slist_nd* head;
  vr_slist_nd* foot;
  int size;
};

VR_DECLARE_EXPORT
vr_slist* vr_slist_new();
VR_DECLARE_EXPORT
void vr_slist_des(vr_slist* ls,vr_val_des_func des);
VR_DECLARE_EXPORT
void vr_slist_ins(vr_slist* ls,void* val,int pos);
VR_DECLARE_EXPORT
void vr_slist_apd(vr_slist* ls,void* val);
VR_DECLARE_EXPORT
void vr_slist_upd(vr_slist* ls,void* val,int pos);
VR_DECLARE_EXPORT
void* vr_slist_get(vr_slist* ls,int pos);
VR_DECLARE_EXPORT
void vr_slist_trav(vr_slist* ls,void(*trav_hook)(int,void*));
VR_DECLARE_EXPORT
void vr_slist_del(vr_slist* ls,int pos,vr_val_des_func des);
VR_DECLARE_EXPORT
void vr_slist_cln(vr_slist* ls,vr_val_des_func des);
VR_DECLARE_EXPORT
int vr_slist_size(vr_slist* ls);

#endif
