#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_
#include<stdio.h>
#include<stdbool.h>
typedef int Type;
typedef struct linkNode{
	Type data;
	struct linkNode *next;
}linkNode,*linkList;
bool linkListInitalize(linkList* ppList);
bool linkListShow(const linkList list,const char delimiter);
bool linkListHeadInsert(linkList list,Type data);
bool linkListTailInsert(linkList list,Type data);
bool linkListInsert(linkList list,Type data,int pos);
bool linkListErase(linkList list,int pos);
bool linkListIndexSearch(linkList list,int pos);
int linkListDataSearch(linkList list,Type data);
linkNode* linkListCombine(linkList firstList,linkList lastList);
bool linkListFree(linkList* ppList);
#endif