#ifndef VR_OBJ_H
#define VR_OBJ_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef void*(*_vr_obj_call_func)(void*,void*,int);

#define VR_OBJ_DECLATE(OBJ) struct OBJ* _vr_base;struct _vr_obj_info* _vr_info;

struct _vr_obj{VR_OBJ_DECLATE(_vr_obj)};
struct _vr_obj_info
{
  struct _vr_obj_info* _vr_base;
  _vr_obj_call_func _vr_call;
  char* _vr_type;
  int _vr_size;
};

extern struct _vr_obj_info _vr_obj_info;

void* _vr_obj_call_query(void* ins,void* info_ins,int num);
void* _vr_obj_call(void* ins,void* info_ins,int num);
struct _vr_obj* _vr_obj_new(struct _vr_obj_info* obj);
int _vr_obj_des(struct _vr_obj* ins);

#define _VR_OBJ_INFO_DECLATE(OBJ)		\
  struct _vr_obj_info OBJ##_info

#define _VR_OBJ_CALL_DECLATE(OBJ)				\
  void* _vr_obj_##OBJ##_call(void* ins,void* info_ins,int num)

#define _VR_OBJ_INFO(BASE,OBJ)						\
  _VR_OBJ_INFO_DECLATE(OBJ)={&BASE##_info,				\
			     _vr_obj_##OBJ##_call,			\
			     #OBJ,					\
			     sizeof(struct OBJ)};

#define VR_OBJ_MAP_BEGIN(BASE,OBJ)				\
  _VR_OBJ_CALL_DECLATE(OBJ);					\
  _VR_OBJ_INFO(BASE,OBJ)					\
  _VR_OBJ_CALL_DECLATE(OBJ){					\
  switch(num){

#define VR_F_MAP(OBJ,NUM,CALL)				\
  case (NUM): {return &((struct OBJ*)ins)->CALL;}

#define VR_M_MAP(NUM,CALL)			\
  case (NUM): {return (CALL);}

#define VR_OBJ_MAP_END				\
  default:return NULL;}				\
  }

#define VR_OBJ_MAP_DECLATE(OBJ)						\
  extern _VR_OBJ_INFO_DECLATE(OBJ);					\
  extern _VR_OBJ_CALL_DECLATE(OBJ);

#define VR_OBJ_NEW(OBJ)				\
  (struct OBJ*)_vr_obj_new(&OBJ##_info);

#define VR_OBJ_DES(INS)				\
  _vr_obj_des((struct _vr_obj*)(INS));

#define VR_OBJ_CALL(OBJ,INS,NUM)		\
  _vr_obj_call_query(INS,&OBJ##_info,NUM);

#define VR_OBJ_TYPE(INS)			\
  (INS)->_vr_info->_vr_type;

#define VR_OBJ_TYPEOF(A,B)			\
  ((A)->_vr_info==(B)->_vr_info) ? 1:0;

#define VR_ROOT vroot

struct vroot
{
  VR_OBJ_DECLATE(_vr_obj)
};

VR_OBJ_MAP_DECLATE(vroot)

#endif
