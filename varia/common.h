#ifndef VR_COMMON_H
#define VR_COMMON_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/types.h"

#define ERR_HDL(MSG)				\
  do{						\
    fprintf(stderr,MSG);			\
    abort();					\
  }while(0)

#endif
