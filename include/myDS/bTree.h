#ifndef B_TREE_H
#define B_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#define M 3
#define MAX_KEY (M-1)
#define MIN_KEY ((M-1)/2)
#define MID_KEY ((M+1)/2)

typedef int Key;
typedef void* eleType;
typedef struct BTNode
{
    int keynum;
    Key keys[M+1];
    eleType data[M+1];
    struct BTNode* parent;
    struct BTNode* child[M+1];
} BTNode, *BTree;

void bTreeInitalize(BTree* tree);
void bTreeShowNode(BTNode* node);
void bTreeShow(BTree tree);
void bTreePreOrderTraversal(BTree tree, void (*traversal)(void *));
void bTreeInOrderTraversal(BTree tree, void (*traversal)(void *));
void bTreeLevelOrderTraversal(BTree tree,void(*traversal)(void*));
eleType bTreeSearch(BTree tree,Key key);
bool bTreeInsert(BTree tree,Key key,eleType value);
eleType bTreeDelete(BTree tree,Key key);
void bTreeFree(BTree* tree);

#ifdef __cplusplus
}
#endif

#endif /* B_TREE_H */