#include "lkls.h"
#include "lkstk.h"
#include "lkque.h"
#include <stdio.h>

int test(){
  vr_lkls* ls=vr_lkls_new();
  int j=0,ret=0,size=0,i=0;
  while(i<10){
    vr_lkls_ins(ls,&i,0,i);
    //   vr_lkls_upd(ls,&ret,4,i);
    i++;ret+=12;
  }
  printf("lkls size:%d\n",vr_lkls_size(ls));
  /* vr_lkls_del(ls,9); */
  while(j<10){
    vr_lkls_get(ls,(void*)&ret,&size,j);
    printf("lkls:%d,%d\n",ret,vr_lkls_size(ls));
    j++;
    }
  vr_lkls_cln(ls);
  printf("lkls size:%d\n",vr_lkls_size(ls));
}
 int test_lkstk() 
 { 
   int val=0,ret=0,size=0,i=0,j=0,len=0; 
   vr_lkstk* stk=vr_lkstk_new(); 
   while(i<10){ 
     vr_lkstk_pull(stk,&val,4); 
     i++;val++; 
   } 
   while(j<11){ 
     vr_lkstk_pop(stk,&ret,&size); 
     printf("lkstk:%d,length:%d\n",ret,vr_lkstk_size(stk)); 
     j++; 
   } 
 } 
void test_que()
{
  vr_lkque* que=vr_lkque_new();
  int val=10,ret=0,size=0,i=0,j=0;
  while(i<10){
  vr_lkque_enq(que,&i,4);
  if(i==2){
    vr_lkque_deq(que,&ret,&size);
    printf("lkque:%d,size:%d,\n",ret,vr_lkque_size(que));
  }
  i++;}
  while(j<10){
  vr_lkque_deq(que,&ret,&size);
  printf("lkque:%d,size:%d\n",ret,vr_lkque_size(que));
  j++;
  }
}
int main(){
  test();
  test_lkstk();
  //test_que();
}
