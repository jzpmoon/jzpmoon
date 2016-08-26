/**
 *link list include
 */
#ifndef VR_LKLS_H_INCL
#define VR_LKLS_H_INCL

typedef struct vr_lkls_nd vr_lkls_nd;
typedef struct vr_lkls vr_lkls;

vr_lkls* vr_lkls_new();
void vr_lkls_des(vr_lkls* ls);
void vr_lkls_ins(vr_lkls* ls,void* val,int size,int pos);
void vr_lkls_apd(vr_lkls* ls,void* val,int size);
void vr_lkls_upd(vr_lkls* ls,void* val,int size,int pos);
void vr_lkls_get(vr_lkls* ls,void* val,int* size,int pos);
void vr_lkls_del(vr_lkls* ls,int pos);
void vr_lkls_cln(vr_lkls* ls);
int vr_lkls_size(vr_lkls* ls);

#endif
