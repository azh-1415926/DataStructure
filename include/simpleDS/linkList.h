#ifndef LINK_LIST_H
#define LINK_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

typedef void* eleType;

typedef struct linkNode
{
	eleType data;
	struct linkNode *next;
}linkNode,*linkList;

linkList linkListInitalize(linkList* pList);
void linkListFree(linkList* pList);
void linkListHeadInsert(linkList list,const eleType data);
void linkListTailInsert(linkList list,const eleType data);
void linkListInsert(linkList list,const eleType data,int pos);
eleType linkListErase(linkList list,int pos);
eleType linkListIndexSearch(const linkList list,int pos);
int linkListDataSearch(const linkList list,const eleType data,bool(*compare)(const eleType,const eleType));
linkList linkListCombine(linkList firstList,const linkList lastList);

#ifdef __cplusplus
}
#endif

#endif