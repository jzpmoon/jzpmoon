#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>

int main(int argc,char** argv){
  int servsock_fd,clisock_fd;
  int epoll_fd;
  struct sockaddr_in serv_addr,cli_addr;
  socklen_t socklen=sizeof(struct sockaddr_in);
  struct epoll_event ev;
  struct epoll_event events[1024];
  bzero(&serv_addr,socklen);
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_addr.sin_port=8241;
  servsock_fd=socket(AF_INET,SOCK_STREAM,0);
  bind(servsock_fd,(struct sockaddr*)&serv_addr,socklen);
  listen(servsock_fd,1024);
  epoll_fd=epoll_create(1024);
  ev.events=EPOLLIN||EPOLLET;
  ev.data.fd=servsock_fd;
  epoll_ctl(epoll_fd,EPOLL_CTL_ADD,servsock_fd,&ev);
  for(;;){
   int nfd=epoll_wait(servsock_fd,events,1024,-1);   
   if(nfd==-1){
     fprintf(stderr,"epoll_watit error");
     break;
   }
   int i;
   for(i=0;i<nfd;i++){
     if(events[i].data.fd==servsock_fd){
       clisock_fd=accept(servsock_fd,(struct sockaddr*)&cli_addr,&socklen);
       ev.events=EPOLLIN|EPOLLET;
       ev.data.fd=clisock_fd;
       epoll_ctl(epoll_fd,EPOLL_CTL_ADD,clisock_fd,&ev);
     }
   }
  }
}
