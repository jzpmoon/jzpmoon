#include "include/vr_slist.h"
#include "include/vr_queue.h"
#include "include/vr_stack.h"
#include "include/vr_bitree.h"
#include "include/vr_rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void des(int* i)
{
  
}
int test(){
  vr_slist* ls=vr_slist_new();
  int val[10]={0,1,2,3,4,5,6,7,8,9};
  int i=0,j=0;
  while(i<10){
    vr_slist_apd(ls,&val[i++]);
  }
  while(j<10){
    printf("slist:%d\n",*(int*)vr_slist_get(ls,j++));
  }
}

void test_queue()
{
  vr_queue* ls=vr_queue_new(NULL);
  int val[10]={0,1,2,3,4,5,6,7,8,9};
  int i=0,j=0;
  while(i<10){
    vr_queue_enq(ls,&val[i++]);
  }
  while(j++<10){
    printf("queue:%d:%d\n",*(int*)vr_queue_deq(ls),vr_queue_size(ls));
  }
}

void test_stack()
{
  vr_stack* ls=vr_stack_new(NULL);
  int val[10]={0,1,2,3,4,5,6,7,8,9};
  int i=0,j=0;
  while(i<10){
    vr_stack_push(ls,&val[i++]);
  }
  val[3]=20;
  while(j++<10){
    printf("stack:%d\n",*(int*)vr_stack_pop(ls));
  }
}

int comp(void* a,void* b)
{
  if(*(int*)a>*(int*)b)
    return 1;
  if(*(int*)a==*(int*)b)
    return 0;
  return -1;
}
int trav(void* key,void* val)
{
  printf("key:%d,val:%d\n",*(int*)key,*(int*)val);
  return 0;
}
int test_bitree()
{
  printf("begin bitree\n");  
  vr_bitree* tree=vr_bitree_new(comp);
  int val[10]={1,0,2,3,4,7,6,5,8,9};
  int i=0;
  while(i<10){
    vr_bitree_ins(tree,&val[i],&val[i]);i++;
  }
  vr_bitree_trav(tree,trav,VR_TREE_IN_ORDER_TRAV);
  printf("end bitree\n");
}

int test_rbtree()
{
  vr_rbtree* tree=vr_rbtree_new(comp);
  int val[20];
  int k=0,i=0,j=0;
  
  while(k<20){
    val[k]=k;k++;
  }

  while(i<20){
    vr_rbtree_ins(tree,&val[i],&val[i]);i++;
  }
  
  /* while(j<20){ */
  /*   vr_rbtree_del(tree,&val[j]); */
  /*   j++; */
  /* } */
  vr_rbtree_trav(tree,trav,VR_TREE_PRE_ORDER_TRAV);
}

int main(){
  test();
  test_queue();
  test_stack();
  test_bitree();
  test_rbtree();
}
