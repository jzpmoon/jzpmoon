#include <stdlib.h>
#include "rn_task.h"

rn_task* rn_task_new(rn_task_func begin,rn_task_func end,void* data)
{
  rn_task* task=(rn_task*)malloc(sizeof(rn_task));
  rn_task_init(task,begin,end,data);
  return task;
}

int rn_task_init(rn_task* task,rn_task_func begin,rn_task_func end,void* data)
{
  if(task){
    task->begin=begin;
    task->end=end;
    task->data=data;
  }
}

void rn_task_des(rn_task* task)
{
  free(task);
}
