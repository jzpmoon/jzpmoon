/**
 *sigle link list
 */
#include "include/vr_error.h"
#include "include/vr_slist.h"

static vr_slist_nd* vr_slist_nd_new();
static void vr_slist_nd_des(vr_slist_nd* nd,vr_val_des_func des);
static void vr_slist_nd_set(vr_slist_nd* nd,void* val);
static void* vr_slist_nd_get(vr_slist_nd* nd);
static vr_slist_nd* vr_slist_get_nd(vr_slist* ls,int pos);

static vr_slist_nd* vr_slist_get_nd(vr_slist* ls,int pos)
{
  vr_slist_nd* nd=NULL;
  int ls_size=ls->size;
  int i=0;
  if(pos==ls_size-1)
    return ls->foot;
  nd=ls->head;
  while(i<pos){
    nd=nd->next;
    i++;
  }
  return nd;
}

static vr_slist_nd* vr_slist_nd_new()
{
  vr_slist_nd* nd=(vr_slist_nd*) malloc(sizeof(vr_slist_nd));
  if(nd!=NULL){
    nd->next=NULL;
    nd->val=NULL;
  }
  return nd;
}

static void vr_slist_nd_des(vr_slist_nd* nd,vr_val_des_func des)
{
  if(des)
    (*des)(nd->val);
  free(nd);
}

static void vr_slist_nd_set(vr_slist_nd* nd,void* val)
{
  nd->val=val;
}

static void* vr_slist_nd_get(vr_slist_nd* nd)
{
  return nd->val;
}

vr_slist* vr_slist_new()
{
  vr_slist* ls=(vr_slist*)malloc(sizeof(vr_slist));
  if (ls!=NULL){
    vr_slist_init(ls);
  }
  return ls;
}

void vr_slist_des(vr_slist* ls,vr_val_des_func des)
{
  vr_slist_cln(ls,des);
  free(ls);
}

void vr_slist_ins(vr_slist* ls,void* val,int pos)
{
  vr_slist_nd* nd=NULL;
  vr_slist_nd* new_nd=NULL;
  VR_IDX_CHK(ls->size+1,pos);
  new_nd=vr_slist_nd_new();
  vr_slist_nd_set(new_nd,val);
  if(pos==0){
    nd=ls->head;
    ls->head=new_nd;
  } else {
    vr_slist_nd* prv_nd=vr_slist_get_nd(ls,pos-1);
    nd=prv_nd->next;
    prv_nd->next=new_nd;
  }
  if(nd!=NULL)
    new_nd->next=nd;
  else
    ls->foot=new_nd;
  ls->size++;
}

void vr_slist_apd(vr_slist* ls,void* val)
{
  vr_slist_ins(ls,val,ls->size);
}

void vr_slist_upd(vr_slist* ls,void* val,int pos)
{
  vr_slist_nd* nd=NULL;
  VR_IDX_CHK(ls->size,pos);
  nd=vr_slist_get_nd(ls,pos);
  vr_slist_nd_set(nd,val);
}

void* vr_slist_get(vr_slist* ls,int pos)
{
  vr_slist_nd* nd=NULL;
  VR_IDX_CHK(ls->size,pos);
  nd=vr_slist_get_nd(ls,pos);
  return vr_slist_nd_get(nd);
}

void vr_slist_del(vr_slist* ls,int pos,vr_val_des_func des)
{
  vr_slist_nd* prv_nd=NULL;
  vr_slist_nd* nd=NULL;
  VR_IDX_CHK(ls->size,pos);
  if(pos==0){
    nd=ls->head;
    ls->head=nd->next;
  } else {
    prv_nd=vr_slist_get_nd(ls,pos-1);
    nd=prv_nd->next;
    prv_nd->next=nd->next;
  }
  if(nd->next==NULL)
    ls->foot=prv_nd;
  vr_slist_nd_des(nd,des);
  ls->size--;
}

void vr_slist_cln(vr_slist* ls,vr_val_des_func des)
{
  int ls_size=ls->size;
  int i=0;
  while(i<ls_size){
    vr_slist_del(ls,0,des);
    i++;
  }
}

int vr_slist_size(vr_slist* ls)
{
  return ls->size;
}
