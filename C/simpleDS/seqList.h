#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct seqList {		
	void** pList;
	int capacity;
	int length;
}*seqList;
void seqListInitalize(seqList* ppList,int capacity);
void seqListFree(seqList* list);
void seqListInsert(seqList list,void* data,int pos);
void* seqListErase(seqList list,int pos);
void* seqListIndexSearch(seqList list,int pos);
int seqListDataSearch(seqList list,void* const data,bool(*compare)(void*,void* const));
seqList seqListCombine(seqList firstList,seqList const endList);
seqList seqListCombineNoRepeat(seqList firstList,seqList const endList,bool(*compare)(void*,void* const));

#ifdef __cplusplus
}
#endif

#endif