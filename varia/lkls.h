/**
 *link list
 */
#ifndef VR_LKLS_H
#define VR_LKLS_H
#include "include/lkls.h"
#define VR_LKLS_INIT(ls)			\
  do						\
    {						\
      (ls)->head=NULL;				\
      (ls)->foot=NULL;				\
      (ls)->size=0;				\
    } while(0)

struct vr_lkls_nd {
  struct vr_lkls_nd* next;
  void* val;
  int size;
};

struct vr_lkls {
  vr_lkls_nd* head;
  vr_lkls_nd* foot;
  int size;
};

#endif
