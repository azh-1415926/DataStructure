#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int Type;
typedef struct seqList {		
	Type *pList;
	int capacity;
	int length;
}*seqList;
bool seqListInitalize(seqList* ppList,int capacity);
bool seqListShow(const seqList list,const char delimiter);
bool seqListInsert(seqList list,Type data,int pos);
int seqListDataSearch(seqList list,Type data);
Type seqListIndexSearch(seqList list,int pos);
seqList seqListCombine(seqList firstList,seqList endList);
seqList seqListCombineNoRepeat(seqList firstList,seqList endList);
bool seqListFree(seqList* list);
#endif