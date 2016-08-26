#include "lkls.h"
#include <stdio.h>

int test(){
  vr_lkls* ls=vr_lkls_init();
  int j=0,ret=0,size=0,i=0;
  while(i<10){
    vr_lkls_ins(ls,&i,4,i);
    vr_lkls_upd(ls,&ret,4,i);
    i++;ret+=12;
  }
  printf("lkls size:%d\n",vr_lkls_size(ls));
  //vr_lkls_del(ls,9);
  while(j<10){
    vr_lkls_get(ls,(void*)&ret,&size,j);
    printf("lkls:%d,%d\n",ret,vr_lkls_size(ls));
    j++;
    }
}

int main(){
  test();
}
