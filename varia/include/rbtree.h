/* red balck tree include */
#ifndef VR_RBTREE_H_INCL
#define VR_RBTREE_H_INCL

typedef struct vr_rbtree_nd vr_rbtree_nd;
typedef struct vr_rbtree vr_rbtree;

vr_rbtree* vr_rbtree_new();
void vr_rbtree_des(vr_rbtree* tree);
void 
vr_rbtree_ins(vr_rbtree* tree,
	      void* key,
	      void* val,
	      int kysz,
	      int vlsz);
void 
vr_rbtree_get(vr_rbtree* tree,
		   void* key,
		   void* val,
		   int kysz,
		   int* vlsz);
void vr_rbtree_del(vr_rbtree* tree,void* key,int kysz);
void vr_rbtree_cln(vr_rbtree* tree);
int vr_rbtree_size(vr_rbtree* tree);

#endif 
