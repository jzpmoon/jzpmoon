#ifndef RN_TASK_H
#define RN_TASK_H

typedef int (*rn_task_func)(void* data);
typedef struct rn_task rn_task;

struct rn_task {
  rn_task_func begin;
  rn_task_func end;
  void* data;
};

rn_task* rn_task_new(rn_task_func begin,rn_task_func end,void* data);
int rn_task_init(rn_task* task,rn_task_func begin,rn_task_func end,void* data);
void rn_task_des(rn_task* task);
#endif
