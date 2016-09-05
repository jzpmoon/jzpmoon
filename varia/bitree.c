/* binary tree */
#include "trcomn.h"
#include "bitree.h"
#include "lkstk.h"
#include "ptr.h"

typedef int (*vr_bitree_nd_hfn_t)(vr_bitree_nd* nd);
static vr_bitree_nd* vr_bitree_nd_new();
static int vr_bitree_nd_des(vr_bitree_nd* nd);
static void vr_bitree_nd_set(vr_bitree_nd* nd,vr_bitree_nd* p,void* key,void* val,int kysz,int vlsz);
static void vr_bitree_nd_get(vr_bitree_nd* nd,void* key,void* val,int* kysz,int* vlsz);
static void vr_bitree_get_nd(vr_bitree_nd* root,void* key,int kysz,vr_bitree_nd** prv_nd,vr_bitree_nd** nd,vr_compare_fn_t comp);
static void vr_bitree_middle_traverse(vr_bitree_nd* root,vr_bitree_nd_hfn_t hook);

static void vr_bitree_middle_traverse(vr_bitree_nd* root,vr_bitree_nd_hfn_t hook)
{
  vr_bitree_nd* nd=root;
  vr_bitree_nd* tmp_nd=NULL;
  vr_lkstk* stk=vr_lkstk_new();
  do{
    if(nd!=NULL){
      vr_lkstk_pull(stk,(void*)&nd,sizeof(void*));
      nd=nd->left;
    } else {
      if(vr_lkstk_size(stk)!=0){
	vr_lkstk_pop(stk,(void*)&tmp_nd,NULL);
	nd=tmp_nd->right;
	if((*hook)(tmp_nd)==-1) break;
      } else{
	break;
      }
    }
  } while(1);
  vr_lkstk_des(stk);
}

static void vr_bitree_get_nd(vr_bitree_nd* root,void* key,int kysz,vr_bitree_nd** prv_nd,vr_bitree_nd** nd,vr_compare_fn_t comp)
{
  vr_bitree_nd* tmp_prv_nd=NULL;
  vr_bitree_nd* tmp_nd=root;
  while(tmp_nd!=NULL){
    int cmp=(* comp)(key,tmp_nd->key,kysz,tmp_nd->kysz);
    if(cmp==0){
      break;
    }else{
      tmp_prv_nd=tmp_nd;
      if(cmp==1)
	tmp_nd=tmp_nd->right;
      else if(cmp==-1)
	tmp_nd=tmp_nd->left;
    }
  }
  if(prv_nd!=NULL)
    *prv_nd=tmp_prv_nd;
  if(nd!=NULL)
    *nd=tmp_nd;
}

static vr_bitree_nd* vr_bitree_nd_new()
{
  vr_bitree_nd* nd=(vr_bitree_nd*) malloc(sizeof(vr_bitree_nd));
  if(nd!=NULL)
    VR_BITREE_ND_INIT(nd);
  return nd;
}

static int vr_bitree_nd_des(vr_bitree_nd* nd)
{
  void* nd_key=nd->key;
  void* nd_val=nd->val;
  if(nd_key!=NULL){
    free(nd_key);
  }
  if(nd_val!=NULL){
    free(nd_val);
  }
  free(nd);
  return 0;
}

static void vr_bitree_nd_set(vr_bitree_nd* nd,vr_bitree_nd* p,void* key,void* val,int kysz,int vlsz)
{
  void** nd_key=&nd->key;
  void** nd_val=&nd->val;
  int* nd_kysz=&nd->kysz;
  int* nd_vlsz=&nd->vlsz;
  if(p!=NULL)
    nd->p=p;
  if(key!=NULL)
    vr_nd_ptr_set(nd_key,key,nd_kysz,kysz);
  if(val!=NULL)
    vr_nd_ptr_set(nd_val,val,nd_vlsz,vlsz);
}

static void vr_bitree_nd_get(vr_bitree_nd* nd,void* key,void* val,int* kysz,int* vlsz)
{
  void* nd_key=nd->key;
  void* nd_val=nd->val;
  int nd_kysz=nd->kysz;
  int nd_vlsz=nd->vlsz;
  if(key!=NULL)
    memcpy(key,nd_key,nd_kysz);
  if(val!=NULL)
    memcpy(val,nd_val,nd_vlsz);
  if(kysz!=NULL)
    *kysz=nd_vlsz;
  if(vlsz!=NULL)
    *vlsz=nd_vlsz;
}

vr_bitree* vr_bitree_new(vr_compare_fn_t comp)
{
  vr_bitree* tree=malloc(sizeof(vr_bitree));
  if(tree!=NULL){
    tree->root=NULL;
    tree->size=0;
    tree->comp=comp;
  }
  return tree;
}

void vr_bitree_des(vr_bitree* tree)
{
  vr_bitree_cln(tree);
  free(tree);
}

void vr_bitree_ins(vr_bitree* tree,void* key,void* val,int kysz,int vlsz)
{
  if(val==NULL||vlsz==0){
    vr_bitree_del(tree,key,kysz);
    return;
  }
  vr_bitree_nd* prv_nd=NULL;
  vr_bitree_nd* nd=NULL;
  vr_bitree_nd* new_nd=NULL;
  vr_bitree_get_nd(tree->root,key,kysz,&prv_nd,&nd,tree->comp);
  if(nd==NULL){
    new_nd=vr_bitree_nd_new();
    vr_bitree_nd_set(new_nd,prv_nd,key,val,kysz,vlsz);
    if(prv_nd==NULL)
      tree->root=new_nd;
    else{
      int cmp=(* tree->comp)(key,prv_nd->key,kysz,prv_nd->kysz);
      if(cmp==1)
	prv_nd->right=new_nd;
      else
	prv_nd->left=new_nd;
    }
    tree->size++;
  }else{
    vr_bitree_nd_set(nd,NULL,NULL,val,0,vlsz);
  }
}

int vr_bitree_get(vr_bitree* tree,void* key,void* val,int kysz,int* vlsz)
{
  vr_bitree_nd* nd=tree->root;
  vr_compare_fn_t comp=tree->comp;
  while(nd!=NULL){
    int cmp=(*comp)(key,nd->key,kysz,nd->kysz);
    if(cmp==0){
      vr_bitree_nd_get(nd,NULL,val,0,vlsz);
      return 0;
    }else if(cmp==1)
      nd=nd->right;
    else
      nd=nd->left;
  }
  return -1;
}
void vr_bitree_trav(vr_bitree* tree,vr_bitree_nd_fn_t hook)
{
  
}

void vr_bitree_del(vr_bitree* tree,void* key,int kysz)
{
  vr_bitree_nd* prv_nd=NULL;
  vr_bitree_nd* nd=NULL;
  vr_bitree_nd* del_nd=NULL;
  vr_bitree_nd* mv_nd=NULL;
  vr_bitree_get_nd(tree->root,key,kysz,&prv_nd,&nd,tree->comp);
  if(nd==NULL) return;
  if(nd->left==NULL||nd->right==NULL)
    del_nd=nd;
  else
    vr_bitree_get_nd(nd,key,kysz,&del_nd,NULL,tree->comp);
  if(del_nd->left!=NULL)
    mv_nd=del_nd->left;
  else
    mv_nd=del_nd->right;
  if(del_nd->p==NULL)
    tree->root=mv_nd;
  else
    if(del_nd->p->left==del_nd)
      del_nd->p->left=mv_nd;
    else
      del_nd->p->right=mv_nd;
  if(mv_nd!=NULL) mv_nd->p=del_nd->p;
  if(del_nd!=nd){
    void* key=NULL;
    void* val=NULL;
    int kysz=0,vlsz=0;
    vr_bitree_nd_get(del_nd,key,val,&kysz,&vlsz);
    vr_bitree_nd_set(nd,NULL,key,val,kysz,vlsz);
  }
  vr_bitree_nd_des(del_nd);
  tree->size--;
}

void vr_bitree_cln(vr_bitree* tree)
{
  vr_bitree_middle_traverse(tree->root,vr_bitree_nd_des);
}

int vr_bitree_size(vr_bitree* tree)
{
  return tree->size;
}
