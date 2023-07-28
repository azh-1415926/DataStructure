#include "testCase.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static void(*Inital)(void*,int)=NULL;

void initalCase(void (*inital)(void*,int))
{
    Inital=inital;
    srand(time(NULL));
}

eleType *createCase(eleType *array, int n)
{
    int i=0;
    int num;
    while(i<n){
        num=rand();
        if(Inital)
            Inital(&array[i],num);
        i++;
    }
    return array;
}

eleType *createCaseNoRepeat(eleType *array, int n)
{
    int index;
    memset(array,0,n*sizeof(eleType));
    for(int i=0;i<n;i++){
        index=rand()%n;
        while(array[index]!=0)
            index=rand()%n;
        array[index]=i+1;
    }
    return array;
}

void showCase(eleType *array, int n, void (*show)(void *))
{
    for(int i=0;i<n;i++)
        show(&array[i]);
    printf("\n");
}

bool verifyCase(eleType *array, int n, int (*compare)(void *, void *))
{
    int flag;
    for(int i=0;i<n-1;i++){
        flag=compare(&array[i],&array[i+1]);
        if(flag>0)
            return false;
    }
    return true;
}