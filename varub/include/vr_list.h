#ifndef VR_LIST_H
#define VR_LIST_H

#include "vr_common.h"
#include "vr_type.h"

typedef struct vr_list_node vr_list_node,* vr_index;
typedef struct vr_list vr_list;

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
  int length;
};

VR_DECLARE_EXPORT
vr_list* vr_list_new();
VR_DECLARE_EXPORT
int vr_list_init(vr_list* list);
VR_DECLARE_EXPORT
int vr_list_insert(vr_list* list,void* data,int position);
VR_DECLARE_EXPORT
int vr_list_append(vr_list* list,void* data);
VR_DECLARE_EXPORT
void vr_list_sort(vr_list* list,vr_compare_func cmp);
VR_DECLARE_EXPORT
vr_index vr_list_head(vr_list* list);
VR_DECLARE_EXPORT
vr_index vr_list_foot(vr_list* list);
VR_DECLARE_EXPORT
vr_index vr_list_next(vr_list* list,vr_index index);
VR_DECLARE_EXPORT
vr_index vr_list_prev(vr_list* list,vr_index index);
VR_DECLARE_EXPORT 
void* vr_list_index(vr_index index);
VR_DECLARE_EXPORT 
vr_index vr_list_del(vr_list* list,vr_index index,vr_val_des_func des);
VR_DECLARE_EXPORT
void vr_list_cln(vr_list* list,vr_val_des_func des);
VR_DECLARE_EXPORT 
void vr_list_des(vr_list* list,vr_val_des_func des);

#endif
