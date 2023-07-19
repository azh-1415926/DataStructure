#include "sort.h"

static void swap(void* first,void* second,int size)
{
    if(first==second)
        return;
    for(int i=0;i<size;i++){
        *((char*)first+i)^=*((char*)second+i);
        *((char*)second+i)^=*((char*)first+i);
        *((char*)first+i)^=*((char*)second+i);
    }
}
void bubbleSort(eleType array, int n, int size,int (*compare)(const eleType, const eleType))
{
    if(array==NULL)
        return;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(compare((char*)array+j*size,(char*)array+(j+1)*size)>0)
                swap((char*)array+j*size,(char*)array+(j+1)*size,size);
        }
    }
}

void selectionSort(eleType array, int n, int size, int (*compare)(const eleType, const eleType))
{
    if(array==NULL)
        return;
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i;j<n-1;j++){
            if(compare((char*)array+min*size,(char*)array+j*size)>0)
                min=j;
        }
        if(i!=min)
            swap((char*)array+i*size,(char*)array+min*size,size);
    }
}