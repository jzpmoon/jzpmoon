#include "ptr.h"

void vr_nd_ptr_set(void** nd_ptr,void* ptr,int* nd_ptr_sz,int ptr_sz)
{
  if(*nd_ptr_sz!=ptr_sz){
    if(*nd_ptr!=NULL)
      free(*nd_ptr);
    *nd_ptr=malloc(ptr_sz);
    *nd_ptr_sz=ptr_sz;
  }
  memcpy(*nd_ptr,ptr,ptr_sz);
}
