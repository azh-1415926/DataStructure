#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <functional>

namespace azh
{
    /*
        T1 为所排序的数据类型
        T2 为用于遍历的迭代器或指针，若未指定为迭代器，则默认为 T1 类型的指针
        T3 为用于存放数据比较函数的容器类型
    */
    template<class T1,class T2=T1*,class T3=std::function<int(const T1&,const T1&)>>
    class Sort
    {
        public:
            Sort()=delete;
            static void bubbleSort(T2 begin,T2 end,T3 comparision);
            static void selectionSort(T2 begin,T2 end,T3 comparision);
            static void insertionSort(T2 begin,T2 end,T3 comparision);
            static void shellSort(T2 begin,T2 end,T3 comparision);
            static void mergeSort(T2 begin,T2 end,T3 comparision);
            static void mergeSortRecursive(T2 begin,T2 end,T3 comparision);
            static void quickSort(T2 begin,T2 end,T3 comparision);
            static void quickSortRecursive(T2 begin,T2 end,T3 comparision);
            static void heapSort(T2 begin,T2 end, T3 comparision);
        
        private:
            static void swap(T2 v1,T2 v2)
            {
                T1 temp=*v1;
                *v1=*v2;
                *v2=temp;
            }
    };

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::bubbleSort(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("bubbleSort");
        for(int i=0;i<len-1;i++)
        {
            for(int j=0;j<len-1-i;j++)
            {
                if(comparision(*(begin+j),*(begin+j+1))>0)
                    swap(begin+j,begin+j+1);
            }
        }
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::selectionSort(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("selectionSort");
        for(int i=0;i<len-1;i++)
        {
            int min=i;
            for(int j=i+1;j<len;j++)
            {
                if(comparision(*(begin+min),*(begin+j))>0)
                    min=j;
            }
            if(i!=min)
                swap(begin+i,begin+min); 
        }
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::insertionSort(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("insertionSort");
        T2 temp=new T1;
        for(int i=1;i<len;i++)
        {
            int j;
            *temp=*(begin+i);
            for(j=i;j>0&&(comparision(*(begin+j-1),*temp)>0);j--)
                swap(begin+j,begin+j-1);
            swap(begin+j,temp);
        }
        delete temp;
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::shellSort(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("shellSort");
        T2 temp=new T1;
        for(int gap=len>>1;gap>0;gap>>=1)
        {
            for(int i=gap;i<len;i++)
            {
                int j;
                *temp=*(begin+i);
                for(j=i-gap;j>=0&&(comparision(*(begin+j),*temp)>0);j-=gap)
                    swap(begin+j+gap,begin+j);
                swap(begin+j+gap,temp);
            }
        }
        delete temp;
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::mergeSort(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("mergeSort");
        T2 temp=new T1[len];
        for(int mergeSize=1;mergeSize<len;mergeSize<<=1)
        {
            for(int left=0;left<len;)
            {
                int mid=left+mergeSize-1;
                int right=(mid+mergeSize)<(len-1)?(mid+mergeSize):(len-1);
                if(mid>=len)
                    break;
                /* 归并开始 */
                int i=left;
                int p1=left;
                int p2=mid+1;
                while(p1<=mid&&p2<=right)
                {
                    if(comparision(*(begin+p1),*(begin+p2))<=0)
                    {
                        *(temp+i)=*(begin+p1);
                        i++;
                        p1++;
                    }
                    else
                    {
                        *(temp+i)=*(begin+p2);
                        i++;
                        p2++;
                    }
                }
                while(p1<=mid)
                {
                    *(temp+i)=*(begin+p1);
                    i++;
                    p1++;
                }
                while(p2<=right)
                {
                    *(temp+i)=*(begin+p2);
                    i++;
                    p2++;
                }
                for(int j=0;j<right+1-left;j++)
                    *(begin+left+j)=*(temp+left+j);
                /* 归并结束 */
                left=right+1;
            }
            if(mergeSize>len/2)
                break;
        }
        delete[] temp;
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::mergeSortRecursive(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("mergeSortRecursive");
        T2 temp=new T1[len];
        static std::function<void(int,int)> _mergeRecursive=[begin,comparision,temp](int left,int right)
        {
            if(left==right)
                return;
            int mid=left+((right-left)>>1);
            _mergeRecursive(left,mid);
            _mergeRecursive(mid+1,right);
            /* 归并开始 */
            int i=left;
            int p1=left;
            int p2=mid+1;
            while(p1<=mid&&p2<=right)
            {
                if(comparision(*(begin+p1),*(begin+p2))<=0)
                {
                    *(temp+i)=*(begin+p1);
                    i++;
                    p1++;
                }
                else
                {
                    *(temp+i)=*(begin+p2);
                    i++;
                    p2++;
                }
            }
            while(p1<=mid)
            {
                *(temp+i)=*(begin+p1);
                i++;
                p1++;
            }
            while(p2<=right)
            {
                *(temp+i)=*(begin+p2);
                i++;
                p2++;
            }
            for(size_t i=0;i<right+1-left;i++)
                *(begin+left+i)=*(temp+left+i);
            /* 归并结束 */
        };
        _mergeRecursive(0,len-1);
        delete[] temp;
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::quickSort(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("quickSort");
        int* lStack=new int[len/2];
        int* rStack=new int[len/2];
        int p=-1;
        int pivot,flag;
        //push 0-len-1
        p++;
        lStack[p]=0;
        rStack[p]=len-1;
        while(p>=0)
        {
            pivot=rStack[p];
            int l=lStack[p];
            int r=pivot-1;
            while(l<r)
            {
                //compare to left
                flag=comparision(*(begin+l),*(begin+pivot));
                if(flag<=0)
                {
                    l++;
                    continue;
                }
                //compare to right
                while(l<r&&flag>=0)
                {
                    flag=comparision(*(begin+r),*(begin+pivot));
                    if(flag>=0)
                        r--;
                }
                swap(begin+l,begin+r);
            }
            flag=comparision(*(begin+l),*(begin+pivot));
            if(l>=r&&flag>0)
                swap(begin+l,begin+pivot);
            else
                l++;
            if(l>lStack[p]+1&&l<rStack[p]-1)
            {
                rStack[p+1]=rStack[p];
                rStack[p]=l-1;
                lStack[p+1]=l+1;
                p++;
            }  
            else if(l>lStack[p]+1)
                rStack[p]=l-1;
            else if(l<rStack[p]-1)
                lStack[p]=l+1;
            else
                p--;
        }
        delete[] lStack;
        delete[] rStack;
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::quickSortRecursive(T2 begin,T2 end,T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("quickSortRecursive");
        static std::function<void(int,int)> _quickRecursive=[begin,comparision](int left,int right)
        {
            if(left>=right)
                return;
            int pivot=right;
            int l=left;
            int r=right-1;
            int flag;
            while(l<r)
            {
                //compare to left
                flag=comparision(*(begin+l),*(begin+pivot));
                if(flag<=0)
                {
                    l++;
                    continue;
                }
                //compare to right
                while(l<r&&flag>=0)
                {
                    flag=comparision(*(begin+r),*(begin+pivot));
                    if(flag>=0)
                        r--;
                }
                swap(begin+l,begin+r);
            }
            flag=comparision(*(begin+l),*(begin+pivot));
            if(l>=r&&flag>0)
                swap(begin+l,begin+pivot);
            else
                l++;
            if(left<l-1)
                _quickRecursive(left,l-1);
            if(l+1<right)
                _quickRecursive(l+1,right);
        };
        _quickRecursive(0,len-1);
    }

    template<class T1,class T2,class T3>
    void Sort<T1,T2,T3>::heapSort(T2 begin,T2 end, T3 comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("heapSort");
        static std::function<void(int,int)> heapify=[begin,comparision](int index, int heapSize)
        {
            int pre=index;
            int curr=index*2+1;
            int flag;
            while(curr<=heapSize)
            {
                if(curr+1<=heapSize)
                {
                    flag=comparision(*(begin+curr+1),*(begin+curr));
                    if(flag>0)
                        curr++;
                }
                flag=comparision(*(begin+pre),*(begin+curr));
                if(flag>0)
                    return;
                else
                {
                    swap(begin+pre,begin+curr);
                    pre=curr;
                    curr=pre*2+1;
                }
            }
        };
        for(int i=len/2-1;i>=0;i--)
            heapify(i,len-1);
        for(int i=len-1;i>0;i--)
        {
            swap(begin,begin+i);
            heapify(0,i-1);
        }
    }
}

#endif /* SORT_H */