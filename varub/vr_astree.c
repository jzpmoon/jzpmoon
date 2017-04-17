#include <stdarg.h>
#include "vr_astree.h"

vr_ast_node* vr_ast_node_init(vr_ast_node* node,int type)
{
  if(node==NULL)
    return NULL;
  node->type=type;
  node->child=NULL;
  node->brother=NULL;
  return node;
}

void vr_ast_des(vr_ast_node* ast)
{
  
}

static vr_ast_node* vr_ast_node_last_child(vr_ast_node* parent)
{
  vr_ast_node* tmp=NULL;;
  vr_ast_node* child=parent->child;
  while(child!=NULL){
    tmp=child;
    child=child->brother;
  }
  return tmp;
}

void vr_ast_node_deriver(vr_ast_node* parent,int count,...)
{
  int i=1;
  va_list ptr;
  vr_ast_node* child=NULL;
  vr_ast_node* last_child=NULL;
  last_child=vr_ast_node_last_child(parent);
  va_start(ptr,count);
  child=(vr_ast_node*)va_arg(ptr,vr_ast_node*);
  if(last_child!=NULL)
    last_child->brother=child;
  else
    parent->child=child;
  while(i<count){
    vr_ast_node* tmp=(vr_ast_node*)va_arg(ptr,vr_ast_node*);
    child->brother=tmp;
    child=tmp;
    i++;
  }
  va_end(ptr);
}
