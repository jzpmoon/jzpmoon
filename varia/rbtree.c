/* red balck tree */
#include "trcomn.h"
#include "rbtree.h"
#include "lkstk.h"

vr_rbt_nd* vr_rbt_nd_new();
void vr_rbt_nd_des(vr_rbt_nd* nd);
void vr_rbt_nd_set(vr_rbt_nd* nd,void* key,void* val,int kysz,int vlsz);
void vr_rbt_nd_get(vr_rbt_nd* nd,void* key,void* val,int kysz,int* vlsz);

vr_rbtree* vr_rbtree_new(){
  vr_rbtree* tree= (vr_rbtree*) malloc(sizeof(vr_rbtree));
  if(tree!=NULL){
    tree->root=NULL;
    tree->size=0;
  }
  return tree;
}

void vr_rbtree_des(vr_rbtree* tree){
  vr_rbt_nd* nd=tree->root;
  vr_rbt_nd* right_nd=NULL;
  vr_lkstk* stk=vr_lkstk_new();
  while(1){
    if(nd!=NULL){
      vr_lkstk_pull(stk,(void*)&nd,sizeof(void*));
      nd=nd->left;
    } else {
      int stk_size=vr_lkstk_size(stk);
      if(stk!=0){
	vr_lkstk_pop(stk,(void*)nd,NULL);
	right_nd=nd->right;
	vr_rbt_nd_des(nd);
	nd=right_nd;
      } else{
	vr_lkstk_des(stk);
	return;
      }
    }
  }
}

void vr_rbtree_ins(vr_rbtree* tree,void* key,void* val,int kysz,int vlsz)
{
  
}
