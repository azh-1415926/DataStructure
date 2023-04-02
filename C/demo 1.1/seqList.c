#include "seqList.h"
#define printData(data)(printf("%d",data))
#define printDataByDelimiter(data,delimiter)(printf("%d%c",data,delimiter))
#define printDelimiterAndData(delimiter,data)(printf("%c%d",delimiter,data))
void seqListInitalize(seqList* ppList,int capacity){
    *ppList=(seqList)malloc(sizeof(struct seqList));
	(*ppList)->pList=malloc(sizeof(Type)*capacity);
	(*ppList)->capacity=capacity;
	(*ppList)->length=0;
}
void seqListShow(const seqList list,const char delimiter){
	for(int i=0;i<list->length;++i){
		if(i==0){
			printDelimiterAndData('[',list->pList[i]);
		}else if(i>0){
			printDelimiterAndData(delimiter,list->pList[i]);
		}
		if(i==list->length-1){
			printf("]\n");
		}
	}
}
void seqListInsert(seqList list,Type data,int pos){
	if(pos<0||pos>=list->capacity)
		return;
	++list->length;
	for(int i=list->length-1;i>pos;--i){
		list->pList[i]=list->pList[i-1];
	}
	list->pList[pos]=data;
}
int seqListDataSearch(seqList list,Type data){
	for(int i=0;i<list->length;++i)
		if(list->pList[i]==data)
			return i;
	return -1;
}
Type seqListIndexSearch(seqList list,int pos){
	if(pos<0||pos>=list->length)
		return 0;
	return list->pList[pos];
}
seqList seqListCombine(seqList firstList,seqList endList){
	seqList list;
	seqListInitalize(&list,firstList->length+endList->length);
	for(int i=0,j=0;i<list->capacity;++i){
		if(i<firstList->capacity){
			list->pList[i]=firstList->pList[i];
		}else{
			list->pList[i]=endList->pList[j];
			j++;
		}
	}
	list->length=list->capacity;
	return list;
}
seqList seqListCombineNoRepeat(seqList firstList,seqList endList){
	seqList list=seqListCombine(firstList,endList);
	for(int i=0;i<list->length-1;++i){
		for(int j=i+1;j<list->length;++j){
			if(list->pList[i]==list->pList[j]){
				for(int k=j;k<list->length-1;k++){
					list->pList[k]=list->pList[k+1];
				}
				--j;
				--list->length;
			}
		}
	}
	return list;
}
void seqListFree(seqList* ppList){
	free((*ppList)->pList);
	free(*ppList);
	*ppList=NULL;
}