#include "seqList.h"
#define printData(data)(printf("%d",data))
#define printDataByDelimiter(data,delimiter)(printf("%d%c",data,delimiter))
#define printDelimiterAndData(delimiter,data)(printf("%c%d",delimiter,data))
bool seqListInitalize(seqList* ppList,int capacity){
	if(ppList==NULL){
        printf("please input incorrect point,Initalize failed!\n");
        return false;
    }
    *ppList=(seqList)malloc(sizeof(struct seqList));
    if(ppList==NULL){
        printf("malloc error,Initalize failed!\n");
        return false;
    }
	(*ppList)->pList=malloc(sizeof(Type)*capacity);
	if((*ppList)->pList==NULL){
		printf("malloc error!\n");
		return false;
	}
	(*ppList)->capacity=capacity;
	(*ppList)->length=0;
	return true;
}
bool seqListShow(const seqList list,const char delimiter){
	if(list==NULL){
		printf("list is null,please initalize it,Show failed!\n");
        return false;
	}
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
	return true;
}
bool seqListInsert(seqList list,Type data,int pos){
	if(list==NULL){
		printf("list is null,please initalize it,Insert failed!\n");
        return false;
	}
	if(list->length==list->capacity){
		printf("list is full,Insert failed!\n");
		return false;
	}
	if(pos<0||pos>=list->capacity){
		printf("position is invaild,Insert failed!\n");
		return false;
	}
	++list->length;
	for(int i=list->length-1;i>pos;--i){
		list->pList[i]=list->pList[i-1];
	}
	list->pList[pos]=data;
	return true;
}
int seqListDataSearch(seqList list,Type data){
	if(list==NULL){
		printf("list is null,please initalize it,DataSearch failed!\n");
        return false;
	}
	for(int i=0;i<list->length;++i){
		if(list->pList[i]==data){
			return i;
		}
	}
	return -1;
}
Type seqListIndexSearch(seqList list,int pos){
	if(list==NULL){
		printf("list is null,please initalize it,IndexSearch failed!\n");
        return 0;
	}
	if(pos<0||pos>=list->length){
		printf("position is invaild,Insert failed!\n");
		return 0;
	}
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
bool seqListFree(seqList* ppList){
	if(ppList==NULL){
		printf("list is null,Free failed!\n");
        return false;
	}
	free((*ppList)->pList);
	free(*ppList);
	*ppList=NULL;
	return true;
}