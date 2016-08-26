/**
 *link list
 */
#include "lscomn.h"
#include "lkls.h"

static vr_lkls_nd* vr_lkls_nd_new();
static void vr_lkls_nd_des(vr_lkls_nd* nd);
static void vr_lkls_nd_set(vr_lkls_nd* nd,void* val,int size);
static void vr_lkls_nd_get(vr_lkls_nd* nd,void* val,int* size);
static vr_lkls_nd* vr_lkls_get_nd(vr_lkls* ls,int pos);

static vr_lkls_nd* vr_lkls_get_nd(vr_lkls* ls,int pos)
{
  int ls_size=ls->size;
  if(pos==ls_size-1)
    return ls->foot;
  vr_lkls_nd* nd=ls->head;
  int i=0;
  while(i<ls_size){
    if(pos==i)
      return nd;
    nd=nd->next;
    i++;
  }
}

static vr_lkls_nd* vr_lkls_nd_new()
{
  vr_lkls_nd* nd=(vr_lkls_nd*) malloc(sizeof(vr_lkls_nd));
  if(nd!=NULL){
    nd->next=NULL;
    nd->val=NULL;
    nd->size=0;
  }
  return nd;
}

static void vr_lkls_nd_des(vr_lkls_nd* nd)
{
  if(nd->val!=NULL)
    free(nd->val);
  free(nd);
}

static void vr_lkls_nd_set(vr_lkls_nd* nd,void* val,int size)
{
  if(nd->size!=size){
    if(nd->val!=NULL)
      free(nd->val);
    nd->val=(vr_lkls_nd*)malloc(size);
    nd->size=size;
  }
  memcpy(nd->val,val,size);
}

static void vr_lkls_nd_get(vr_lkls_nd* nd,void* val,int* size)
{
  if(nd->val!=NULL)
    memcpy(val,nd->val,nd->size);
  if(size!=NULL)
    *size=nd->size;
}

vr_lkls* vr_lkls_new()
{
  vr_lkls* ls=(vr_lkls*)malloc(sizeof(vr_lkls));
  if (ls!=NULL){
    VR_LKLS_INIT(ls);
  }
  return ls;
}

void vr_lkls_des(vr_lkls* ls)
{
  vr_lkls_cln(ls);
  free(ls);
}

void vr_lkls_ins(vr_lkls* ls,void* val,int size,int pos)
{
  VR_IDX_CHK(ls->size+1,pos);
  vr_lkls_nd* new_nd=vr_lkls_nd_new();
  vr_lkls_nd_set(new_nd,val,size);
  vr_lkls_nd* nd=NULL;
  if(pos==0){
    nd=ls->head;
    ls->head=new_nd;
  } else {
    vr_lkls_nd* prv_nd=vr_lkls_get_nd(ls,pos-1);
    nd=prv_nd->next;
    prv_nd->next=new_nd;
  }
  if(nd!=NULL)
    new_nd->next=nd;
  else
    ls->foot=new_nd;
  ls->size++;
}

void vr_lkls_apd(vr_lkls* ls,void* val,int size)
{
  vr_lkls_ins(ls,val,size,ls->size);
}

void vr_lkls_upd(vr_lkls* ls,void* val,int size,int pos)
{
  VR_IDX_CHK(ls->size,pos);
  vr_lkls_nd* nd=vr_lkls_get_nd(ls,pos);
  vr_lkls_nd_set(nd,val,size);
}

void vr_lkls_get(vr_lkls* ls,void* val,int* size,int pos)
{
  VR_IDX_CHK(ls->size,pos);
  vr_lkls_nd* nd=vr_lkls_get_nd(ls,pos);
  vr_lkls_nd_get(nd,val,size);
}

void vr_lkls_del(vr_lkls* ls,int pos)
{
  VR_IDX_CHK(ls->size,pos);
  vr_lkls_nd* prv_nd=NULL;
  vr_lkls_nd* nd=NULL;
  if(pos==0){
    nd=ls->head;
    ls->head=nd->next;
  } else {
    prv_nd=vr_lkls_get_nd(ls,pos-1);
    nd=prv_nd->next;
    prv_nd->next=nd->next;
  }
  if(nd->next==NULL)
    ls->foot=prv_nd;
  vr_lkls_nd_des(nd);
  ls->size--;
}

void vr_lkls_cln(vr_lkls* ls)
{
  int ls_size=ls->size;
  int i=0;
  while(i<ls_size){
    vr_lkls_del(ls,0);
    i++;
  }
}

int vr_lkls_size(vr_lkls* ls)
{
  return ls->size;
}
