/* red balck tree */
#ifndef VR_RBTREE_H
#define VR_RBTREE_H
#include "trcomn.h"
#define VR_RED 0
#define VR_bLK 1
typedef struct vr_rbt_nd {
  void* key;
  void* val;
  int kysz
  int vlsz;
  int clr;
  struct vr_rbt_nd* prnt;
  struct vr_rbt_nd* left;
  struct vr_rbt_nd* right;
} vr_rbt_nd;
typedef struct vr_rbtree {
  vr_rbt_nd* root;
  int size;
} vr_rbtree;

vr_rbtree* vr_rbtree_init();
int vr_rbtree_des(vr_rbtree* tree);
int vr_rbtree_ins(vr_rbtree* tree,void* key,void* val,int kysz,int vlsz);
int vr_rbtree_get(vr_rbtree* tree,void* key,void* val,int kysz,int* vlsz);
int vr_rbtree_del(vr_rbtree* tree,void* key,int kysz);
int vr_rbtree_size(vr_rbtree* tree);
#endif 
