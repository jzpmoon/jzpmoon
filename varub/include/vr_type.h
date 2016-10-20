#ifndef VR_TYPES_H
#define VR_TYPES_H

#define VR_TREE_PRE_ORDER_TRAV (0)
#define VR_TREE_IN_ORDER_TRAV (1)
#define VR_TREE_POST_ORDER_TRAV (2)
typedef int (*vr_hook_func)();
typedef void(*vr_val_des_func)(void*);
typedef int (*vr_compare_func)(void* max,void* min);
typedef int(*vr_trav_func)(void* key,void* val);

#endif
