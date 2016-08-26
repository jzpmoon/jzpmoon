#include "listen.h"

rn_listen* rn_listen_new(rn_sockaddr* addr)
{
  rn_listen* listen=(rn_listen*)malloc(sizeof(rn_listen));
  listen->addr=addr;
  int fd=socket(addr->pf,adr->type,0);
  bind(fd,(struct sockaddr*)addr->addr,sizeof(addr->socklen));
  listen(fd,5);
  listen->fd=fd;
}

void rn_listen_loop(rn_listen* listen,rn_hook)
{

}
