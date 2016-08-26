/* red balck tree */
#include "rbtree.h"

vr_rbtree* vr_rbtree_init(){
  vr_rbtree* tree= (vr_rbtree*) malloc(sizeof(vr_rbtree));
  if(tree!=NULL){
    tree->root=NULL;
    tree->size=0;
  }
  return tree;
}
