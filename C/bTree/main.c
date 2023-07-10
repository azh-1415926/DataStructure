#include "bTree.h"
void traversal(void* data){
    printf("%d",*(int*)data);
}
int main(){
    BTree tree;
    int a[18]={35,16,18,70,5,50,22,60,13,17,12,45,25,42,15,90,30,7};
    //int a[18]={35,16,18,70,5,50,22,60,13,17,12,45,25,42,15,90,30,7};
    bTreeInitalize(&tree);
    for(int i=0;i<sizeof(a)/sizeof(int);i++){
        bTreeInsert(tree,a[i],&a[i]);
    }
    printf("Create bTree\n");
    printf("find key:60,data:%d\n",*(int*)(bTreeSearch(tree,60)));
    printf("LevelOrderTraversal:");
    bTreeLevelOrderTraversal(tree,traversal);
    printf("PreOrderTraversal:");
    bTreePreOrderTraversal(tree,traversal);
    printf("InOrderTraversal:");
    bTreeInOrderTraversal(tree,traversal);
    printf("ShowKeys:");
    bTreeShow(tree);
    bTreeDelete(tree,45);
    bTreeDelete(tree,90);
    bTreeDelete(tree,50);
    bTreeDelete(tree,22);
    bTreeDelete(tree,42);
    printf("Delete some keys\n");
    printf("LevelOrderTraversal:");
    bTreeLevelOrderTraversal(tree,traversal);
    printf("PreOrderTraversal:");
    bTreePreOrderTraversal(tree,traversal);
    printf("InOrderTraversal:");
    bTreeInOrderTraversal(tree,traversal);
    printf("ShowKeys:");
    bTreeShow(tree);
    bTreeFree(&tree);
    return 0;
}