#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_
#include<stdio.h>
#include<stdbool.h>
typedef int Type;
typedef struct linkNode{
	Type data;
	struct linkNode *next;
}linkNode,*linkList;
void linkListInitalize(linkList* ppList);
void linkListShow(const linkList list,const char delimiter);
void linkListHeadInsert(linkList list,Type data);
void linkListTailInsert(linkList list,Type data);
void linkListInsert(linkList list,Type data,int pos);
void linkListErase(linkList list,int pos);
Type linkListIndexSearch(linkList list,int pos);
int linkListDataSearch(linkList list,Type data);
linkList linkListCombine(linkList firstList,linkList lastList);
void linkListFree(linkList* ppList);
#endif