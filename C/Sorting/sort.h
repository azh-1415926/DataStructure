#ifndef _SORT_H_
#define _SORT_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* eleType;
void bubbleSort(eleType array,int n,int size,int(*compare)(const eleType,const eleType));
void selectSort(eleType array,int n,int size,int(*compare)(const eleType,const eleType));

#ifdef __cplusplus
}
#endif

#endif /* _SORT_H_ */