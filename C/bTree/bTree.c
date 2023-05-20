#include "bTree.h"
#include "linkQueue.h"
#include<stdlib.h>

static int serachIndex(BTNode *node,Key key){
    int i=1;
    while(i<=node->keynum&&key>=node->keys[i++]);
    return i;
}

static void insertValue(BTNode* node,int index,pPair pair){
    int endPos=node->keynum+1;
    for(int i=0;i<endPos-index;i++){
        node->keys[endPos-i]=node->keys[endPos-i-1];
        node->data[endPos-i]=node->data[endPos-i-1];
    }
    node->keys[index]=pair->key;
    node->data[index]=pair->value;
}

static void insertBTNode(BTNode* parent,int index,BTNode* node){
    int endPos=node->keynum+1;
    for(int i=0;i<endPos-index;i++)
        node->child[endPos-i]=node->child[endPos-i-1];
    node->child[index]=node;
}

static BTNode* splitBTNode(BTNode* parent,BTNode* node){
    int i=1;
    Pair pair={node->keys[MID_KEY],node->data[MID_KEY]};
    i=serachIndex(parent,node->keys[MID_KEY]);
    insertBTNode(parent,i,&pair);
    parent->
}

static BTNode* createBTNode(BTNode* parent,pPair pair){
    BTNode* node=malloc(sizeof(BTNode));
    if(pair!=NULL){
        node->keynum=1;
        node->keys[1]=pair->key;
        node->data[1]=pair->value;
    }else
        node->keynum=0;
    node->parent=parent;
    node->child[0]=NULL;
    node->child[1]=NULL;
}

void bTreeCreateRoot(BTree *tree, pPair pair, BTNode *lchild, BTNode *rchild)
{
    *tree=createBTNode(NULL,pair);
    if(pair!=NULL){
        (*tree)->keynum=1;
        (*tree)->child[0]=lchild;
        (*tree)->child[1]=rchild;
    }
}

void bTreeInitalize(BTree *tree)
{
    if(tree==NULL)
        return;
    bTreeCreateRoot(tree,NULL,NULL,NULL);
}

bool bTreeInsert(BTree tree, pPair pair)
{
    int i=1;
    BTNode* currNode=tree;
    BTNode* preNode=NULL;
    while(currNode!=NULL){
        i=serachIndex(currNode,pair->key);
        if(currNode->keynum==0)
            break;
        if(pair->key==currNode->keys[i]){
            return false;
        }
        if(pair->key>currNode->keys[i]){
            preNode=currNode;
            currNode=currNode->child[i];
        }
    }
    if(preNode!=NULL)
        currNode=preNode;
    insertValue(currNode,i,pair);
    //insertBTNode(preNode,);
    currNode->keynum++;
    printf("insert to node:%p,key:%d,value:%d",currNode,pair->key,*(int*)pair->value);
    if(currNode->keynum==MAX_KEY){
        splitBTNode(preNode,currNode);
    }
}

void bTreeFree(BTree *tree)
{
    if(tree==NULL&&*tree==NULL)
        return;
    linkQueue queue;
    BTNode* currNode=NULL;
    linkQueueInitalize(&queue);
    linkQueueEnqueue(queue,*tree);
    int i=1;
    while(!linkQueueIsEmpty(queue)){
        currNode=linkQueueFront(queue);
        linkQueueDequeue(queue);
        if(currNode->child[0]!=NULL){
            linkQueueEnqueue(queue,currNode->child[0]);
        }
        while(i++<currNode->keynum){
            if(currNode->child[i]!=NULL)
                linkQueueEnqueue(queue,currNode->child[i]);
        }
        printf("delete Node:%p,key:%d,value:%d",currNode,currNode->keys[1],*(int*)currNode->data);
        free(currNode);
        i=1;
    }
    linkQueueFree(&queue);
}
