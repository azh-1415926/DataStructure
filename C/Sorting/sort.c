#include "sort.h"
#define ARRAY(p,i) (*((char*)(p)+(i)))
#define P_ARRAY(p,i,size) ((char*)(p)+(i)*size)

static void swap(void* first,void* second,int size)
{
    if(first==second)
        return;
    for(int i=0;i<size;i++){
        // *((char*)first+i)^=*((char*)second+i);
        // *((char*)second+i)^=*((char*)first+i);
        // *((char*)first+i)^=*((char*)second+i);
        ARRAY(first,i)^=ARRAY(second,i);
        ARRAY(second,i)^=ARRAY(first,i);
        ARRAY(first,i)^=ARRAY(second,i);
    }
}

static void copy(void* first,const void* second,int size)
{
    if(!(first&&second))
        return;
    for(int i=0;i<size;i++)
        // *((char*)first+i)=*((char*)second+i);
        ARRAY(first,i)=ARRAY(second,i);
}

void bubbleSort(pType array, int n, int size,int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            // if(compare((char*)array+j*size,(char*)array+(j+1)*size)>0)
            //     swap((char*)array+j*size,(char*)array+(j+1)*size,size);
            if(compare(P_ARRAY(array,j,size),P_ARRAY(array,j+1,size))>0)
                swap(P_ARRAY(array,j,size),P_ARRAY(array,j+1,size),size);
        }
    }
}

void selectionSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i;j<n-1;j++){
            // if(compare((char*)array+min*size,(char*)array+j*size)>0)
            if(compare(P_ARRAY(array,min,size),P_ARRAY(array,j,size))>0)
                min=j;
        }
        if(i!=min)
            // swap((char*)array+i*size,(char*)array+min*size,size);
            swap(P_ARRAY(array,i,size), P_ARRAY(array,min,size),size);  
    }
}

void insertionSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int i=1;i<n;i++){
        int j;
        char temp[size];
        // copy(temp,(char*)array+i*size,size);
        // for(j=i;j>0&&(compare((char*)array+(j-1)*size,temp)>0);j--)
        //     swap((char*)array+j*size,(char*)array+(j-1)*size,size);
        // swap((char*)array+j*size,temp,size);
        copy(temp,P_ARRAY(array,i,size),size);
        for(j=i;j>0&&(compare(P_ARRAY(array,j-1,size),temp)>0);j--)
            swap(P_ARRAY(array,j,size),P_ARRAY(array,j-1,size),size);
        swap(P_ARRAY(array,j,size),temp,size);
    }
}