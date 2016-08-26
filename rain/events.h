#ifndef RN_EVENTS_H
#define RN_EVENTS_H

#define EV_ACCEPT 0
#define EV_CONN 1
#define EV_READ 2
#define EV_WRITE 3
#define EV_ERR 4

typedef void (*rn_hook)(int fd,int event);

#endif
