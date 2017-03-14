/* red balck tree include */
#ifndef VR_RBTREE_H
#define VR_RBTREE_H

#include "vr_common.h"
#include "vr_type.h"

typedef struct vr_rbt_nd vr_rbt_nd;
typedef struct vr_rbtree vr_rbtree;

#define VR_RED 0
#define VR_BLACK 1
struct vr_rbt_nd {
  void* key;
  void* val;
  vr_rbt_nd* left;
  vr_rbt_nd* right;
  vr_rbt_nd* parent;
  int color;
};

struct vr_rbtree {
  vr_rbt_nd* root;
  vr_compare_func cmp;
  int size;
};

#define vr_rbtree_init(tree,cmp)		\
  do{						\
    (tree)->root=NULL;				\
    (tree)->cmp=(cmp);				\
    (tree)->size=0;				\
  }while(0)

VR_DECLARE_EXPORT
vr_rbtree* vr_rbtree_new(vr_compare_func cmp);
VR_DECLARE_EXPORT
void vr_rbtree_des(vr_rbtree* tree,vr_kv_des_func des);
VR_DECLARE_EXPORT
int vr_rbtree_ins(vr_rbtree* tree,void* key,void* val);
VR_DECLARE_EXPORT
void* vr_rbtree_get(vr_rbtree* tree,void* key);
VR_DECLARE_EXPORT
void vr_rbtree_del(vr_rbtree* tree,void* key,vr_kv_des_func des);
VR_DECLARE_EXPORT
void vr_rbtree_cln(vr_rbtree* tree,vr_kv_des_func des);
VR_DECLARE_EXPORT
int vr_rbtree_size(vr_rbtree* tree);
VR_DECLARE_EXPORT
void vr_rbtree_trav(vr_rbtree* tree,vr_trav_func hook,int type);

#endif
