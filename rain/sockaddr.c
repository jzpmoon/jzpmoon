#include "sockaddr.h"

rn_sockaddr* rn_sockaddr_new(char* ip,int port,int af,int type)
{
  switch(af){
  case AF_UNIX:{
    
    break;}
  case AF_INET:{
    malloc(sizeof(struct sockaddr_in));
    break;}
  }
}
