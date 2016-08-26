/* link stack include */
#ifndef VR_LKSTK_H_INCL
#define VR_LKSTK_H_INCL

typedef struct vr_lkstk vr_lkstk;

vr_lkstk* vr_lkstk_new();
void vr_lkstk_des(vr_lkstk* stk);
void vr_lkstk_pull(vr_lkstk* stk,void* val,int size);
void vr_lkstk_pop(vr_lkstk* stk,void* val,int* size);
void vr_lkstk_cln(vr_lkstk* stk);
int vr_lkstk_size(vr_lkstk* stk);

#endif
