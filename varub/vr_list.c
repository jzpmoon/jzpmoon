#include "include/vr_list.h"

static vr_list_node* vr_list_node_new(void* data);
static void vr_list_node_des(vr_list_node* node,
			     vr_val_des_func des);

vr_list* vr_list_new()
{
  vr_list* list=malloc(sizeof(vr_list));
  vr_list_init(list);
  return list;
}

int vr_list_init(vr_list* list)
{
  if(!list) return -1;
  list->head=NULL;
  list->foot=NULL;
  list->length=0;
  return 0;
}

int vr_list_insert(vr_list* list,void* data,int position)
{
  int i=0;
  vr_index index=NULL;
  vr_list_node* node=NULL;
  if(list->length<position||position<0) return -1;
  index=list->head;
  while(i<position)
    {
      index=index->next;
      i++;
    }
  node=vr_list_node_new(data);
  if(index)
    {
      node->prev=index->prev;
      node->next=index;
      index->prev=node;
      node->prev->next=node;
      if(i==0)
	list->head=node;
      else
	if(list->head==index)
	  list->foot=node;
    }
  else
    {
      node->prev=node;
      node->next=node;
      list->head=node;
      list->foot=node;
    }
  return ++list->length;
}

int vr_list_append(vr_list* list,void* data)
{
  vr_list_node* node=vr_list_node_new(data);
  vr_list_node* foot=list->foot;
  if(foot==NULL){
    list->head=node;
    list->foot=node;
    node->prev=node;
    node->next=node;
  }else{
    node->prev=foot;
    node->next=list->head;
    list->head->prev=node;
    foot->next=node;
    list->foot=node;
  }
  return ++list->length;
}

vr_index vr_list_head(vr_list* list)
{
  return list->head;
}

vr_index vr_list_next(vr_list* list,vr_index index)
{
  if(list->foot!=index)
    return index->next;
  else
    return NULL;
}

vr_index vr_list_prev(vr_list* list,vr_index index)
{
  if(list->head!=index)
    return index->prev;
  else
    return NULL;
}

void* vr_list_index(vr_index index)
{
  return index->data;
}

vr_index vr_list_del(vr_list* list,vr_index index,vr_val_des_func des)
{
  vr_list_node* next_index=NULL;
  if(list->head==index&&list->foot==index){
    list->head=NULL;
    list->foot=NULL;
  }else{
    index->prev->next=index->next;
    index->next->prev=index->prev;
    if(list->head==index){
      list->head=index->next;
      next_index=list->head;
    }else if(list->foot==index){
      list->foot=index->prev;
    }else{
      next_index=index->next;
    }
  }
  vr_list_node_des(index,des);
  list->length--;
  return next_index;
}

void vr_list_cln(vr_list* list,vr_val_des_func des)
{
  vr_list_node* node=list->head;
  while(node)
    {
      if(list->foot==node)
	{
	  vr_list_node_des(node,des);
	  break;
	}
      node=node->next;
      vr_list_node_des(node->prev,des);
    }
  list->head=NULL;
  list->foot=NULL;
  list->length=0;
}

void vr_list_des(vr_list* list,vr_val_des_func des)
{
  if(!list) return;
  vr_list_cln(list,des);
  free(list);
}

static vr_list_node* vr_list_node_new(void* data)
{
  vr_list_node* node=malloc(sizeof(vr_list_node));
  if(node)
    node->data=data;
  return node;
}

static void vr_list_node_des(vr_list_node* node,vr_val_des_func des)
{
  if(des)
    des(node->data);
  free(node);
}
