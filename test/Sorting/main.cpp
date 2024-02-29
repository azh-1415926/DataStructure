#include <myDS/sort.hpp>
#include <myTools/sortCase.hpp>
#include <myTools/timer.hpp>
#include <algorithm>

#include <ctime>

static azh::Vector<int> vec;
static azh::Vector<int> vecCpy;

#define SHOW_CONTAINER_DATA(container,showFunc) \
    for(auto i=container.begin();i!=container.end();i++) \
    { \
        showFunc(*i); \
        std::cout<<" "; \
    } \
    std::cout<<"\n";

int comparisionForInt(const int& v1,const int& v2)
{
    return v1-v2;
};

int getRandForInt(int seed)
{
    srand(time(NULL));
    seed+=213;
    return rand()%seed+10;
}

void printData(int data)
{
    std::cout<<data;
}

#define SORT_FUNC(name) \
    azh::Sort<int,azh::Vector<int>::iterator>::name(vec.begin(),vec.end(),comparisionForInt);

void sortBy(int i)
{
    static azh::Vector<std::string> sortMethods=
    {
        "qsort",
        "bubbleSort",
        "selectionSort",
        "insertionSort",
        "shellSort",
        "mergeSort",
        "mergeSortRecursive",
        "quickSort",
        "quickSortRecursive",
        "heapSort"
    };
    if(i>=sortMethods.size())
        return;
    static int pre=-1;
    if(i!=pre)
        std::cout<<"Sorted By : "<<sortMethods[i]<<"\n";
    switch (i)
    {
    case 0:
        // std::sort(vec.begin(),vec.end(),comparisionForInt);
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
    pre=i;
}

int main()
{
    int sortCount=1000000;
    azh::Timer timer;
    azh::sortCase<int> sortCase(10,0,10);
    sortCase.setRandFunction(getRandForInt);
    
    /* 测试全部排序 */
    for(int i=1;i<10;i++)
    {
        vecCpy=sortCase.getNoRepeatByCount(sortCount*10);
        SHOW_CONTAINER_DATA(vecCpy,printData);
        timer.start();
        for(int j=0;j<sortCount;j++)
        {
            vec=vecCpy;
            sortBy(i);
        }
        double sec=timer.end();
        SHOW_CONTAINER_DATA(vec,printData);
        std::cout<<"Cost time:"<<sec<<"\n";
        bool isVaild=sortCase.verify(vec,comparisionForInt);
        if(!isVaild)
            std::cout<<"sort error!\n";
    }

    /* 测试单个排序 */
    for(int i=0;i<10;i++)
    {
        vecCpy=sortCase.getNoRepeat();
        std::cout<<"This is "<<i+1<<" th sort\n";
        SHOW_CONTAINER_DATA(vecCpy,printData);
        timer.start();
        for(int j=0;j<sortCount;j++)
        {
            vec=vecCpy;
            sortBy(5);
        }
        double sec=timer.end();
        SHOW_CONTAINER_DATA(vec,printData);
        bool isVaild=sortCase.verify(vec,comparisionForInt);
        if(!isVaild)
            std::cout<<"sort error!\n";
    }

    return 0;
}