#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <functional>

namespace azh
{
    /* T1 为所排序的数据类型、T2 为用于遍历的迭代器或指针，若未指定为迭代器，则默认为 T1 类型的指针 */
    template<class T1,class T2=T1*>
    class Sort
    {
        public:
            Sort()=delete;
            static void bubbleSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void selectionSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void insertionSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void shellSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void mergeSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void mergeSortRecursive(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void quickSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void quickSortRecursive(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision);
            static void heapSort(T2 begin,T2 end, std::function<bool(const T1&,const T1&)> comparision);
        
        private:
            static void swap(T2 v1,T2 v2)
            {
                T1 temp=*v1;
                *v1=*v2;
                *v2=temp;
            }
    };

    template<class T1,class T2>
    void Sort<T1,T2>::bubbleSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("bubbleSort");
        for(int i=0;i<len-1;i++)
        {
            for(int j=0;j<len-1-i;j++)
            {
                if(comparision(*(begin+j),*(begin+j+1)))
                    swap(begin+j,begin+j+1);
            }
        }
    }

    template<class T1,class T2>
    void Sort<T1,T2>::selectionSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("selectionSort");
        for(int i=0;i<len-1;i++)
        {
            int min=i;
            for(int j=i+1;j<len;j++)
            {
                if(comparision(*(begin+min),*(begin+j)))
                    min=j;
            }
            if(i!=min)
                swap(begin+i,begin+min); 
        }
    }

    template<class T1,class T2>
    void Sort<T1,T2>::insertionSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("insertionSort");
        T2 temp=new T1;
        for(int i=1;i<len;i++){
            int j;
            *temp=*(begin+i);
            for(j=i;j>0&&(comparision(*(begin+j-1),*temp));j--)
                swap(begin+j,begin+j-1);
            swap(begin+j,temp);
        }
        delete temp;
    }

    template<class T1,class T2>
    void Sort<T1,T2>::shellSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
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
                for(j=i-gap;j>=0&&(comparision(*(begin+j),*temp));j-=gap)
                    swap(begin+j+gap,begin+j);
                swap(begin+j+gap,temp);
            }
        }
        delete temp;
    }

    template<class T1,class T2>
    void Sort<T1,T2>::mergeSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
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
                    if(!comparision(*(begin+p1),*(begin+p2)))
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

    template<class T1,class T2>
    void Sort<T1,T2>::mergeSortRecursive(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
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
                if(!comparision(*(begin+p1),*(begin+p2)))
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

    template<class T1,class T2>
    void Sort<T1,T2>::quickSort(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("quickSort");
    }

    template<class T1,class T2>
    void Sort<T1,T2>::quickSortRecursive(T2 begin,T2 end,std::function<bool(const T1&,const T1&)> comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("quickSortRecursive");
    }

    template<class T1,class T2>
    void Sort<T1,T2>::heapSort(T2 begin,T2 end, std::function<bool(const T1&,const T1&)> comparision)
    {
        int len=end-begin;
        if(len<=0)
            throw std::invalid_argument("heapSort");
    }
}

#endif /* SORT_H */