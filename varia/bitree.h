/* binary tree */
#ifndef VR_BITREE_H
#define VR_BITREE_H
#include "include/bitree.h"

#define VR_BITREE_ND_INIT(nd)			\
  do						\
    {						\
      (nd)->key=NULL;				\
      (nd)->val=NULL;				\
      (nd)->kysz=0;				\
      (nd)->vlsz=0;				\
      (nd)->p=NULL;				\
      (nd)->left=NULL;				\
      (nd)->right=NULL;				\
    } while(0)

struct vr_bitree_nd {
  void* key;
  void* val;
  int kysz;
  int vlsz;
  struct vr_bitree_nd* p;
  struct vr_bitree_nd* left;
  struct vr_bitree_nd* right;
};

struct vr_bitree {
  vr_bitree_nd* root;
  int size;
  vr_compare_fn_t comp;
};

#endif
