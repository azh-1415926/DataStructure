#include <simpleDS/linkQueue.hpp>
#include <simpleDS/binaryTree.hpp>
#include <simpleDS/linkList.hpp>
#include <simpleDS/vector.hpp>

int main(){
    azh::linkQueue<int> queue;
    queue.enqueue(0);
    queue.enqueue(1);
    queue.enqueue(2);
    int array[]={1,2,3,4,5,6};
    azh::binaryTree<int> tree(array,6);
    tree.inOrderTraversal();
    azh::linkList<int> list;
    list.insert(0);
    list.show();
    azh::vector<int> vec;
    vec.push_back(0);
    vec.push_back(3);
    for(auto i : vec)
    {
        std::cout<<i<<" ";
    }
    auto vec_copy=vec;
    for(auto i : vec_copy)
    {
        std::cout<<i<<" ";
    }
    vec.pop_back();
    vec.pop_back();
    return 0;
}