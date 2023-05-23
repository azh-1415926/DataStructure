#include "bTree.h"
int main(){
    BTree tree;
    int a[10]={35,16,18,70,5,50,22,60,13,17};
    bTreeInitalize(&tree);
    printf("root:%p,child[0]:%p,child[1]:%p\n",tree,tree->child[0],tree->child[1]);
    for(int i=0;i<6;i++){
        bTreeInsert(tree,a[i],&a[9-i]);
    }
    int *p=bTreeSearch(tree,60);
    if(p!=NULL)
        printf("search data:%d\n",*p);
    bTreeFree(&tree);
    return 0;
}