#include "bTree.h"
int main(){
    BTree tree;
    int a[10]={1,2,3,4,5,10,9,8,7,6};
    Pair pair[10]={
        {35,&a[4]},
        {16,&a[3]},
        {18,&a[2]},
        {70,&a[1]},
        {5,&a[0]},
        {50,&a[5]},
        {22,&a[6]},
        {60,&a[7]},
        {13,&a[8]},
        {17,&a[9]}
        };
    bTreeInitalize(&tree);
    printf("root:%p,child[0]:%p,child[1]:%p\n",tree,tree->child[0],tree->child[1]);
    for(int i=0;i<9;i++){
        bTreeInsert(tree,&pair[i]);
    }
    bTreeFree(&tree);
    return 0;
}