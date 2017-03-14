/* red balck tree */
#include "include/vr_rbtree.h"
#include "include/vr_stack.h"

#define vr_rbt_nd_color(nd) ((nd) ? (nd)->color : VR_BLACK)

static vr_rbt_nd* vr_rbt_nd_new();
static void vr_rbt_nd_set(vr_rbt_nd* nd,void* key,void* val);
static void vr_rbt_nd_des(vr_rbt_nd* nd,vr_kv_des_func des);
static void vr_rbt_nd_tglt(vr_rbt_nd* root,
		     void* key,
		     vr_rbt_nd** gra_nd,
		     vr_rbt_nd** par_nd,
		     vr_rbt_nd** nd,
		     vr_compare_func cmp);
static void vr_rbt_rotate_left(vr_rbtree* tree,vr_rbt_nd* x);
static void vr_rbt_rotate_right(vr_rbtree* tree,vr_rbt_nd* x);
static void vr_rbt_pre_order(vr_rbt_nd* root,vr_trav_func hook);
static void vr_rbt_in_order(vr_rbt_nd* root,vr_trav_func hook);
static void vr_rbt_post_order(vr_rbt_nd* root,vr_trav_func hook);
static vr_rbt_nd* vr_rbt_nd_pre(vr_rbt_nd* nd);
static vr_rbt_nd* vr_rbt_nd_next(vr_rbt_nd* nd);
static vr_rbt_nd* vr_rbt_first(vr_rbt_nd* nd);

vr_rbtree* vr_rbtree_new(vr_compare_func cmp){
  vr_rbtree* tree=(vr_rbtree*)malloc(sizeof(vr_rbtree));
  if(tree){
    vr_rbtree_init(tree,cmp);
  }
  return tree;
}

void vr_rbtree_des(vr_rbtree* tree,vr_kv_des_func des)
{
  vr_rbtree_cln(tree,des);
  free(tree);
}

int vr_rbtree_ins(vr_rbtree* tree,void* key,void* val)
{
  vr_rbt_nd* gra_nd=NULL;
  vr_rbt_nd* par_nd=NULL;
  vr_rbt_nd* nd=NULL;
  if(key==NULL||val==NULL)
    return -1;
  vr_rbt_nd_tglt(tree->root,key,&gra_nd,&par_nd,&nd,tree->cmp);
  if(nd)
    return -1;
  else{
    nd=vr_rbt_nd_new();
    vr_rbt_nd_set(nd,key,val);
    if(par_nd==NULL)
      tree->root=nd;
    else{
      int cmp_res=(* tree->cmp)(key,par_nd->key);
      nd->parent=par_nd;
      if(cmp_res>0)
	par_nd->right=nd;
      else
	par_nd->left=nd;
    }
    while(1){
      if(!par_nd){
	nd->color=VR_BLACK;
	break;
      }
      if(vr_rbt_nd_color(par_nd)==VR_BLACK) break;
      if(vr_rbt_nd_color(gra_nd->left)==VR_RED&&vr_rbt_nd_color(gra_nd->right)==VR_RED){
	gra_nd->color=VR_RED;
	gra_nd->left->color=VR_BLACK;
	gra_nd->right->color=VR_BLACK;
	nd=gra_nd;
	par_nd=nd->parent;
	if(par_nd) gra_nd=par_nd->parent;
	continue;
      }
      gra_nd->color=VR_RED;
      if(vr_rbt_nd_color(gra_nd->right)==VR_BLACK){
	if(par_nd->right==nd)
	  vr_rbt_rotate_left(tree,par_nd);
	gra_nd->left->color=VR_BLACK;
	vr_rbt_rotate_right(tree,gra_nd);
      }else{
	if(par_nd->left==nd)
	  vr_rbt_rotate_right(tree,par_nd);
	gra_nd->right->color=VR_BLACK;
	vr_rbt_rotate_left(tree,gra_nd);
      }
      break;
    }
    tree->size++;
  }
  return tree->size;
}

void* vr_rbtree_get(vr_rbtree* tree,void* key)
{
  vr_rbt_nd* nd=NULL;
  vr_rbt_nd_tglt(tree->root,key,NULL,NULL,&nd,tree->cmp);
  if(nd)
    return nd->val;
  return NULL;
}

void vr_rbtree_del(vr_rbtree* tree,void* key,vr_kv_des_func des)
{
  vr_rbt_nd* par_nd=NULL;
  vr_rbt_nd* nd=NULL;
  vr_rbt_nd* del_nd=NULL;
  vr_rbt_nd* fix_nd=NULL;
  vr_rbt_nd* w_nd=NULL;
  int color_del_nd=0;
  vr_rbt_nd_tglt(tree->root,key,NULL,&par_nd,&nd,tree->cmp);
  if(!nd) return;
  if(nd->left==NULL||nd->right==NULL)
    del_nd=nd;
  else{
    vr_rbt_nd_tglt(nd->right,key,&par_nd,&del_nd,NULL,tree->cmp);
    if(!par_nd)
      par_nd=nd;
  }
  if(del_nd->left)
    fix_nd=del_nd->left;
  else
    fix_nd=del_nd->right;
  if(par_nd==NULL)
    tree->root=fix_nd;
  else if(par_nd->left==del_nd)
    par_nd->left=fix_nd;
  else
    par_nd->right=fix_nd;
  if(fix_nd)
    fix_nd->parent=par_nd;
  if(nd!=del_nd){
    nd->key=del_nd->key;
    nd->val=del_nd->val;
  }
  color_del_nd=vr_rbt_nd_color(del_nd);
  vr_rbt_nd_des(del_nd,des);
  tree->size--;
  if(color_del_nd==VR_RED)
    return;
  while(1){
    if(vr_rbt_nd_color(fix_nd)==VR_RED){
      fix_nd->color=VR_BLACK;
      break;
    }
    if(!par_nd)
      break;
    if(par_nd->left==fix_nd){
      w_nd=par_nd->right;
      if(!w_nd){
	fix_nd=par_nd;
	par_nd=par_nd->parent;
	continue;
      }
      if(vr_rbt_nd_color(w_nd)==VR_RED){
	par_nd->color=VR_RED;
	w_nd->color=VR_BLACK;
	vr_rbt_rotate_left(tree,par_nd);
	continue;
      }
      if(vr_rbt_nd_color(w_nd->left)==VR_BLACK&&vr_rbt_nd_color(w_nd->right)==VR_BLACK){
	w_nd->color=VR_RED;
	if(vr_rbt_nd_color(par_nd)==VR_RED){
	  par_nd->color=VR_BLACK;
	  break;
	}
	fix_nd=par_nd;
	par_nd=par_nd->parent;
	continue;
      }
      if(vr_rbt_nd_color(w_nd->left)==VR_RED){
	w_nd->color=VR_RED;
	w_nd->left->color=VR_BLACK;
	vr_rbt_rotate_right(tree,w_nd);
	w_nd=par_nd->right;
	continue;
      }
      w_nd->color=par_nd->color;
      par_nd->color=VR_BLACK;
      w_nd->right->color=VR_BLACK;
      vr_rbt_rotate_left(tree,par_nd);
      break;
    }else{
      w_nd=par_nd->left;
      if(!w_nd){
	fix_nd=par_nd;
	par_nd=par_nd->parent;
	continue;
      }
      if(vr_rbt_nd_color(w_nd)==VR_RED){
	par_nd->color=VR_RED;
	w_nd->color=VR_BLACK;
	vr_rbt_rotate_right(tree,par_nd);
      }
      if(vr_rbt_nd_color(w_nd->left)==VR_BLACK&&vr_rbt_nd_color(w_nd->right)==VR_BLACK){
	w_nd->color=VR_RED;
	if(vr_rbt_nd_color(par_nd)==VR_RED){
	  par_nd->color=VR_BLACK;
	  break;
	}
	fix_nd=par_nd;
	par_nd=par_nd->parent;
	continue;
      }
      if(vr_rbt_nd_color(w_nd->right)==VR_RED){
	w_nd->color=VR_RED;
	w_nd->right->color=VR_BLACK;
	vr_rbt_rotate_left(tree,w_nd);
	w_nd=par_nd->left;
	continue;
      }
      w_nd->color=par_nd->color;
      par_nd->color=VR_BLACK;
      w_nd->left->color=VR_BLACK;
      vr_rbt_rotate_right(tree,par_nd);
      break;
    }
  }
}

void vr_rbtree_trav(vr_rbtree* tree,vr_trav_func hook,int type)
{
  switch(type){
  case VR_TREE_PRE_ORDER_TRAV:vr_rbt_pre_order(tree->root,hook);break;
  case VR_TREE_IN_ORDER_TRAV:vr_rbt_in_order(tree->root,hook);break;
  case VR_TREE_POST_ORDER_TRAV:vr_rbt_post_order(tree->root,hook);break;
  }
}

void vr_rbtree_cln(vr_rbtree* tree,vr_kv_des_func des)
{
  vr_rbt_nd* nd=vr_rbt_first(tree->root);
  vr_rbt_nd* next=NULL;
  while(nd){
    next=vr_rbt_nd_next(nd);
    vr_rbt_nd_des(nd,des);
    nd=next;
  }
}

static void vr_rbt_rotate_left(vr_rbtree* tree,vr_rbt_nd* x)
{
  vr_rbt_nd* y=x->right;
  x->right=y->left;
  y->left=x;
  if(x->parent==NULL)
    tree->root=y;
  else if(x->parent->left==x)
    x->parent->left=y;
  else
    x->parent->right=y;
  y->parent=x->parent;
  x->parent=y;
  if(x->right)
    x->right->parent=x;
}

static void vr_rbt_rotate_right(vr_rbtree* tree,vr_rbt_nd* x)
{
  vr_rbt_nd* y=x->left;
  x->left=y->right;
  y->right=x;
  if(x->parent==NULL)
    tree->root=y;
  else if(x->parent->left==x)
    x->parent->left=y;
  else
    x->parent->right=y;
  y->parent=x->parent;
  x->parent=y;
  if(x->left)
    x->left->parent=x;
}

static void vr_rbt_nd_tglt(vr_rbt_nd* root,void* key,vr_rbt_nd** gra_nd,vr_rbt_nd** par_nd,vr_rbt_nd** nd,vr_compare_func cmp)
{
  vr_rbt_nd* _gra_nd=NULL;
  vr_rbt_nd* _par_nd=NULL;
  vr_rbt_nd* _nd=root;
  while(_nd){
    int cmp_res=(* cmp)(key,_nd->key);
    if(cmp_res==0){
      break;
    }else{
      _gra_nd=_par_nd;
      _par_nd=_nd;
      if(cmp_res>0)
	_nd=_nd->right;
      else
	_nd=_nd->left;
    }
  }
  if(gra_nd!=NULL) *gra_nd=_gra_nd;
  if(par_nd!=NULL) *par_nd=_par_nd;
  if(nd!=NULL) *nd=_nd;
}

static vr_rbt_nd* vr_rbt_nd_new()
{
  vr_rbt_nd* nd=(vr_rbt_nd*)malloc(sizeof(vr_rbt_nd));
  if(nd){
    nd->key=NULL;
    nd->val=NULL;
    nd->left=NULL;
    nd->right=NULL;
    nd->parent=NULL;
    nd->color=VR_RED;
  }
  return nd;
}

static void vr_rbt_nd_des(vr_rbt_nd* nd,vr_kv_des_func des)
{
  if(des)
    des(nd->key,nd->val);
  free(nd);
}

static void vr_rbt_nd_set(vr_rbt_nd* nd,void* key,void* val)
{
  if(key) nd->key=key;
  if(val) nd->val=val;
}


static void vr_rbt_pre_order(vr_rbt_nd* root,vr_trav_func hook)
{
  vr_rbt_nd* nd=root;
  vr_rbt_nd* tmp_nd=NULL;
  vr_stack* stk=vr_stack_new();
  do{
    if(nd){
      if(nd->right) vr_stack_push(stk,nd->right);
      tmp_nd=nd;nd=nd->left;
      if((*hook)(tmp_nd->key,tmp_nd->val)==-1) break;
    }else{
      if(vr_stack_size(stk))
	nd=vr_stack_pop(stk,NULL);
      else
	break;
    }
  } while(1);
  vr_stack_des(stk,NULL);
}

static void vr_rbt_in_order(vr_rbt_nd* root,vr_trav_func hook)
{
  vr_rbt_nd* nd=root;
  vr_rbt_nd* tmp_nd=NULL;
  vr_stack* stk=vr_stack_new();
  do{
    if(nd){
      vr_stack_push(stk,(void*)nd);
      nd=nd->left;
    } else {
      if(vr_stack_size(stk)){
	tmp_nd=vr_stack_pop(stk,NULL);
	nd=tmp_nd->right;
	if((*hook)(tmp_nd->key,tmp_nd->val)==-1) break;
      } else{
	break;
      }
    }
  } while(1);
  vr_stack_des(stk,NULL);
}

static void vr_rbt_post_order(vr_rbt_nd* root,vr_trav_func hook)
{
  vr_rbt_nd* nd=root;
  vr_rbt_nd* tmp_nd=NULL;
  vr_stack* stk=vr_stack_new();
  do{
    if(nd){
      vr_rbt_nd* l=nd->left;
      vr_rbt_nd* r=nd->right;
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
      nd=vr_stack_pop(stk,NULL);
    else
      break;
  } while(1);
  vr_stack_des(stk,NULL);
}

static vr_rbt_nd* vr_rbt_nd_pre(vr_rbt_nd* nd)
{
  vr_rbt_nd* _nd=nd;
  if(_nd->left){
    _nd=_nd->left;
    while(_nd->right)
      _nd=_nd->right;
  }else{
    while(_nd->parent&&_nd->parent->right!=_nd)
      _nd=_nd->parent;
    _nd=_nd->parent;
  }
  return _nd;
}

static vr_rbt_nd* vr_rbt_nd_next(vr_rbt_nd* nd)
{
  vr_rbt_nd* _nd=nd;
  if(_nd->right){
    _nd=_nd->right;
    while(_nd->left)
      _nd=_nd->left;
  }else{
    while(_nd->parent&&_nd->parent->left!=_nd)
      _nd=_nd->parent;
    _nd=_nd->parent;
  }
  return _nd;
}

static int vr_compare_alway_min(void* max,void* min){return -1;};
static vr_rbt_nd* vr_rbt_first(vr_rbt_nd* nd)
{
  vr_rbt_nd* first=NULL;
  vr_rbt_nd_tglt(nd,NULL,NULL,&first,NULL,vr_compare_alway_min);
  return first;
}
