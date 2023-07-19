#include <stdio.h>
#include <time.h>
#include "sort.h"
#define COUNT 1000000
#define SIZE sizeof(int)
#define TEST_CASE int array[]={1,7,8,2,4,6,3,5,9,10}
#define SHOW_CASE show(array,sizeof(array)/sizeof(int))

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
    TEST_CASE;
    if(count==0)
        SHOW_CASE;
    bubbleSort(array,sizeof(array)/sizeof(int),sizeof(int),compare);
    if(count==COUNT-1)
        SHOW_CASE;
}

void func2(int count)
{
    TEST_CASE;
    if(count==0)
        SHOW_CASE;
    selectionSort(array,sizeof(array)/sizeof(int),sizeof(int),compare);
    if(count==COUNT-1)
        SHOW_CASE;
}

void func3(int count)
{
    TEST_CASE;
    if(count==0)
        SHOW_CASE;
    insertionSort(array,sizeof(array)/sizeof(int),sizeof(int),compare);
    if(count==COUNT-1)
        SHOW_CASE;
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
    printf("InsectionSort\n");
    countTime(COUNT,func3);
    return 0;
}