#ifndef VR_ASTREE_H
#define VR_ASTREE_H

#define VR_AST_NODE_NEW(NT,T) vr_ast_node_init(malloc(sizeof(NT)),(T))

#define VR_AST_NODE_HEADER			\
  int type;					\
  struct vr_ast_node* child;			\
  struct vr_ast_node* brother;

typedef struct vr_ast_node{
  VR_AST_NODE_HEADER
} vr_ast_node,vr_astree;

vr_ast_node* vr_ast_node_init(vr_ast_node* node,int type);

void vr_ast_node_deriver(vr_ast_node* parent,int count,...);

void vr_ast_des(vr_ast_node* ast);

#endif
