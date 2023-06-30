#include "bTree.h"
void traversal(void* data){
    printf("%d",*(int*)data);
}
int main(){
    BTree tree;
    int a[18]={35,16,18,70,5,50,22,60,13,17,12,45,25,42,15,90,30,7};
    bTreeInitalize(&tree);
    for(int i=0;i<18;i++){
        bTreeInsert(tree,a[i],&a[i]);
    }
    bTreeDelete(tree,45);
    bTreeDelete(tree,90);
    bTreeDelete(tree,50);
    bTreeDelete(tree,22);
    bTreeDelete(tree,42);
    bTreeLevelOrderTraversal(tree,traversal);
    bTreeShow(tree,traversal);
    bTreeFree(&tree);
    return 0;
}