#ifndef RN_WORKERGRP_H
#define RN_WORKERGRP_H

#include <pthread.h>
#include "rn_task.h"
#include "vr_queue.h"

typedef struct rn_workergrp rn_workergrp;

struct rn_workergrp {
  vr_queue queue;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  #define RN_WG_START 0
  #define RN_WG_STOP 1
  #define RN_WG_EXIT -1
  int state;
  int max_size;
  int real_size;
  int idle_size;
};

rn_workergrp* rn_workergrp_new(int size);
int rn_workergrp_init(rn_workergrp* wg,int size);
int rn_workergrp_des(rn_workergrp* wg);
int rn_workergrp_start(rn_workergrp* wg);
int rn_workergrp_stop(rn_workergrp* wg);
int rn_workergrp_post(rn_workergrp* wg,rn_task* task);
int rn_workergrp_resize(rn_workergrp* wg,int size);
#endif
