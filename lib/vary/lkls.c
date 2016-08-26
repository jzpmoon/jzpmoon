/**
 *link list
 */
#include "lscomn.h"
#include "lkls.h"

vr_lkls_nd* vr_lkls_nd_init();
int vr_lkls_nd_des(vr_lkls_nd* nd);
int vr_lkls_nd_set(vr_lkls_nd* nd,void* val,int size);
int vr_lkls_nd_get(vr_lkls_nd* nd,void* val,int* size);

vr_lkls_nd* vr_lkls_nd_init()
{
  vr_lkls_nd* nd=(vr_lkls_nd*) malloc(sizeof(vr_lkls_nd));
  if(nd!=NULL){
    nd->next=NULL;
    nd->val=NULL;
    nd->size=0;
  }
  return nd;
}

int vr_lkls_nd_des(vr_lkls_nd* nd)
{
  if(nd->val!=NULL)
    free(nd->val);
  free(nd);
  return 0;
}

int vr_lkls_nd_set(vr_lkls_nd* nd,void* val,int size)
{
  if(nd->size!=size){
    if(nd->val!=NULL)
      free(nd->val);
    nd->val=(vr_lkls_nd*)malloc(size);
    nd->size=size;
  }
  memcpy(nd->val,val,size);
  return 0;
}

int vr_lkls_nd_get(vr_lkls_nd* nd,void* val,int* size)
{
  if(nd->val!=NULL)
    memcpy(val,nd->val,nd->size);
  *size=nd->size;
  return 0;
}

vr_lkls* vr_lkls_init()
{
  vr_lkls* ls=(vr_lkls*)malloc(sizeof(vr_lkls));
  if (ls!=NULL){
    ls->head=NULL;
    ls->foot=NULL;
    ls->size=0;
  }
  return ls;
}

int vr_lkls_des(vr_lkls* ls)
{
  vr_lkls_nd* nd=ls->head;
  vr_lkls_nd* tmp_nd=NULL;
  int ls_size=ls->size;
  int i=0;
  while(i<ls_size){
    if(nd==NULL){
      free(ls);
      return i;
    }
    tmp_nd=nd;
    nd=nd->next;
    vr_lkls_nd_des(tmp_nd);
  }
}

int vr_lkls_ins(vr_lkls* ls,void* val,int size,int pos)
{
  int ls_size=ls->size;
  VR_IDX_CHK(ls_size+1,pos);
  if(pos!=0&&pos==ls_size){
    ls->foot->next=vr_lkls_nd_init();
    vr_lkls_nd_set(ls->foot->next,val,size);
    ls->foot=ls->foot->next;
    ls->size++;
    return pos;
  }
  vr_lkls_nd*  prv_nd=NULL;
  vr_lkls_nd* nd=ls->head;
  int i=0;
  while(i<=ls_size){
    if(pos==i){
      vr_lkls_nd* tmp_nd=NULL;
      tmp_nd=vr_lkls_nd_init();
      vr_lkls_nd_set(tmp_nd,val,size);
      tmp_nd->next=nd;
      if(prv_nd==NULL)
	ls->head=tmp_nd;
      else
	prv_nd->next=tmp_nd;
      if(nd==NULL)
	ls->foot=tmp_nd;
      ls->size++;
      return i;
    }
    prv_nd=nd;
    nd=nd->next;
    i++;
  }
}

int vr_lkls_upd(vr_lkls* ls,void* val,int size,int pos)
{
  int ls_size=ls->size;
  VR_IDX_CHK(ls_size,pos);
  vr_lkls_nd* nd=ls->head;
  if(pos==ls_size-1){
    vr_lkls_nd_set(ls->foot,val,size);
    return pos;
  }
  int i=0;
  while(i<ls_size){
    if(pos==i){
      vr_lkls_nd_set(nd,val,size);
      return i;
    }
    nd=nd->next;
    i++;
  }
}

int vr_lkls_get(vr_lkls* ls,void* val,int* size,int pos)
{
  int ls_size=ls->size;
  VR_IDX_CHK(ls_size,pos);
  vr_lkls_nd* nd=ls->head;
  if(pos==ls_size-1){
    vr_lkls_nd_get(ls->foot,val,size);
    return pos;
  }
  int i=0;
  while(i<ls_size){
    if(pos==i){
    vr_lkls_nd_get(nd,val,size);
    return i;
    }
    nd=nd->next;
    i++;
  }
}

int vr_lkls_del(vr_lkls* ls,int pos)
{
  int ls_size=ls->size;
  VR_IDX_CHK(ls_size,pos);
  vr_lkls_nd* prv_nd=NULL;
  vr_lkls_nd* nd=ls->head;
  int i=0;
  while(i<ls_size){
    if(pos==i){
      if(prv_nd==NULL){
	ls->head=nd->next;
      } else {
	prv_nd->next=nd->next;
      }
      if(nd->next==NULL)
	ls->foot=prv_nd;
      vr_lkls_nd_des(nd);
      ls->size--;
      return i;
    }
    prv_nd=nd;
    nd=nd->next;
    i++;
  }
}

int vr_lkls_size(vr_lkls* ls)
{
  return ls->size;
}
