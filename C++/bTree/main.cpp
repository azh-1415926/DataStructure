#include <iostream>
#include "bTree.hpp"
void visit(int data){
    std::cout<<data;
}
int main(){
    BTree<int> tree;
    tree.insert(35,35);
    tree.insert(16,16);
    tree.insert(18,18);
    tree.insert(70,70);
    tree.insert(5,5);
    tree.insert(50,50);
    tree.insert(22,22);
    tree.insert(60,60);
    tree.insert(13,13);
    tree.insert(17,17);
    tree.insert(12,12);
    tree.insert(45,45);
    tree.insert(25,25);
    tree.insert(42,42);
    tree.insert(15,15);
    tree.insert(90,90);
    tree.insert(30,30);
    tree.insert(7,7);
    std::cout<<"Create bTree\n";
    std::cout<<"ShowKeys:";
    tree.show();
    std::cout<<"inOrderTraversal:";
    tree.inOrderTraversal(visit);
    std::cout<<"preOrderTraversal:";
    tree.preOrderTraversal(visit);
    std::cout<<"Delete some keys\n";
    tree.erase(45);
    tree.erase(90);
    tree.erase(50);
    tree.erase(22);
    tree.erase(42);
    std::cout<<"ShowKeys:";
    tree.show();
    std::cout<<"inOrderTraversal:";
    tree.inOrderTraversal(visit);
    std::cout<<"preOrderTraversal:";
    tree.preOrderTraversal(visit);
    return 0;
}