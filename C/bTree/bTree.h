#ifndef _B_TREE_H_
#define _B_TREE_H_
#include <stdio.h>
#include <stdbool.h>

#define M 3
#define MAX_KEY (M-1)
#define MIN_KEY ((M-1)/2)
#define MID_KEY ((M+1)/2)
typedef int Key;
typedef void* eleType;
typedef struct BTNode {
    int keynum;
    Key keys[M+1];
    eleType data[M+1];
    struct BTNode* parent;
    struct BTNode* child[M+1];
}BTNode,*BTree;
void bTreeInitalize(BTree* tree);
void bTreeTraversal(BTree tree,void(*traversal)(void*));
eleType bTreeSearch(BTree tree,Key key);
bool bTreeInsert(BTree tree,Key key,eleType value);
eleType bTreeDelete(BTree tree,Key key);
void bTreeFree(BTree* tree);
#endif /* _B_TREE_H_ */
