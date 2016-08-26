#ifndef RN_LISTEN_H
#define RN_LISTEN_H
#include "common.h"
#include "sockaddr.h"

typedef struct rn_listen{
  int fd;
  struct rn_sockaddr* addr;
} rn_listen;

rn_listen* rn_listen_new(rn_sockaddr* addr);
void rn_listen_loop(rn_listen* listen,rn_hook ev);

#endif
