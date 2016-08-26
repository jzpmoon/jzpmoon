#idndef RN_SOCKADDR_H
#define RN_SOCKADDR_H

typedef struct rn_sockaddr {
  int af;
  int pf;
  int type;
  union addr_u {
    struct sockaddr_un un;
    struct sockaddr_in in;
    struct sockaddr_in6 in6;
  };
  int socklen;
} rn_sockaddr;

rn_sockaddr* rn_sockaddr_new(char* ip,int port,int af,int type);

#endif
