/* binary tree */
#include "include/vr_bitree.h"
#include "include/vr_stack.h"

vr_bitree_nd* vr_bitree_nd_new();
void vr_bitree_nd_des(vr_bitree_nd* nd);
void vr_bitree_nd_set(vr_bitree_nd* nd,void* key,void* val);
void vr_bitree_nd_get(vr_bitree_nd* nd,void** key,void** val);
void vr_bitree_get_tglt(vr_bitree_nd* root,void* key,vr_bitree_nd** gra_nd,vr_bitree_nd** par_nd,vr_bitree_nd** nd,vr_compare_func comp);
void vr_bitree_pre_order(vr_bitree_nd* root,vr_trav_func hook);
void vr_bitree_in_order(vr_bitree_nd* root,vr_trav_func hook);
void vr_bitree_post_order(vr_bitree_nd* root,vr_trav_func hook);

vr_bitree* vr_bitree_new(vr_compare_func comp)
{
  vr_bitree* tree=malloc(sizeof(vr_bitree));
  if(tree!=NULL){
    VR_BITREE_INIT(tree,comp);
  }
  return tree;
}

void vr_bitree_des(vr_bitree* tree)
{
  vr_bitree_cln(tree);
  free(tree);
}

void vr_bitree_ins(vr_bitree* tree,void* key,void* val)
{
  if(val==NULL){
    vr_bitree_del(tree,key);
  }
  vr_bitree_nd* par_nd=NULL;
  vr_bitree_nd* nd=NULL;
  vr_bitree_get_tglt(tree->root,key,NULL,&par_nd,&nd,tree->comp);
  if(nd)
    vr_bitree_nd_set(nd,key,val);
  else{
    nd=vr_bitree_nd_new();
    vr_bitree_nd_set(nd,key,val);
    if(par_nd==NULL)
      tree->root=nd;
    else{
      int cmp=(* tree->comp)(key,par_nd->key);
      if(cmp>0)
	par_nd->right=nd;
      else
	par_nd->left=nd;
    }
    tree->size++;
  }
}

void* vr_bitree_get(vr_bitree* tree,void* key)
{
  vr_bitree_nd* nd=NULL;
  void* val=NULL;
  vr_bitree_get_tglt(tree->root,key,NULL,NULL,&nd,tree->comp);
  if(nd!=NULL)
    vr_bitree_nd_get(nd,NULL,&val);
  return val;
}

void vr_bitree_trav(vr_bitree* tree,vr_trav_func hook,int order)
{
  switch(order){
  case VR_TREE_PRE_ORDER_TRAV:vr_bitree_pre_order(tree->root,hook);break;
  case VR_TREE_IN_ORDER_TRAV:vr_bitree_in_order(tree->root,hook);break;
  case VR_TREE_POST_ORDER_TRAV:vr_bitree_post_order(tree->root,hook);break;
  }
}

void vr_bitree_del(vr_bitree* tree,void* key)
{
  vr_bitree_nd* nd=NULL;
  vr_bitree_nd* del_nd=NULL;
  vr_bitree_nd* par_del_nd=NULL;
  vr_bitree_nd* mv_nd=NULL;
  vr_bitree_get_tglt(tree->root,key,NULL,&par_del_nd,&nd,tree->comp);
  if(nd==NULL) return;
  if(nd->left==NULL||nd->right==NULL)
    del_nd=nd;
  else
    vr_bitree_get_tglt(nd->right,key,&par_del_nd,&del_nd,NULL,tree->comp);
  if(del_nd->left)
    mv_nd=del_nd->left;
  else
    mv_nd=del_nd->right;
  if(par_del_nd==NULL)
    tree->root=mv_nd;
  else
    if(par_del_nd->left==del_nd)
      par_del_nd->left=mv_nd;
    else
      par_del_nd->right=mv_nd;
  if(del_nd!=nd){
    void* key=NULL;
    void* val=NULL;
    vr_bitree_nd_get(del_nd,&key,&val);
    vr_bitree_nd_set(nd,key,val);
  }
  vr_bitree_nd_des(del_nd);
  tree->size--;
}

static int vr_compare_alway_eq(void* max,void* min){return 0;}
void vr_bitree_cln(vr_bitree* tree)
{
  vr_bitree_nd* del_nd=NULL;
  while(1){
    vr_bitree_get_tglt(tree->root,NULL,NULL,NULL,&del_nd,vr_compare_alway_eq);
    if(del_nd==NULL) break;
    vr_bitree_del(tree,del_nd->key);
  }
}

int vr_bitree_size(vr_bitree* tree)
{
  return tree->size;
}

void vr_bitree_pre_order(vr_bitree_nd* root,vr_trav_func hook)
{
  vr_bitree_nd* nd=root;
  vr_bitree_nd* tmp_nd=NULL;
  vr_stack* stk=vr_stack_new();
  do{
    if(nd){
      if(nd->right) vr_stack_push(stk,nd->right);
      tmp_nd=nd;nd=nd->left;
      if((*hook)(tmp_nd->key,tmp_nd->val)==-1) break;
    }else{
      if(vr_stack_size(stk))
	nd=vr_stack_pop(stk);
      else
	break;
    }
  } while(1);
  vr_stack_des(stk,NULL);
}

void vr_bitree_in_order(vr_bitree_nd* root,vr_trav_func hook)
{
  vr_bitree_nd* nd=root;
  vr_bitree_nd* tmp_nd=NULL;
  vr_stack* stk=vr_stack_new();
  do{
    if(nd){
      vr_stack_push(stk,(void*)nd);
      nd=nd->left;
    } else {
      if(vr_stack_size(stk)){
	tmp_nd=vr_stack_pop(stk);
	nd=tmp_nd->right;
	if((*hook)(tmp_nd->key,tmp_nd->val)==-1) break;
      } else{
	break;
      }
    }
  } while(1);
  vr_stack_des(stk,NULL);
}

void vr_bitree_post_order(vr_bitree_nd* root,vr_trav_func hook)
{
  vr_bitree_nd* nd=root;
  vr_bitree_nd* tmp_nd=NULL;
  vr_stack* stk=vr_stack_new();
  do{
    if(nd){
      vr_bitree_nd* l=nd->left;
      vr_bitree_nd* r=nd->right;
      if( (l==NULL&&r==NULL) || (l==tmp_nd&&r==NULL) || r==tmp_nd ){
	if((*hook)(nd->key,nd->val)==-1) break;
	tmp_nd=nd;
      }else{
	vr_stack_push(stk,nd);
	if(r)vr_stack_push(stk,r);
	nd=l;
	continue;
      }
    }
    if(vr_stack_size(stk))
      nd=vr_stack_pop(stk);
    else
      break;
  } while(1);
  vr_stack_des(stk,NULL);
}

void vr_bitree_get_tglt(vr_bitree_nd* root,void* key,vr_bitree_nd** gra_nd,vr_bitree_nd** par_nd,vr_bitree_nd** nd,vr_compare_func comp)
{
  vr_bitree_nd* _gra_nd=NULL;
  vr_bitree_nd* _par_nd=NULL;
  vr_bitree_nd* _nd=root;
  while(_nd!=NULL){
    int cmp=(* comp)(key,_nd->key);
    if(cmp==0){
      break;
    }else{
      _gra_nd=_par_nd;
      _par_nd=_nd;
      if(cmp>0)
	_nd=_nd->right;
      else
	_nd=_nd->left;
    }
  }
  if(gra_nd!=NULL) *gra_nd=_gra_nd;
  if(par_nd!=NULL) *par_nd=_par_nd;
  if(nd!=NULL) *nd=_nd;
}

vr_bitree_nd* vr_bitree_nd_new()
{
  vr_bitree_nd* nd=(vr_bitree_nd*) malloc(sizeof(vr_bitree_nd));
  if(nd)
    VR_BITREE_ND_INIT(nd);
  return nd;
}

void vr_bitree_nd_des(vr_bitree_nd* nd)
{
  free(nd);
}

void vr_bitree_nd_set(vr_bitree_nd* nd,void* key,void* val)
{
  if(key) nd->key=key;
  if(val) nd->val=val;
}

void vr_bitree_nd_get(vr_bitree_nd* nd,void** key,void** val)
{
  if(key) *key=nd->key;
  if(val) *val=nd->val;
}
