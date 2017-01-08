#ifndef VR_LIST_H
#define VR_LIST_H

#include "vr_type.h"

typedef struct vr_list_node vr_list_node,* vr_index;
typedef struct vr_list vr_list,vr_closure;

struct vr_list_node
{
  void* data;
  struct vr_list_node* prev;
  struct vr_list_node* next;
};
struct vr_list
{
  vr_list_node* head;
  vr_list_node* foot;
  vr_closure* cmpr;
  vr_closure* desr;
  int length;
};

vr_list* vr_list_new();
int vr_list_init(vr_list* list);
void vr_list_cmpr(vr_list* list,vr_closure_func* func);
void vr_list_desr(vr_list* list,vr_closure_func* func);
int vr_list_insert(vr_list* list,void* data,int position);
int vr_list_append(vr_list* list,void* data);
vr_index vr_list_head(vr_list* list);
vr_index vr_list_next(vr_list* list,vr_index index);
vr_index vr_list_prev(vr_list* list,vr_index index);
void* vr_list_index(vr_index index);
int vr_list_del(vr_list* list,vr_index index);
void vr_list_cln(vr_list* list);
void vr_list_des(vr_list* list);

vr_list* vr_closure_new();
int vr_closure_init(vr_closure* closure);
void vr_closure_exec(vr_closure* closure,void* params,void* retval);

#endif
