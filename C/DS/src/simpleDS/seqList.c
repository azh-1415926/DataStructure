#include <simpleDS/seqList.h>
#include <stdlib.h>

seqList seqListInitalize(seqList* pList,int capacity)
{
    *pList=(seqList)malloc(sizeof(struct seqList));
	(*pList)->data=malloc(sizeof(eleType)*capacity);
	(*pList)->capacity=capacity;
	(*pList)->length=0;
}

void seqListFree(seqList* pList)
{
	free((*pList)->data);
	free(*pList);
	*pList=(eleType)0;
}

void seqListInsert(seqList list,const eleType data,int pos)
{
	if(pos<0||pos>=list->capacity)
		return;
	++list->length;
	for(int i=list->length-1;i>pos;--i)
		list->data[i]=list->data[i-1];
	list->data[pos]=data;
}

eleType seqListErase(seqList list,int pos)
{
	if(pos<0||pos>=list->capacity)
		return (eleType)0;
	--list->length;
	eleType data=list->data[pos];
	for(int i=pos;i<list->length;++i)
		list->data[i]=list->data[i+1];
	return data;
}

eleType seqListIndexSearch(const seqList list,int pos)
{
	if(pos<0||pos>=list->length)
		return (eleType)0;
	return list->data[pos];
}

int seqListDataSearch(const seqList list,const eleType data,int (*compare)(const eleType,const eleType))
{
	for(int i=0;i<list->length;++i)
		if(!compare(list->data[i],data))
			return i;
	return -1;
}
seqList seqListCombine(seqList firstList,const seqList endList)
{
	
	if(firstList==(eleType)0)
		return endList;
	if(endList==(eleType)0)
		return firstList;
	seqList list;
	seqListInitalize(&list,firstList->length+endList->length);
	for(int i=0,j=0;i<list->capacity;++i)
	{
		if(i<firstList->capacity)
			list->data[i]=firstList->data[i];
		else
			list->data[i]=endList->data[j++];
	}
	list->length=list->capacity;
	return list;
}

seqList seqListCombineNoRepeat(seqList firstList,const seqList endList,int (*compare)(const eleType,const eleType))
{
	seqList list=seqListCombine(firstList,endList);
	for(int i=0;i<list->length-1;++i)
	{
		for(int j=i+1;j<list->length;++j)
		{
			if(!compare(list->data[i],list->data[j]))
			{
				for(int k=j;k<list->length-1;k++)
					list->data[k]=list->data[k+1];
				--j;
				--list->length;
			}
		}
	}
	return list;
}