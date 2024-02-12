#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void Type;
typedef Type* pType;
void bubbleSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void selectionSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void insertionSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void shellSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void mergeSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void mergeSortRecursive(pType array,int n,int size,int(*compare)(const pType,const pType));
void quickSort(pType array,int n,int size,int(*compare)(const pType,const pType));
void quickSortRecursive(pType array, int n, int size, int (*compare)(const pType, const pType));
void heapSort(pType array, int n, int size, int (*compare)(const pType, const pType));

#ifdef __cplusplus
}
#endif

#endif /* SORT_H */