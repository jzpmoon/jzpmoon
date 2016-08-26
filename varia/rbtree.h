/* red balck tree */
#ifndef VR_RBTREE_H
#define VR_RBTREE_H
#include "bitree.h"
#include "include/rbtree.h"
#define VR_RED 0
#define VR_bLK 1

struct vr_rbtree_nd {
  struct vr_bitree_nd bitree_nd;
  int clr;
  struct vr_rbtree_nd* p;
};
struct vr_rbtree {
  vr_rbtree_nd* root;
  int size;
};

#endif 
