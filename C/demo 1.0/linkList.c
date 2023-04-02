#include "linkList.h"
#include<stdlib.h>
#define printData(data)(printf("%d",data))
#define printDataByDelimiter(data,delimiter)(printf("%d%c",data,delimiter))
#define printDelimiterAndData(delimiter,data)(printf("%c%d",delimiter,data))
bool linkListInitalize(linkList* ppList){
	*ppList=(linkList)malloc(sizeof(linkNode));
	if(*ppList==NULL){
		printf("malloc error!\n");
		return false;
	}
	(*ppList)->next=NULL;
	return true;
}
bool linkListShow(const linkList list,const char delimiter){
	if(list==NULL){
		printf("list is null,must initalize!\n");
		return false;
	}
	linkList pList=list;
    if(pList->next==NULL){
        printf("list is empty!\n");
		return false;
    }
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
	return true;
}
bool linkListHeadInsert(linkList list,Type data){
	if(list==NULL){
		printf("list is null,must initalize,HeadInsert failed!\n");
		return false;
	}
	linkList temp=list->next;
	list->next=(linkNode*)malloc(sizeof(linkNode));
	if(list->next==NULL){
		printf("malloc error,HeadInsert failed!\n");
		list->next=temp;
		return false;
	}
	list->next->data=data;
	list->next->next=temp;
	return true;
}
bool linkListTailInsert(linkList list,Type data){
	if(list==NULL){
		printf("list is null,must initalize,TailInsert failed!\n");
		return false;
	}
	linkList pList=list;
	while(pList->next){
		pList=pList->next;
	}
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	if(pList->next==NULL){
		printf("malloc error,TailInsert failed!\n");
		return false;
	}
	pList=pList->next;
	pList->data=data;
	pList->next=NULL;
	return true;
}
bool linkListInsert(linkList list,Type data,int pos){
	if(list==NULL){
		printf("list is null,must initalize,Insert failed!\n");
		return false;
	}else if(pos<0){
		printf("position is less than 0,please input incorrect positon,Insert failed!\n");
		return false;
	}
	linkList pList=list;
	int i=0;
	while(i<pos&&pList->next){
		pList=pList->next;
		++i;
	}
	if(i<pos&&pList->next==NULL){
		printf("position is error,please input incorrect positon,Insert failed!\n");
		return false;
	}
	linkList temp=pList->next;
	pList->next=(linkNode*)malloc(sizeof(linkNode));
	if(pList->next==NULL){
		printf("malloc error,Insert failed!\n");
		return false;
	}
	pList=pList->next;
	pList->next=temp;
	pList->data=data;
	return true;
}
bool linkListErase(linkList list,int pos){
	if(list==NULL){
		printf("list is null,must initalize,Erase failed!\n");
		return false;
	}else if(pos<0){
		printf("position is less than 0,please input incorrect positon,Erase failed!\n");
		return false;
	}
	linkList pList=list;
	int i=0;
	while(i<pos&&pList->next){
		pList=pList->next;
		++i;
	}
	if(i<pos&&pList->next==NULL){
		printf("position is error,please input incorrect positon,Insert failed!\n");
		return false;
	}
	linkList temp=pList->next;
	pList->next=temp->next;
	free(temp);
	return true;
}
bool linkListIndexSearch(linkList list,int pos){
	if(list==NULL){
		printf("list is null,must initalize,IndexSearch failed!\n");
		return false;
	}else if(pos<0){
		printf("position is less than 0,please input incorrect positon,IndexSearch failed!\n");
		return false;
	}
	linkList pList=list;
	int i=0;
	while(i<pos&&pList->next){
		pList=pList->next;
		++i;
	}
	if(i<pos&&pList->next==NULL){
		printf("position is error,please input incorrect positon,IndexSearch failed!\n");
		return false;
	}
	return true;
}
int linkListDataSearch(linkList list,Type data){
	if(list==NULL){
		printf("list is null,must initalize,DataSearch failed!\n");
		return -1;
	}
	linkList pList=list;
	int i=0;
	while(pList->next){
		pList=pList->next;
		if(pList->data==data){
			return i;
		}
		++i;
	}
	printf("Can't search this data,DataSearch failed!\n");
	return -1;
}
linkNode* linkListCombine(linkList firstList,linkList lastList){
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
bool linkListFree(linkList* ppList){
	if(ppList==NULL){
		printf("list point is null,Free failed!\n");
		return false;
	}
	if(ppList!=NULL&&(*ppList)==NULL){
		printf("list is null,Free failed!\n");
		return false;
	}
	linkList temp=NULL;
	while((*ppList)->next){
		temp=(*ppList)->next;
		(*ppList)->next=temp->next;
		free(temp);
	}
	free(*ppList);
	*ppList=NULL;
	return true;
}