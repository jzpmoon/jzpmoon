/* binary tree */
#include "trcomn.h"
#include "bitree.h"
#include "lkstk.h"

static vr_bitree_nd* vr_bitree_nd_new();
static void vr_bitree_nd_des(vr_bitree_nd* nd);
static void vr_bitree_nd_set(vr_bitree_nd* nd,void* key,void* val,int kysz,int vlsz);
static void vr_bitree_nd_val_set(vr_bitree_nd* nd,void* val,int vlsz);
static void vr_bitree_nd_get(vr_bitree_nd* nd,void* val,int vlsz);
static vr_bitree_nd* vr_bitree_get_mnt(vr_bitree_nd* root,void* key, int kysz,compare comp,vr_brtree_nd* mnt);

static vr_bitree_nd* vr_bitree_get_mnt(vr_bitree_nd* root,void* key,int kysz,compare comp,vr_brtree_nd* mnt)
{
  vr_bitree_nd* prv_nd=NULL;
  vr_bitree_nd* nd=root;
  while(nd!=NULL){
    int cmp_res=(*comp)(nd->key,key,nd->kysz,kysz);
    if(cmp_res==0){
      break;
    }else{
      prv_nd=nd;
      if(cmp_res==1){
	nd=nd->left;
      } else if(cmp_res==-1){
	nd=nd->right;
      }
    }
  }
  mnt=prv_nd;
}

static vr_bitree_nd* vr_bitree_nd_new()
{
  vr_bitree_nd* nd=(vr_bitree_nd*) malloc(sizeof(vr_bitree_nd));
  if(nd!=NULL)
    VR_BITREE_ND_INIT(nd);
  return nd;
}

static void vr_bitree_nd_des(vr_bitree_nd* nd)
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
}

static void vr_bitree_nd_set(vr_bitree_nd* nd,void* key,void* val,int kysz,int vlsz)
{
  void* nd_key=nd->key;
  void* nd_val=nd->val;
  int* nd_kysz=&nd->kysz;
  int* nd_vlsz=&nd->vlsz;
  vr_nd_ptr_set(nd_key,key,nd_kysz,kysz);
  vr_nd_ptr_set(nd_val,val,nd_vlsz,vlsz);
}

static void vr_bitree_nd_val_set(vr_bitree_nd* nd,void* val,int vlsz)
{
  void* nd_val=nd->val;
  int* nd_vlsz=nd->vlsz;
  vr_nd_ptr_set(nd_val,val,nd_vlsz,vlsz);
}

static void vr_bitree_nd_get(vr_bitree_nd* nd,void* val,int* vlsz)
{
  void* nd_val=nd->val;
  int nd_vlsz=nd->vlsz;
  if(nd_val!=NULL)
    memcpy(val,nd_val,nd_vlsz);
  if(vlsz!=NULL)
    *vlsz=nd_vlsz;
}

vr_bitree* vr_bitree_new(compare comp)
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
  vr_bitree_nd* nd=tree->root;
  vr_bitree_nd* tmp_nd=NULL;
  vr_lkstk* stk=vr_lkstk_new();
  do{
    if(nd!=NULL){
      vr_lkstk_pull(stk,(void*)&nd,sizeof(void*));
      nd=nd->left;
    } else {
      if(vr_lkstk_size(stk)!=0){
	vr_lkstk_pop(stk,(void*)tmp_nd,NULL);
	nd=tmp->right;
	vr_bitree_nd_des(tmp_nd);
      } else{
	free(tree);
	return;
      }
    }
  } while(1);
}

void vr_bitree_ins(vr_bitree* tree,void* key,void* val,int kysz,int vlsz)
{

}

void vr_bitree_get(vr_bitree* tree,void* key,void* val,int kysz,int* vlsz)
{
  
}

void vr_bitree_del(vr_bitree* tree,void* key,int kysz)
{
  
}
