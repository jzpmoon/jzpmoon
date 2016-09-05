#ifndef VR_TYPES_H
#define VR_TYPES_H

typedef int (*vr_hook_fn_t)(char* match,...);
typedef int (*vr_compare_fn_t)(void* max,void* min,int mxsz,int mnsz);

#endif
