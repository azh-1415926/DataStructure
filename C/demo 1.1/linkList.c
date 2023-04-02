#include "linkList.h"
#include<stdlib.h>
#define printData(data)(printf("%d",data))
#define printDataByDelimiter(data,delimiter)(printf("%d%c",data,delimiter))
#define printDelimiterAndData(delimiter,data)(printf("%c%d",delimiter,data))
void linkListInitalize(linkList* ppList){
	*ppList=(linkList)malloc(sizeof(linkNode));
	(*ppList)->next=NULL;
}
void linkListShow(const linkList list,const char delimiter){
	linkList pList=list;
	if(pList->next){
		printf("[");
		pList=pList->next;
		printData(pList->data);
	}
	while(pList->next){
		pList=pList->next;
		printDelimiterAndData(delimiter,pList->data);
	}
	printf("]\n");
}
void linkListHeadInsert(linkList list,Type data){
	linkList temp=list->next;
	list->next=(linkNode*)malloc(sizeof(linkNode));
	list->next->data=data;
	list->next->next=temp;
}
void linkListTailInsert(linkList list,Type data){
	linkList pList=list;
	while(pList->next){
		pList=pList->next;
	}
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	pList=pList->next;
	pList->data=data;
	pList->next=NULL;
}
void linkListInsert(linkList list,Type data,int pos){
	linkList pList=list;
	int i=0;
	while(i<pos&&pList->next){
		pList=pList->next;
		++i;
	}
	if(i<pos&&pList->next==NULL)
		return;
	linkList temp=pList->next;
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	pList=pList->next;
	pList->next=temp;
	pList->data=data;
}
void linkListErase(linkList list,int pos){
	linkList pList=list;
	int i=0;
	while(i<pos&&pList->next){
		pList=pList->next;
		++i;
	}
	if(i<pos&&pList->next==NULL)
		return;
	linkList temp=pList->next;
	pList->next=temp->next;
	free(temp);
}
Type linkListIndexSearch(linkList list,int pos){
	linkList pList=list;
	int i=0;
	while(i<pos&&pList->next){
		pList=pList->next;
		++i;
	}
	if(i<pos&&pList->next==NULL)
		return 0;
	return pList->data;
}
int linkListDataSearch(linkList list,Type data){
	if(list==NULL)
		return -1;
	linkList pList=list;
	int i=0;
	while(pList->next){
		pList=pList->next;
		if(pList->data==data){
			return i;
		}
		++i;
	}
	return -1;
}
linkList linkListCombine(linkList firstList,linkList lastList){
	if(lastList==NULL){
		return firstList;
	}else if(firstList==NULL){
		return lastList;
	}
	linkList pList=firstList;
	while(pList->next){
		pList=pList->next;
	}
	linkList temp=lastList;
	lastList=NULL;
	while(temp->next){
		temp=temp->next;
		pList->next=temp;
		pList=pList->next;
	}
	return firstList;
}
void linkListFree(linkList* ppList){
	linkList temp=NULL;
	while((*ppList)->next){
		temp=(*ppList)->next;
		(*ppList)->next=temp->next;
		free(temp);
	}
	free(*ppList);
	*ppList=NULL;
}