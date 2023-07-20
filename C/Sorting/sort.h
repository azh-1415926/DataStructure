#ifndef _SORT_H_
#define _SORT_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void eleType;
typedef eleType* pType;
void bubbleSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void selectionSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void insertionSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void shellSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void mergeSort(pType array,int n,int size,int(*compare)(const pType,const pType));

#ifdef __cplusplus
}
#endif

#endif /* _SORT_H_ */