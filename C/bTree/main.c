#include "bTree.h"
int main(){
    BTree tree;
    int a[5]={1,2,3,4,5};
    Pair pair[5]={{1,&a[4]},{2,&a[3]},{3,&a[2]},{4,&a[1]},{5,&a[0]}};
    bTreeInitalize(&tree);
    printf("root:%p,child[0]:%p,child[1]:%p\n",tree,tree->child[0],tree->child[1]);
    // bTreeInsert(tree,&pair[1]);
    // bTreeInsert(tree,&pair[2]);
    // bTreeInsert(tree,&pair[3]);
    for(int i=1;i<5;i++){
        bTreeInsert(tree,&pair[i]);
    }
    bTreeFree(&tree);
    return 0;
}