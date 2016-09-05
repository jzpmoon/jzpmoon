/* binary tree include */
#ifndef VR_BITREE_H_INCL
#define VR_BITREE_H_INCL
#include "types.h"
typedef struct vr_bitree_nd vr_bitree_nd;
typedef struct vr_bitree vr_bitree;
typedef int(*vr_bitree_nd_fn_t)();

vr_bitree* vr_bitree_new(vr_compare_fn_t comp);
void vr_bitree_des(vr_bitree* tree);
void vr_bitree_ins(vr_bitree* tree,void* key,void* val,int kysz,int vlsz);
int vr_bitree_get(vr_bitree* tree,void* key,void* val,int kysz,int* vlsz);
void vr_bitree_trav(vr_bitree* tree,vr_bitree_nd_fn_t hook);
void vr_bitree_del(vr_bitree* tree,void* key,int kysz);
void vr_bitree_cln(vr_bitree* tree);
int vr_bitree_size(vr_bitree* tree);
#endif
