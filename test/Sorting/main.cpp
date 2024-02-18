#include <myDS/sort.hpp>
#include <myTools/sortCase.hpp>
#include <algorithm>

#define SHOW_CONTAINER_DATA(container,showFunc) \
    std::cout<<"Show data from container : "<<#container<<"\n"; \
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

int main()
{
    azh::sortCase<int> sortCase(10,0,10);
    sortCase.setRandFunction(getRandForInt);
    azh::vector<int> vec=sortCase.getNoRepeat();
    SHOW_CONTAINER_DATA(vec,printData);
    azh::Sort<int,azh::vector<int>::iterator>::bubbleSort(vec.begin(),vec.end(),comparisionForInt);
    SHOW_CONTAINER_DATA(vec,printData);
    sortCase.verify(vec,comparisionForInt);
    return 0;
}