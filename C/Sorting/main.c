#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#define COUNT 1000000
#define SIZE sizeof(int)
#define TEST_CASE int array[]={1,7,8,2,4,6,3,5,9,10}
//#define TEST_CASE int array[]={10,9,8,7,6,5,4,3,2,1}
//#define TEST_CASE int array[]={1,2,3,4,5,6,7,8,9,10}
#define N 10
#define RANDOM_CASE \
    int array[N]={0};   \
    srand(time(NULL));  \
    int index=0;    \
    for(int i=0;i<N;i++){   \
        index=rand()%10;    \
        while(array[index]!=0)  \
            index=rand()%10;    \
        array[index]=i+1; \
    }   \
    
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