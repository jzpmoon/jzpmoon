#include <pthread.h>
#include <stdlib.h>
#include "rn_workergrp.h"

int task_begin()
{
  printf("thread:%d, task,begin\n",pthread_self());
  sleep(3);
}
int task_end()
{
  printf("thread:%d, task,end\n",pthread_self());
}
int test_wg()
{
  rn_workergrp* wg=rn_workergrp_new(10);
  rn_workergrp_start(wg);
  rn_task* task=rn_task_new(task_begin,task_end,NULL);
  int i=0;
  while(i++<100){
    sleep(1);
    rn_workergrp_post(wg,task);
  }
  sleep(5);
  rn_workergrp_des(wg);
  return 0;
}
void* hook(void* arg)
{
  pthread_mutex_lock((pthread_mutex_t*)arg);
  printf("%d\n",pthread_self());
}
int test_mutex()
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex,NULL);
  pthread_t thread;
  pthread_create(&thread,NULL,hook,&mutex);
  pthread_create(&thread,NULL,hook,&mutex);
  sleep(5);
}
void main()
{
  test_wg();
}
