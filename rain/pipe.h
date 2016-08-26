#ifndef RN_PIPE_H
#define RN_PIPE_H

typedef int (* rn_flow)(rn_drip* drip);

typedef struct rn_pipe {
  rn_flow enc;
  rn_flow dec;
} rn_pipe;

rn_pipe* rn_pipe_new(rn_flow enc,rn_flow dec);

#endif
