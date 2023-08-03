#include <simpleDS/linkList.h>
#include <stdlib.h>

void linkListInitalize(linkList* ppList)
{
	*ppList=(linkList)malloc(sizeof(linkNode));
	(*ppList)->next=NULL;
}

void linkListFree(linkList* ppList)
{
	linkList temp=NULL;
	while((*ppList)->next){
		temp=(*ppList)->next;
		(*ppList)->next=temp->next;
		free(temp);
	}
	free(*ppList);
	*ppList=NULL;
}

void linkListHeadInsert(linkList list,void* const data)
{
	linkList temp=list->next;
	list->next=(linkNode*)malloc(sizeof(linkNode));
	list->next->data=data;
	list->next->next=temp;
}

void linkListTailInsert(linkList list,void* const data)
{
	linkList pList=list;
	while(pList->next)
		pList=pList->next;
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	pList=pList->next;
	pList->data=data;
	pList->next=NULL;
}

void linkListInsert(linkList list,void* const data,int pos)
{
	linkList pList=list;
	int i=0;
	while(i++<pos&&pList->next)
		pList=pList->next;
	if(i<pos&&pList->next==NULL)
		return;
	linkList temp=pList->next;
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	pList=pList->next;
	pList->next=temp;
	pList->data=data;
}

void* linkListErase(linkList list,int pos)
{
	linkList pList=list;
	int i=0;
	while(i++<pos&&pList->next)
		pList=pList->next;
	if(i<pos&&pList->next==NULL)
		return NULL;
	linkList temp=pList->next;
	void* data=temp->data;
	pList->next=temp->next;
	free(temp);
	return data;
}

void* linkListIndexSearch(linkList const list,int pos)
{
	linkList pList=list;
	int i=0;
	while(i++<pos&&pList->next)
		pList=pList->next;
	if(i<pos&&pList->next==NULL)
		return NULL;
	return pList->data;
}

int linkListDataSearch(linkList const list,void* const data,bool(*compare)(void*,void* const))
{
	if(list==NULL)
		return -1;
	linkList pList=list;
	int i=0;
	while(pList->next){
		pList=pList->next;
		if(compare(pList->data,data))
			return i;
		++i;
	}
	return -1;
}

linkList linkListCombine(linkList firstList,linkList const lastList)
{
	if(lastList==NULL)
		return firstList;
	if(firstList==NULL)
		return lastList;
	linkList pList=firstList;
	while(pList->next)
		pList=pList->next;
	linkList temp=lastList;
	while(temp->next){
		temp=temp->next;
		pList->next=(linkNode*)malloc(sizeof(linkNode));
		pList=pList->next;
		pList->data=temp->data;
		pList->next=NULL;
	}
	return firstList;
}