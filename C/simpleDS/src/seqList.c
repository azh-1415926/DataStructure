#include <simpleDS/seqList.h>
#include <stdlib.h>

void seqListInitalize(seqList* ppList,int capacity)
{
    *ppList=(seqList)malloc(sizeof(struct seqList));
	(*ppList)->pList=malloc(sizeof(void*)*capacity);
	(*ppList)->capacity=capacity;
	(*ppList)->length=0;
}

void seqListFree(seqList* ppList)
{
	free((*ppList)->pList);
	free(*ppList);
	*ppList=NULL;
}

void seqListInsert(seqList list,void* data,int pos)
{
	if(pos<0||pos>=list->capacity)
		return;
	++list->length;
	for(int i=list->length-1;i>pos;--i){
		list->pList[i]=list->pList[i-1];
	}
	list->pList[pos]=data;
}

void* seqListErase(seqList list,int pos)
{
	if(pos<0||pos>=list->capacity)
		return NULL;
	--list->length;
	void* data=list->pList[pos];
	for(int i=pos;i<list->length;--i)
		list->pList[i]=list->pList[i+1];
	return data;
}

void* seqListIndexSearch(seqList const list,int pos)
{
	if(pos<0||pos>=list->length)
		return NULL;
	return list->pList[pos];
}

int seqListDataSearch(seqList list,void* const data,bool(*compare)(void*,void* const))
{
	for(int i=0;i<list->length;++i)
		if(compare(list->pList[i],data))
			return i;
	return -1;
}
seqList seqListCombine(seqList firstList,seqList const endList)
{
	seqList list;
	seqListInitalize(&list,firstList->length+endList->length);
	for(int i=0,j=0;i<list->capacity;++i){
		if(i<firstList->capacity)
			list->pList[i]=firstList->pList[i];
		else
			list->pList[i]=endList->pList[j++];
	}
	list->length=list->capacity;
	return list;
}

seqList seqListCombineNoRepeat(seqList firstList,seqList const endList,bool(*compare)(void*,void* const))
{
	seqList list=seqListCombine(firstList,endList);
	for(int i=0;i<list->length-1;++i){
		for(int j=i+1;j<list->length;++j){
			if(compare(list->pList[i],list->pList[j])){
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