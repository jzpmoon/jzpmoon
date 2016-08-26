/* link queue include */
#ifndef VR_LKQUE_H_INCL
#define VR_LKQUE_H_INCL

typedef struct vr_lkque vr_lkque;

vr_lkque* vr_lkque_new();
void vr_lkque_des(vr_lkque* que);
void vr_lkque_enq(vr_lkque* que,void* val,int size);
void vr_lkque_deq(vr_lkque* que,void* val,int* size);
void vr_lkque_cln(vr_lkque* que);
int vr_lkque_size(vr_lkque* que);

#endif
