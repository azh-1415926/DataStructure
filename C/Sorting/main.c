#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "sort.h"
#define COUNT 1000000
#define SIZE sizeof(int)
#define N 15

//#define JUDGE
#define RANDOM

#define RANDOM_CASE \
    if(randomFlag){  \
        srand(time(NULL));  \
        int index=0;    \
        for(int i=0;i<N;i++){   \
            index=rand()%N;    \
            while(arrayCopy[index]!=0)  \
                index=rand()%N;    \
            arrayCopy[index]=i+1; \
        }   \
    }
#define RESET_CASE \
    for(int i=0;i<N;i++){   \
        array[i]=arrayCopy[i];  \
    }
#define SHOW_CASE show(array,N)
#define JUDGE_CASE \
    if(judgeFlag){   \
        if(!judge(array,N)) \
                printf("error!");   \
    }

#ifdef JUDGE
static int judgeFlag=1;
#endif

#ifndef JUDGE
static int judgeFlag=0;
#endif

#ifdef RANDOM
static int randomFlag=1;
static int array[N]={0};
static int arrayCopy[N]={0};
#endif

#ifndef RANDOM
static int randomFlag=0;
#if 1
static int array[]={1,7,8,2,4,6,3,5,9,10};
static int arrayCopy[]={1,7,8,2,4,6,3,5,9,10};
#endif

#if 0
static int array[]={10,9,8,7,6,5,4,3,2,1};
static int arrayCopy[]={10,9,8,7,6,5,4,3,2,1};
#endif

#if 0
static int array[]={1,2,3,4,5,6,7,8,9,10};
static int arrayCopy[]={1,2,3,4,5,6,7,8,9,10};
#endif

#endif

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

bool judge(int* array,int n)
{
    for(int i=0;i<n;i++){
        if(array[i]!=i+1)
            return false;
    }
    return true;
}

void export(const char* log)
{
    time_t now=time(NULL);
    struct tm* time;
    time=localtime(&now);
    char* format="%Y-%m-%d %H:%M:%S";
    char str[20];
    strftime(str,sizeof(str),format,time);
    FILE* f=NULL;
    f=fopen("log.txt","a");
    if(f==NULL)
        return;
    //show
    printf("%s\nSize:%d\nData:",str,N);
    show(arrayCopy,N);
    printf("Count:%d\n",COUNT);
    printf("%s",log);
    //save
    fprintf(f,"%s\nSize:%d\nData:",str,N);
    for(int i=0;i<N-1;i++)
        fprintf(f,"%d ",arrayCopy[i]);
    fprintf(f,"%d\nCount:%d\n%s---END---\n",arrayCopy[N-1],COUNT,log);
}

void func1(int count)
{
    RESET_CASE;
    if(count==0)
        SHOW_CASE;
    bubbleSort(array,N,SIZE,compare);
    if(count==COUNT-1)
        SHOW_CASE;
    JUDGE_CASE;
}

void func2(int count)
{
    RESET_CASE;
    if(count==0)
        SHOW_CASE;
    selectionSort(array,N,SIZE,compare);
    if(count==COUNT-1)
        SHOW_CASE;
    JUDGE_CASE;
}

void func3(int count)
{
    RESET_CASE;
    if(count==0)
        SHOW_CASE;
    insertionSort(array,N,SIZE,compare);
    if(count==COUNT-1)
        SHOW_CASE;
    JUDGE_CASE;
}

void func4(int count)
{
    RESET_CASE;
    if(count==0)
        SHOW_CASE;
    shellSort(array,N,SIZE,compare);
    if(count==COUNT-1)
        SHOW_CASE;
    JUDGE_CASE;
}

void func5(int count)
{
    RESET_CASE;
    if(count==0)
        SHOW_CASE;
    mergeSort(array,N,SIZE,compare);
    if(count==COUNT-1)
        SHOW_CASE;
    JUDGE_CASE;
}

void func6(int count)
{
    RESET_CASE;
    if(count==0)
        SHOW_CASE;
    mergeSortRecursive(array,N,SIZE,compare);
    if(count==COUNT-1)
        SHOW_CASE;
    JUDGE_CASE;
}

double countTime(int count,void(*func)(int))
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
    return costTime;
}

int main(){
    RANDOM_CASE;
    char log[4096]={0};
    char buf[50]={0};
    char* sortInfo[]={
        "BubbleSort",
        "SelectionSort",
        "InsectionSort",
        "ShellSort",
        "MergeSort",
        "MergeSortRecursive"
    };
    int n=sizeof(sortInfo)/sizeof(char*);
    void(*funcInfo[n])(int);
    funcInfo[0]=func1;
    funcInfo[1]=func2;
    funcInfo[2]=func3;
    funcInfo[3]=func4;
    funcInfo[4]=func5;
    funcInfo[5]=func6;
    double costTime=0.0;
    for(int i=0;i<n;i++){
        costTime=countTime(COUNT,funcInfo[i]);
        sprintf(buf,"%s %.3lf\n",sortInfo[i],costTime);
        strcat(log,buf);
    }
    export(log);
    return 0;
}