#include <myDS/sort.hpp>
#include <vector>
#include <algorithm>

bool comparisionForInt(const int& v1,const int& v2)
{
    return (v1-v2)>0;
};

void printData(int data)
{
    std::cout<<data<<"\n";
}

int main()
{
    int vec[]={1,3,2,4,5};
    std::vector<int> vec1={1,3,2,4,5};
    std::cout<<"vec\n";
    std::for_each(vec,vec+sizeof(vec)/sizeof(int),printData);
    std::cout<<"vec1\n";
    std::for_each(vec1.begin(),vec1.end(),printData);
    // azh::Sort<int>::bubbleSort(vec,vec+sizeof(vec)/sizeof(int),comparisionForInt);
    azh::Sort<int>::mergeSort(vec,vec+sizeof(vec)/sizeof(int),comparisionForInt);
    azh::Sort<int,std::vector<int>::iterator>::bubbleSort(vec1.begin(),vec1.end(),comparisionForInt);
    std::cout<<"vec\n";
    std::for_each(vec,vec+sizeof(vec)/sizeof(int),printData);
    std::cout<<"vec1\n";
    std::for_each(vec1.begin(),vec1.end(),printData);
    return 0;
}