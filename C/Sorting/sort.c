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
        for(int j=i+1;j<n;j++){
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

void shellSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int gap=n>>1;gap>0;gap>>=1){
        for(int i=gap;i<n;i++){
            int j;
            char temp[size];
            // copy(temp,(char*)array+i*size,size);
            // for(j=i-gap;j>=0&&(compare((char*)array+j*size,temp)>0);j-=gap)
            //     swap((char*)array+(j+gap)*size,(char*)array+j*size,size);
            // swap((char*)array+(j+gap)*size,temp,size);
            copy(temp,P_ARRAY(array,i,size),size);
            for(j=i-gap;j>=0&&(compare(P_ARRAY(array,j,size),temp)>0);j-=gap)
                swap(P_ARRAY(array,j+gap,size),P_ARRAY(array,j,size),size);
            swap(P_ARRAY(array,j+gap,size),temp,size);
        }
    }
}

void mergeSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int mergeSize=1;mergeSize<n;mergeSize<<=1){
        for(int left=0;left<n;){
            int mid=left+mergeSize-1;
            int right=(mid+mergeSize)<(n-1)?(mid+mergeSize):(n-1);
            if(mid>=n)
                break;
            //merge start
            if(right+1-left<2)
                break;
            char temp[(right+1-left)*size];
            int i=0;
            int p1=left;
            int p2=mid+1;
            while(p1<=mid&&p2<=right){
                // if(compare((char*)array+p1*size,(char*)array+p2*size)<=0){
                if(compare(P_ARRAY(array,p1,size),P_ARRAY(array,p2,size))<=0){
                    // copy(temp,(char*)array+p1*size,size);
                    copy(P_ARRAY(temp,i,size),P_ARRAY(array,p1,size),size);
                    i++;
                    p1++;
                }else{
                    // copy(temp,(char*)array+p2*size,size);
                    copy(P_ARRAY(temp,i,size),P_ARRAY(array,p2,size),size);
                    i++;
                    p2++;
                }
            }
            while(p1<=mid){
                // copy(temp,(char*)array+p1*size,size);
                copy(P_ARRAY(temp,i,size),P_ARRAY(array,p1,size),size);
                i++;
                p1++;
            }
            while(p2<=right){
                // copy(temp,(char*)array+p2*size,size);
                copy(P_ARRAY(temp,i,size),P_ARRAY(array,p2,size),size);
                i++;
                p2++;
            }
            // copy((char*)array+left*size,temp,size);
            copy(P_ARRAY(array,left,size),P_ARRAY(temp,0,size),sizeof(temp));
            //merge end
            left=right+1;
        }
        if(mergeSize>n/2)
            break;
    }
}