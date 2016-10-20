/* worker group */
#include <stdlib.h>
#include "rn_workergrp.h"

static void* rn_worker_work(void* arg);
static int  rn_worker_task_proc(rn_task* task);

rn_workergrp* rn_workergrp_new(int size)
{
  rn_workergrp* wg=(rn_workergrp*)malloc(sizeof(rn_workergrp));
  rn_workergrp_init(wg,size);
  return wg;
}

int rn_workergrp_init(rn_workergrp* wg,int size)
{
  if(!wg) return -1;
  vr_queue_init(&wg->queue);
  pthread_mutex_init(&wg->mutex,NULL);
  pthread_cond_init(&wg->cond,NULL);
  wg->state=RN_WG_STOP;
  wg->max_size=size;
  wg->real_size=0;
  wg->idle_size=0;
  return 0;
}

int rn_workergrp_des(rn_workergrp* wg)
{
  pthread_mutex_lock(&wg->mutex);
  wg->state=RN_WG_EXIT;
  if(wg->idle_size)
    pthread_cond_broadcast(&wg->cond);
  while(wg->real_size){
    pthread_cond_wait(&wg->cond,&wg->mutex);
    printf("real_size:%d\n",wg->real_size);
  }
  pthread_mutex_unlock(&wg->mutex);
  pthread_mutex_destroy(&wg->mutex);
  pthread_cond_destroy(&wg->cond);
  vr_queue_cln(&wg->queue,NULL);
  free(wg);
  return 0;
}

int rn_workergrp_start(rn_workergrp* wg)
{
  pthread_mutex_lock(&wg->mutex);
  wg->state=RN_WG_START;
  pthread_mutex_unlock(&wg->mutex);
  pthread_cond_signal(&wg->cond);
  return 0;
}

int rn_workergrp_stop(rn_workergrp* wg)
{
  pthread_mutex_lock(&wg->mutex);
  wg->state=RN_WG_STOP;
  pthread_mutex_unlock(&wg->mutex);
  pthread_cond_signal(&wg->cond);
  return 0;
}

int rn_workergrp_post(rn_workergrp* wg,rn_task* task)
{
  printf("begin post\n");
  pthread_mutex_lock(&wg->mutex);
  if(wg->state!=RN_WG_START){
    pthread_mutex_unlock(&wg->mutex);
    return -1;
  }
  printf("idle_size:%d,real_size:%d,max_size:%d\n",wg->idle_size,wg->real_size,wg->max_size);
  vr_queue_enq(&wg->queue,task);
  if(wg->idle_size==0&&wg->real_size<wg->max_size){
    pthread_t thread;
    pthread_create(&thread,NULL,rn_worker_work,wg);
    pthread_detach(thread);
    wg->real_size++;
  }
  pthread_mutex_unlock(&wg->mutex);
  pthread_cond_signal(&wg->cond);
  printf("end post\n");
}

static void* rn_worker_work(void* arg)
{
  rn_workergrp* wg=(rn_workergrp*)arg;
  printf("new thread:%d\n",pthread_self());
  while(1){
    pthread_mutex_lock(&wg->mutex);
    if(vr_queue_size(&wg->queue)>0){
      rn_task* task=vr_queue_deq(&wg->queue);
      pthread_mutex_unlock(&wg->mutex);
      rn_worker_task_proc(task);
    } else {
      if(wg->state==RN_WG_EXIT){
	wg->real_size--;
	pthread_mutex_unlock(&wg->mutex);
	pthread_cond_signal(&wg->cond);
	printf("thread:%d,exit\n",pthread_self());
	break;
      } else {
	printf("thread:%d,sleep\n",pthread_self());
	wg->idle_size++;
	pthread_cond_wait(&wg->cond,&wg->mutex);
	pthread_mutex_unlock(&wg->mutex);
	printf("thread:%d,awake\n",pthread_self());
	wg->idle_size--;
      }
    }
  }
}

static int  rn_worker_task_proc(rn_task* task)
{
  if(!task) return -1;
  if(task->begin) (*task->begin)(task->data);
  if(task->end) (*task->end)(task->data);
  return 0;
}
