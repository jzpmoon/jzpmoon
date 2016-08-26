#ifndef RN_CONNECT_H
#define RN_CONNECT_H
#include "common.h"

typedef struct rn_connect {
  int fd;
  struct sockaddr_in addr;
} rn_connect;

rn_connect* rn_connect_new(struct sockaddr_in addr);
void rn_connect_loop(rn_connect* connect,rn_hook ev);

#endif
