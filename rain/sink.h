#ifndef RN_SINK_H
#define RN_SINK_H
#include "common.h"
#include "drip.h"

typedef struct rn_sink {
  int poll_fd;
  struct epoll_event* events;
} rn_sink;

rn_sink* rn_sink_new();
void rn_sink_drip(rn_drip* drip);
void rn_sink_loop(rn_sink* sink,rn_hook ev);

#endif
