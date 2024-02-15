#include <myDS/sort.h>
#include <stdlib.h>

/* 取出数组 p 中，下标为 i 的值 */
#define ARRAY(p,i) (*((char*)(p)+(i)))
/* 取出数组 p 中，下标为 i (元素大小为 size) 的指针 */
#define P_ARRAY(p,i,size) ((char*)(p)+(i)*size)

/* 交换两个变量值，需传入指针和大小 */
static void swap(void* first,void* second,int size)
{
    /* 地址相同立即返回 */
    if(first==second)
        return;
    for(int i=0;i<size;i++){
        /*
            以下宏等同于
            *((char*)first+i)^=*((char*)second+i);
            *((char*)second+i)^=*((char*)first+i);
            *((char*)first+i)^=*((char*)second+i);
        */
        ARRAY(first,i)^=ARRAY(second,i);
        ARRAY(second,i)^=ARRAY(first,i);
        ARRAY(first,i)^=ARRAY(second,i);
    }
}

/* 拷贝 second 位置的值到 first 位置 */
static void copy(void* first,const void* second,int size)
{
    if(!(first&&second))
        return;
    for(int i=0;i<size;i++)
        ARRAY(first,i)=ARRAY(second,i);
}

/* 冒泡排序 */
void bubbleSort(pType array, int n, int size,int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            /*
                等同于
                if(compare((char*)array+j*size,(char*)array+(j+1)*size)>0)
                    swap((char*)array+j*size,(char*)array+(j+1)*size,size);
            */
            if(compare(P_ARRAY(array,j,size),P_ARRAY(array,j+1,size))>0)
                swap(P_ARRAY(array,j,size),P_ARRAY(array,j+1,size),size);
        }
    }
}

/* 选择排序 */
void selectionSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(compare(P_ARRAY(array,min,size),P_ARRAY(array,j,size))>0)
                min=j;
        }
        if(i!=min)
            swap(P_ARRAY(array,i,size), P_ARRAY(array,min,size),size);  
    }
}

/* 插入排序 */
void insertionSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    char* temp=(char*)malloc(size);
    for(int i=1;i<n;i++){
        int j;
        copy(temp,P_ARRAY(array,i,size),size);
        for(j=i;j>0&&(compare(P_ARRAY(array,j-1,size),temp)>0);j--)
            swap(P_ARRAY(array,j,size),P_ARRAY(array,j-1,size),size);
        swap(P_ARRAY(array,j,size),temp,size);
    }
    free(temp);
}

/* 希尔排序 */
void shellSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    char* temp=(char*)malloc(size);
    for(int gap=n>>1;gap>0;gap>>=1){
        for(int i=gap;i<n;i++){
            int j;
            copy(temp,P_ARRAY(array,i,size),size);
            for(j=i-gap;j>=0&&(compare(P_ARRAY(array,j,size),temp)>0);j-=gap)
                swap(P_ARRAY(array,j+gap,size),P_ARRAY(array,j,size),size);
            swap(P_ARRAY(array,j+gap,size),temp,size);
        }
    }
    free(temp);
}

/* 归并排序 */
void mergeSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    char *temp=(char*)malloc(n*size);
    for(int mergeSize=1;mergeSize<n;mergeSize<<=1){
        for(int left=0;left<n;){
            int mid=left+mergeSize-1;
            int right=(mid+mergeSize)<(n-1)?(mid+mergeSize):(n-1);
            if(mid>=n)
                break;
            /* 归并开始 */
            int i=left;
            int p1=left;
            int p2=mid+1;
            while(p1<=mid&&p2<=right){
                if(compare(P_ARRAY(array,p1,size),P_ARRAY(array,p2,size))<=0){
                    copy(P_ARRAY(temp,i,size),P_ARRAY(array,p1,size),size);
                    i++;
                    p1++;
                }else{
                    copy(P_ARRAY(temp,i,size),P_ARRAY(array,p2,size),size);
                    i++;
                    p2++;
                }
            }
            while(p1<=mid){
                copy(P_ARRAY(temp,i,size),P_ARRAY(array,p1,size),size);
                i++;
                p1++;
            }
            while(p2<=right){
                copy(P_ARRAY(temp,i,size),P_ARRAY(array,p2,size),size);
                i++;
                p2++;
            }
            copy(P_ARRAY(array,left,size),P_ARRAY(temp,left,size),(right+1-left)*size);
            /* 归并结束 */
            left=right+1;
        }
        if(mergeSize>n/2)
            break;
    }
    free(temp);
}

/* 归并排序 递归部分 */
static void _mergeRecursive(pType array, char* temp,int left, int right, int size, int (*compare)(const pType, const pType))
{
    if(left==right)
        return;
    int mid=left+((right-left)>>1);
    _mergeRecursive(array,temp,left,mid,size,compare);
    _mergeRecursive(array,temp,mid+1,right,size,compare);
    /* 归并开始 */
    int i=left;
    int p1=left;
    int p2=mid+1;
    while(p1<=mid&&p2<=right){
        if(compare(P_ARRAY(array,p1,size),P_ARRAY(array,p2,size))<=0){
            copy(P_ARRAY(temp,i,size),P_ARRAY(array,p1,size),size);
            i++;
            p1++;
        }else{
            copy(P_ARRAY(temp,i,size),P_ARRAY(array,p2,size),size);
            i++;
            p2++;
        }
    }
    while(p1<=mid){
        copy(P_ARRAY(temp,i,size),P_ARRAY(array,p1,size),size);
        i++;
        p1++;
    }
    while(p2<=right){
        copy(P_ARRAY(temp,i,size),P_ARRAY(array,p2,size),size);
        i++;
        p2++;
    }
    copy(P_ARRAY(array,left,size),P_ARRAY(temp,left,size),(right+1-left)*size);
    /* 归并结束 */
}

/* 归并排序 递归版 */
void mergeSortRecursive(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL&&n<2)
        return;
    char *temp=(char*)malloc(n*size);
    _mergeRecursive(array,temp,0,n-1,size,compare);
    free(temp);
}

/* 快速排序 */
void quickSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    int *lStack=(int*)malloc((n/2)*sizeof(int));
    int *rStack=(int*)malloc((n/2)*sizeof(int));
    int p=-1;
    int pivot,flag;
    //push 0-n-1
    p++;
    lStack[p]=0;
    rStack[p]=n-1;
    while(p>=0){
        pivot=rStack[p];
        int l=lStack[p];
        int r=pivot-1;
        while(l<r){
            //compare to left
            flag=compare(P_ARRAY(array,l,size),P_ARRAY(array,pivot,size));
            if(flag<=0){
                l++;
                continue;
            }
            //compare to right
            while(l<r&&flag>=0){
                flag=compare(P_ARRAY(array,r,size),P_ARRAY(array,pivot,size));
                if(flag>=0)
                    r--;
            }
            swap(P_ARRAY(array,l,size),P_ARRAY(array,r,size),size);
        }
        flag=compare(P_ARRAY(array,l,size),P_ARRAY(array,pivot,size));
        if(l>=r&&flag>0)
            swap(P_ARRAY(array,l,size),P_ARRAY(array,pivot,size),size);
        else
            l++;
        if(l>lStack[p]+1&&l<rStack[p]-1){
            rStack[p+1]=rStack[p];
            rStack[p]=l-1;
            lStack[p+1]=l+1;
            p++;
        }else if(l>lStack[p]+1){
            rStack[p]=l-1;
        }else if(l<rStack[p]-1){
            lStack[p]=l+1;
        }else{
            p--;
        }
    }
    free(lStack);
    free(rStack);
}

/* 快速排序 递归部分 */
static void _quickRecursive(pType array, int left, int right, int size, int (*compare)(const pType, const pType))
{
    if(left>=right)
        return;
    int pivot=right;
    int l=left;
    int r=right-1;
    int flag;
    while(l<r){
        //compare to left
        flag=compare(P_ARRAY(array,l,size),P_ARRAY(array,pivot,size));
        if(flag<=0){
            l++;
            continue;
        }
        //compare to right
        while(l<r&&flag>=0){
            flag=compare(P_ARRAY(array,r,size),P_ARRAY(array,pivot,size));
            if(flag>=0)
                r--;
        }
        swap(P_ARRAY(array,l,size),P_ARRAY(array,r,size),size);
    }
    flag=compare(P_ARRAY(array,l,size),P_ARRAY(array,pivot,size));
    if(l>=r&&flag>0)
        swap(P_ARRAY(array,l,size),P_ARRAY(array,pivot,size),size);
    else
        l++;
    if(left<l-1)
        _quickRecursive(array,left,l-1,size,compare);
    if(l+1<right)
        _quickRecursive(array,l+1,right,size,compare);
}

/* 快速排序 递归版 */
void quickSortRecursive(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    _quickRecursive(array,0,n-1,size,compare);
}

/* 堆排序 堆调整部分 */
static void heapify(pType array, int index, int heapSize, int size, int (*compare)(const pType, const pType))
{
    int pre=index;
    int curr=index*2+1;
    int flag;
    while(curr<=heapSize){
        if(curr+1<=heapSize){
            flag=compare(P_ARRAY(array,curr+1,size),P_ARRAY(array,curr,size));
            if(flag>0)
                curr++;
        }
        flag=compare(P_ARRAY(array,pre,size),P_ARRAY(array,curr,size));
        if(flag>0)
            return;
        else{
            swap(P_ARRAY(array,pre,size),P_ARRAY(array,curr,size),size);
            pre=curr;
            curr=pre*2+1;
        }
    }
}

/* 堆排序 */
void heapSort(pType array, int n, int size, int (*compare)(const pType, const pType))
{
    if(array==NULL)
        return;
    for(int i=n/2-1;i>=0;i--)
        heapify(array,i,n-1,size,compare);
    for(int i=n-1;i>0;i--){
        swap(P_ARRAY(array,0,size),P_ARRAY(array,i,size),size);
        heapify(array,0,i-1,size,compare);
    }
}