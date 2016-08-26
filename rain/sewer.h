#ifndef RN_SEWER_H
#define RN_SEWER_H
#include "pipe.h"

typedef rn_sewer {
  struct vr_lkls pipe;
} rn_sewer;

rn_sewer* rn_sewer_new();
void rn_sewer_pipe_weld(rn_pipe* pipe);
void draining(rn_sewer* sewer,rn_drip* drip);

#endif
