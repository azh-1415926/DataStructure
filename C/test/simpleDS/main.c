#include <simpleDS/seqList.h>
#include <simpleDS/seqStack.h>
#include <simpleDS/seqQueue.h>
#include <simpleDS/linkList.h>
#include <simpleDS/linkStack.h>
#include <simpleDS/linkQueue.h>
#include <myTools/sortCase.h>

#define N 100
#define COUNT 10000
#define LeftRange 10
#define RightRange 1000

int compare(const eleType first,const eleType second)
{
    return *(int*)first-*(int*)second;
}

void test1()
{
    seqList list;
    seqListInitalize(&list,N);
    void* array=(int*)malloc(sizeof(int)*N);
    createCaseNoRepeat(array,N,LeftRange,RightRange);
    for(int i=0;i<N;i++)
    {
        seqListInsert(list,(void*)&((int*)array)[i],i);
        if(*(int*)seqListIndexSearch(list,i)!=((int*)array)[i])
        {
            printf("error,index of %d is %d,but get data:%d\n",i,((int*)array)[i],*(int*)seqListIndexSearch(list,i));
            free(array);
            seqListFree(&list);
            return;
        }
    }
    printf("Test for seqList.\tInsert,IndexSearch success!\n");
    for(int i=0;i<N;i++)
    {
        if(seqListDataSearch(list,&((int*)array)[i],compare)!=i)
        {
            printf("error,%d's index is %d,but get index:%d\n",i,((int*)array)[i],seqListDataSearch(list,(void*)&((int*)array)[i],compare));
            free(array);
            seqListFree(&list);
            return;
        }
    }
    printf("Test for seqList.\tDataSearch success!\n");
    seqList temp;
    seqListInitalize(&temp,N);
    for(int i=0;i<N;i++)
        seqListInsert(temp,(void*)&((int*)array)[N-1-i],i);
    seqList temp2=seqListCombine(list,temp);
    for(int i=0;i<2*N;i++)
    {
        if(i<N)
        {
            if(*(int*)seqListIndexSearch(temp2,i)!=*(int*)seqListIndexSearch(temp,N-1-i))
            {
                printf("error,index of %d is %d,but get data:%d\n",i,((int*)array)[i],*(int*)seqListIndexSearch(temp2,i));
                free(array);
                seqListFree(&list);
                seqListFree(&temp);
                seqListFree(&temp2);
                return;
            }
        }
        else
        {
            if(*(int*)seqListIndexSearch(temp2,i)!=*(int*)seqListIndexSearch(temp,i-N))
            {
                printf("error,index of %d is %d,but get data:%d\n",i,((int*)array)[i-N],*(int*)seqListIndexSearch(temp2,i));
                free(array);
                seqListFree(&list);
                seqListFree(&temp);
                seqListFree(&temp2);
                return;
            }
        }
    }
    printf("Test for seqList.\tCombine success!\n");
    for(int i=0;i<N;i++)
        seqListErase(temp2,i);
    seqListFree(&temp);
    temp=seqListCombineNoRepeat(temp2,list,compare);
    for(int i=0;i<N;i++)
    {
        if(*(int*)seqListIndexSearch(temp,i)!=*(int*)seqListIndexSearch(temp2,i))
        {
            printf("error,index of %d is %d,but get data:%d\n",i,((int*)array)[i],*(int*)seqListIndexSearch(temp,i));
            free(array);
            seqListFree(&list);
            seqListFree(&temp);
            seqListFree(&temp2);
            return;
        }
    }
    printf("Test for seqList.\tErase,CombineNoRepeat success!\n");
    free(array);
    seqListFree(&list);
    seqListFree(&temp);
    seqListFree(&temp2);
}

int main()
{
    test1();
    return 0;
}