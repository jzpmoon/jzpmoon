#include "include/vr_obj.h"

struct _vr_obj_info _vr_obj_info={NULL,
				  _vr_obj_call,
				  "_vr_obj",
				  sizeof(struct _vr_obj)};

VR_OBJ_MAP_BEGIN(_vr_obj,vroot)
/*map declate*/
VR_OBJ_MAP_END

void* _vr_obj_call_query(void* ins,void* info_ins,int num){
  void* call=NULL;
  struct _vr_obj* _ins=ins;
  struct _vr_obj_info* _info_ins=info_ins;
  if(!ins&&!info_ins) return NULL;
  while(_ins!=NULL)
    {
      if(_ins->_vr_info==_info_ins)
	break;
      _ins=_ins->_vr_base;
    }
  if(_ins==NULL)
    {
      _ins=ins;
      while(_info_ins!=NULL)
	{
	  if(_ins->_vr_info==_info_ins)
	    break;
	  _info_ins=_info_ins->_vr_base;
	}
    }
  if(_info_ins==NULL) return NULL;
  if((call=(*_info_ins->_vr_call)(_ins,_info_ins,num))==NULL&&_info_ins->_vr_base!=NULL)
    call= _vr_obj_call_query(_ins->_vr_base,_info_ins->_vr_base,num);
  return call;
}

struct _vr_obj* _vr_obj_new(struct _vr_obj_info* info)
{
  struct _vr_obj_info* _info=info;
  struct _vr_obj* tmp=malloc(_info->_vr_size);
  struct _vr_obj* ins=tmp;
  ins->_vr_info=_info;
  _info=_info->_vr_base;
  while(_info!=NULL){
    tmp->_vr_base=malloc(_info->_vr_size);
    tmp->_vr_base->_vr_info=_info;
    tmp=tmp->_vr_base;
    _info=_info->_vr_base;
  }
  tmp->_vr_base=NULL;
  return ins;
}

int _vr_obj_des(struct _vr_obj* ins)
{
  struct _vr_obj* _ins=ins;
  while(!_ins)
    {
      struct _vr_obj* tmp=_ins;
      _ins=_ins->_vr_base;
      free(tmp);
    }
  return 0;
}

void* _vr_obj_call(void* ins,void* info_ins,int num)
{
  return NULL;
}
