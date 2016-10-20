#ifndef VR_ERROR_H
#define VR_ERROR_H

#define ERR_HDL(MSG)				\
  do{						\
    fprintf(stderr,MSG);			\
    abort();					\
  }while(0)

#define VR_IDX_CHK(S,I)				\
  if((I)<0||(I)>(S)-1)				\
    ERR_HDL("lkls out of bounds!")

#define VR_STK_EMPTY_CHK(S)			\
  if((S)==0)					\
    ERR_HDL("lkstk stack is empty!")

#define VR_QUE_EMPTY_CHK(S)			\
  if((S)==0)					\
    ERR_HDL("lkque queue is empty!")

#endif
