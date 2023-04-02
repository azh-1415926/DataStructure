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
void seqListInitalize(seqList* ppList,int capacity);
void seqListShow(const seqList list,const char delimiter);
void seqListInsert(seqList list,Type data,int pos);
int seqListDataSearch(seqList list,Type data);
Type seqListIndexSearch(seqList list,int pos);
seqList seqListCombine(seqList firstList,seqList endList);
seqList seqListCombineNoRepeat(seqList firstList,seqList endList);
void seqListFree(seqList* list);
#endif