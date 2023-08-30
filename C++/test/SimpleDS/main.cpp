#include <simpleDS/linkQueue.hpp>
#include <simpleDS/binaryTree.hpp>
#include <simpleDS/linkList.hpp>

int main(){
    linkQueue<int> queue;
    queue.enqueue(0);
    queue.enqueue(1);
    queue.enqueue(2);
    int array[]={1,2,3,4,5,6};
    binaryTree<int> tree(array,6);
    tree.inOrderTraversal();
    linkList<int> list;
    list.insert(0);
    list.show();
    return 0;
}