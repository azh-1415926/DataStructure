#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

typedef void* eleType;

typedef struct seqList
{		
	eleType* data;
	int capacity;
	int length;
}*seqList;

seqList seqListInitalize(seqList* pList,int capacity);
void seqListFree(seqList* pList);
void seqListInsert(seqList list,const eleType data,int pos);
eleType seqListErase(seqList list,int pos);
eleType seqListIndexSearch(seqList list,int pos);
int seqListDataSearch(const seqList list,const eleType data,int (*compare)(const eleType,const eleType));
seqList seqListCombine(seqList firstList,const seqList endList);
seqList seqListCombineNoRepeat(seqList firstList,const seqList endList,int (*compare)(const eleType,const eleType));

#ifdef __cplusplus
}
#endif

#endif