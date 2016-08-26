#ifndef RN_DRIP_H
#define RN_DRIP_H
#include "common.h"

typedef struct rn_drip {
  int fd;
  struct sockaddr_in addr;
} rn_drip;

#endif
