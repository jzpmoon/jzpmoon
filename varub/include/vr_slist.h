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

vr_slist* vr_slist_new();
void vr_slist_des(vr_slist* ls,vr_val_des_func des);
void vr_slist_ins(vr_slist* ls,void* val,int pos);
void vr_slist_apd(vr_slist* ls,void* val);
void vr_slist_upd(vr_slist* ls,void* val,int pos);
void* vr_slist_get(vr_slist* ls,int pos);
void vr_slist_del(vr_slist* ls,int pos,vr_val_des_func des);
void vr_slist_cln(vr_slist* ls,vr_val_des_func des);
int vr_slist_size(vr_slist* ls);

#endif
