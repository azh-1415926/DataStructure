#include <stdio.h>
#include <time.h>
#include "sort.h"
#define COUNT 1000000
#define SIZE sizeof(int)

int compare(void* first,void* second)
{
    return *(int*)first-*(int*)second;
}

void show(int* array,int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",array[i]);
    printf("\n");
}

void func1(int count)
{
    int array[]={1,7,8,2,4,6,3,5,9,10};
    if(count==0)
        show(array,sizeof(array)/sizeof(int));
    bubbleSort(array,sizeof(array)/sizeof(int),sizeof(int),compare);
    if(count==COUNT-1)
        show(array,sizeof(array)/sizeof(int));
}

void func2(int count)
{
    int array[]={1,7,8,2,4,6,3,5,9,10};
    if(count==0)
        show(array,sizeof(array)/sizeof(int));
    selectionSort(array,sizeof(array)/sizeof(int),sizeof(int),compare);
    if(count==COUNT-1)
        show(array,sizeof(array)/sizeof(int));
}

void countTime(int count,void(*func)(int))
{
    clock_t startTime,endTime;
    double costTime=0.0;
    startTime=clock();
    for(int i=0;i<count;i++){
        func(i);
    }
    endTime=clock();
    costTime=(endTime-startTime)/1000.0;
    printf("CostTime:%.3lf\n",costTime);
}

int main(){
    printf("BubbleSort\n");
    countTime(COUNT,func1);
    printf("SelectionSort\n");
    countTime(COUNT,func2);
    return 0;
}