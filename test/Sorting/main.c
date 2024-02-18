#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <myDS/sort.h>
#include <myTools/sortCase.h>
#include <myTools/log.h>

/*
    测试数据参数，我们以 int 类型数据为例
    COUNT 测试排序次数
    SIZE 排序数据的大小
    N 排序数组元素个数
    LEFT_RANGE 和 RIGHT_RANGE 为 int 数据的范围，[LEFT_RANGE,RIGHT_RANGE)
*/
#define COUNT 1000000
#define SIZE sizeof(int)
#define N 15
#define LEFT_RANGE 0
#define RIGHT_RANGE 100

#define SORT_FUNC(func) \
    func(array,N,SIZE,compare)

/* 测试排序的数组、用于还原的备用数组 */
static int* array=NULL;
static int* arrayCopy=NULL;
static char currFunc[100];

/* 比较两个数据的大小关系，first > second 返回大于 0，first < second 返回小于 0，相等返回 0 */
int compare(const eleType first,const eleType second)
{
    return *(int*)first-*(int*)second;
}

/* 显示数据函数 */
void printData(eleType data)
{
    printf("%d ",*(int*)data);
}

/* 用于初始化数据的函数 */
void initalData(eleType data,int num)
{
    *(int*)data=num%(RIGHT_RANGE-LEFT_RANGE)+LEFT_RANGE;
}

/* 导出测试数据 */
void export(const char* log)
{
    char buf[4096];
    memset(buf,0,sizeof(buf));
    int index=0;
    sprintf(buf,"Size   : %d\nData   : ",N);
    if(N<=50){
        for(int i=0;i<N-1;i++){
            index=strlen(buf);
            sprintf(buf+index,"%d ",arrayCopy[i]);
        }
        index=strlen(buf);
        sprintf(buf+index,"%d\n",arrayCopy[N-1]);
    }else{
        index=strlen(buf);
        sprintf(buf+index,"%s\n","mass of data");
    }
    index=strlen(buf);
    sprintf(buf+index,"Count  : %d\n%s",COUNT,log);
    printf("%s\n",buf);
    exportLog("sort.log",buf);
}

void sortBy(int i)
{
    switch (i)
    {
    case 0:
        SORT_FUNC(qsort);
        break;

    case 1:
        SORT_FUNC(bubbleSort);
        break;
    
    case 2:
        SORT_FUNC(selectionSort);
        break;

    case 3:
        SORT_FUNC(insertionSort);
        break;

    case 4:
        SORT_FUNC(shellSort);
        break;

    case 5:
        SORT_FUNC(mergeSort);
        break;

    case 6:
        SORT_FUNC(mergeSortRecursive);
        break;

    case 7:
        SORT_FUNC(quickSort);
        break;

    case 8:
        SORT_FUNC(quickSortRecursive);
        break;

    case 9:
        SORT_FUNC(heapSort);
        break;

    default:
        break;
    }
}

/* 计时第 i 个排序方式，执行 count 次数的时间 */
double countTime(int i,int count)
{
    clock_t startTime,endTime;
    double costTime=0.0;
    startTime=clock();
    for(int j=0;j<count;j++)
    {
        memcpy(array,arrayCopy,N*SIZE);
        sortBy(i);
    }
    endTime=clock();
    costTime=(endTime-startTime)/1000.0;
    printf("Sorting by : %-20s CostTime : %.3lfs\n",currFunc,costTime);
    return costTime;
}

/* 从 0-n 测试排序函数，以相同数据序列测试 */
void testAllCase(char** sortInfo,int n)
{
    char log[4096]={0};
    char buf[50]={0};
    double costTime=0.0;
    printf("Array : ");
    showCase((void*)arrayCopy,N,printData);
    for(int i=0;i<n;i++){
        sprintf(currFunc,sortInfo[i]);
        costTime=countTime(i,COUNT);
        if(!verifyCase((void*)array,N,compare))
        {
            showCase((void*)array,N,printData);
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

/* 测试第 i 个排序 count 次随机数据 */
void testOneCase(char* sortName,int i,int count)
{
    printf("------ Name : %s Count : %d ------\n",sortName,count);
    for(int i=0;i<count;i++){
        sprintf(currFunc,sortName);
        memcpy(array,arrayCopy,N*SIZE);
        countTime(i,COUNT);
        printf("Array : ");
        showCase((void*)arrayCopy,N,printData);
        printf("Sorted : ");
        showCase((void*)array,N,printData);
        if(!verifyCase((void*)array,N,compare))
        {
            printf("%s error!",sortName);
            free(array);
            free(arrayCopy);
            exit(1);
        }
        createCase((void*)arrayCopy,N);
        // createCaseNoRepeat(arrayCopy,N,LEFT_RANGE,RIGHT_RANGE);
    }
}

int main()
{
    char* sortInfo[]=
    {
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
    double costTime=0.0;
    array=malloc(N*SIZE);
    arrayCopy=malloc(N*SIZE);
    initalCase(initalData);
    createCase((void*)arrayCopy,N);
    // createCaseNoRepeat(arrayCopy,N,LEFT_RANGE,RIGHT_RANGE);
    testAllCase(sortInfo,10);
    testOneCase(sortInfo[9],9,10);
    free(array);
    free(arrayCopy);
    return 0;
}