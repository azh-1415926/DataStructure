#include "debug.h"

void showBTree(BTNode* node)
{
    if(node==NULL)
        return;
    printf("[ * ] tree node %p\n",node);
    printf("\tkeynum:%d\n\t",node->keynum);
    for(int i=1;i<=M;i++){
        printf("%d ",node->keys[i]);
    }
    printf("\n");
    printf("\tparent:%p\n\t",node->parent);
    for(int i=0;i<=M;i++){
        printf("%p ",node->child[i]);
    }
    printf("\n");
}
