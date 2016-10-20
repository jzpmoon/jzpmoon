/* binary tree include */
#ifndef VR_BITREE_H
#define VR_BITREE_H

#include "vr_common.h"
#include "vr_type.h"

#define VR_BITREE_ND_INIT(nd)			\
  do{						\
    (nd)->key=NULL;				\
    (nd)->val=NULL;				\
    (nd)->left=NULL;				\
    (nd)->right=NULL;				\
  } while(0)

#define VR_BITREE_INIT(tree,comp)		\
  do{						\
    (tree)->root=NULL;				\
    (tree)->size=0;				\
    (tree)->comp=comp;				\
  } while(0)

typedef struct vr_bitree_nd vr_bitree_nd;
typedef struct vr_bitree vr_bitree;

struct vr_bitree_nd {
  void* key;
  void* val;
  struct vr_bitree_nd* left;
  struct vr_bitree_nd* right;
};

struct vr_bitree {
  vr_bitree_nd* root;
  int size;
  vr_compare_func comp;
};

vr_bitree* vr_bitree_new(vr_compare_func comp);
void vr_bitree_des(vr_bitree* tree);
void vr_bitree_ins(vr_bitree* tree,void* key,void* val);
void* vr_bitree_get(vr_bitree* tree,void* key);
void vr_bitree_trav(vr_bitree* tree,vr_trav_func hook,int type);
void vr_bitree_del(vr_bitree* tree,void* key);
void vr_bitree_cln(vr_bitree* tree);
int vr_bitree_size(vr_bitree* tree);
#endif
