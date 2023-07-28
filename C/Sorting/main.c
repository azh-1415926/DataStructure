#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "sort.h"
#include "testCase.h"

#define COUNT 10000000
#define SIZE sizeof(int)
#define N 20
#define LEFT_RANGE 0
#define RIGHT_RANGE 100

static int* array=NULL;
static int* arrayCopy=NULL;
static char currFunc[100];

int compare(void* first,void* second)
{
    return *(int*)first-*(int*)second;
}

void showData(void* data)
{
    printf("%d ",*(int*)data);
}

void inital(void* data,int num)
{
    *(int*)data=num%(RIGHT_RANGE-LEFT_RANGE)+LEFT_RANGE;
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
    printf("%s\nSize   : %d\nData   : ",str,N);
    showCase(arrayCopy,N,showData);
    printf("Sorted : ");
    showCase(array,N,showData);
    printf("Count:%d\n",COUNT);
    printf("%s",log);
    //save
    fprintf(f,"%s\nSize   : %d\nData   : ",str,N);
    for(int i=0;i<N-1;i++)
        fprintf(f,"%d ",arrayCopy[i]);
    fprintf(f,"%d\nSorted : ",arrayCopy[N-1]);
    for(int i=0;i<N-1;i++)
        fprintf(f,"%d ",array[i]);
    fprintf(f,"%d\nCount:%d\n%s---END---\n",array[N-1],COUNT,log);
}

void func0()
{
    qsort(array,N,SIZE,compare);
}

void func1()
{
    bubbleSort(array,N,SIZE,compare);
}

void func2()
{
    selectionSort(array,N,SIZE,compare);
}

void func3()
{
    insertionSort(array,N,SIZE,compare);
}

void func4()
{
    shellSort(array,N,SIZE,compare);
}

void func5()
{
    mergeSort(array,N,SIZE,compare);
}

void func6()
{
    mergeSortRecursive(array,N,SIZE,compare);
}

void func7()
{
    quickSort(array,N,SIZE,compare);
}

void func8()
{
    quickSortRecursive(array,N,SIZE,compare);
}

void func9()
{
    heapSort(array,N,SIZE,compare);
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
    printf("Sorting by : %-20s CostTime : %.3lfs\n",currFunc,costTime);
    return costTime;
}

void testAllCase(char** sortInfo,void(**funcInfo)(int),int n)
{
    char log[4096]={0};
    char buf[50]={0};
    double costTime=0.0;
    printf("Array : ");
    showCase(arrayCopy,N,showData);
    for(int i=0;i<n;i++){
        sprintf(currFunc,sortInfo[i]);
        memcpy(array,arrayCopy,N*SIZE);
        costTime=countTime(COUNT,funcInfo[i]);
        //showCase(arrayCopy,N,showData);
        //showCase(array,N,showData);
        if(!verifyCase(array,N,compare)){
            showCase(array,N,showData);
            printf("%s error!",sortInfo[i]);
            free(array);
            free(arrayCopy);
            exit(1);
        }
        sprintf(buf,"%-20s %.3lfs\n",sortInfo[i],costTime);
        strcat(log,buf);
    }
    export(log);
}

void testOneCase(char* sortName,void(*func)(int),int count)
{
    printf("------ Name : %s Count : %d ------\n",sortName,count);
    for(int i=0;i<count;i++){
        sprintf(currFunc,sortName);
        memcpy(array,arrayCopy,N*SIZE);
        countTime(COUNT,func);
        printf("Array : ");
        showCase(arrayCopy,N,showData);
        printf("Sorted : ");
        showCase(array,N,showData);
        if(!verifyCase(array,N,compare)){
            printf("%s error!",sortName);
            free(array);
            free(arrayCopy);
            exit(1);
        }
        createCase(arrayCopy,N);
    }
}

int main(){
    char* sortInfo[]={
        "qsort",
        "BubbleSort",
        "SelectionSort",
        "InsectionSort",
        "ShellSort",
        "MergeSort",
        "MergeSortRecursive",
        "QuickSort",
        "QuickSortRecursive",
        "HeapSort"
    };
    int n=sizeof(sortInfo)/sizeof(char*);
    void(*funcInfo[n])(int);
    funcInfo[0]=func0;
    funcInfo[1]=func1;
    funcInfo[2]=func2;
    funcInfo[3]=func3;
    funcInfo[4]=func4;
    funcInfo[5]=func5;
    funcInfo[6]=func6;
    funcInfo[7]=func7;
    funcInfo[8]=func8;
    funcInfo[9]=func9;
    double costTime=0.0;
    array=malloc(N*SIZE);
    arrayCopy=malloc(N*SIZE);
    initalCase(inital);
    createCase(arrayCopy,N);
    // createCaseNoRepeat(arrayCopy,N);
    testAllCase(sortInfo,funcInfo,n);
    // testOneCase(sortInfo[2],funcInfo[2],10);
    free(array);
    free(arrayCopy);
    return 0;
}