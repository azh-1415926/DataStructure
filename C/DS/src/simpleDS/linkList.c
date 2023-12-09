#include <simpleDS/linkList.h>
#include <stdlib.h>

linkList linkListInitalize(linkList* pList)
{
	*pList=(linkList)malloc(sizeof(linkNode));
	(*pList)->next=(eleType)0;
}

void linkListFree(linkList* pList)
{
	linkList temp=(eleType)0;
	while((*pList)->next)
	{
		temp=(*pList)->next;
		(*pList)->next=temp->next;
		free(temp);
	}
	free(*pList);
	*pList=(eleType)0;
}

void linkListHeadInsert(linkList list,const eleType data)
{
	linkList temp=list->next;
	list->next=(linkNode*)malloc(sizeof(linkNode));
	list->next->data=data;
	list->next->next=temp;
}

void linkListTailInsert(linkList list,const eleType data)
{
	linkList pList=list;
	while(pList->next)
		pList=pList->next;
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	pList=pList->next;
	pList->data=data;
	pList->next=(eleType)0;
}

void linkListInsert(linkList list,const eleType data,int pos)
{
	linkList pList=list;
	int i=0;
	while(i++<pos&&pList->next)
		pList=pList->next;
	if(i<pos&&pList->next==(eleType)0)
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
	if(i<pos&&pList->next==(eleType)0)
		return (eleType)0;
	linkList temp=pList->next;
	void* data=temp->data;
	pList->next=temp->next;
	free(temp);
	return data;
}

void* linkListIndexSearch(const linkList list,int pos)
{
	linkList pList=list;
	int i=0;
	while(i++<pos&&pList->next)
		pList=pList->next;
	if(i<pos&&pList->next==(eleType)0)
		return (eleType)0;
	return pList->data;
}

int linkListDataSearch(const linkList list,const eleType data,bool(*compare)(const eleType,const eleType))
{
	if(list==(eleType)0)
		return -1;
	linkList pList=list;
	int i=0;
	while(pList->next)
	{
		pList=pList->next;
		if(compare(pList->data,data))
			return i;
		++i;
	}
	return -1;
}

linkList linkListCombine(linkList firstList,const linkList lastList)
{
	if(lastList==(eleType)0)
		return firstList;
	if(firstList==(eleType)0)
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
		pList->next=(eleType)0;
	}
	return firstList;
}