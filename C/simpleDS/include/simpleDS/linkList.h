#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdbool.h>
typedef struct linkNode{
	void* data;
	struct linkNode *next;
}linkNode,*linkList;
void linkListInitalize(linkList* ppList);
void linkListFree(linkList* ppList);
void linkListHeadInsert(linkList list,void* const data);
void linkListTailInsert(linkList list,void* const data);
void linkListInsert(linkList list,void* const data,int pos);
void* linkListErase(linkList list,int pos);
void* linkListIndexSearch(linkList const list,int pos);
int linkListDataSearch(linkList const list,void* const data,bool(*compare)(void*,void* const));
linkList linkListCombine(linkList firstList,linkList const lastList);

#ifdef __cplusplus
}
#endif

#endif