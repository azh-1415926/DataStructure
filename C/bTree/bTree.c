#include "bTree.h"
#include "linkQueue.h"
#include<stdlib.h>
#include "debug.h"
static BTNode* createBTNode(BTNode* parent){
    BTNode* node=malloc(sizeof(BTNode));
    node->keynum=0;
    node->parent=parent;
    for(int i=0;i<=M;i++){
        node->keys[i]=0;
        node->data[i]=0;
        node->child[i]=NULL;
    }
    printf("create node %p\n",node);
    return node;
}

static int serachIndex(BTNode *node,Key key){
    int i=1;
    while(i<node->keynum&&key>node->keys[i])
        i++;
    return i;
}

static void insertValue(BTNode* node,int index,Key key,eleType value){
    int endPos=node->keynum+1;
    for(int i=0;i<endPos-index;i++){
        node->keys[endPos-i]=node->keys[endPos-i-1];
        node->data[endPos-i]=node->data[endPos-i-1];
    }
    node->keys[index]=key;
    node->data[index]=value;
    printf("insert value to node:%p,pos:%d,key:%d,value:%d\n",node,index,key,*(int*)value);
    node->keynum++;
}

static void insertBTNode(BTNode* parent,int index,BTNode* node){
    int endPos=parent->keynum;
    for(int i=0;i<endPos-index;i++)
        parent->child[endPos-i]=parent->child[endPos-i-1];
    parent->child[index]=node;
    if(node!=NULL){
        node->parent=parent;
        printf("node %p 's child[%d] set %p\n",parent,index,node->child[index]);
    }
}

static void splitBTNode(BTNode* node){
    //save mid value
    Key key=node->keys[MID_KEY];
    eleType value=node->data[MID_KEY];
    BTNode* parent=node->parent;
    BTNode* rightChild=NULL;
    //right child
    rightChild=createBTNode(node);
    insertBTNode(rightChild,0,node->child[MID_KEY]);
    node->child[MID_KEY]=NULL;
    for(int i=1;i<=node->keynum-MID_KEY;i++){
        key=node->keys[MID_KEY+i];
        value=node->data[MID_KEY+i];
        node->keys[MID_KEY+i]=0;
        node->data[MID_KEY+i]=NULL;
        insertValue(rightChild,i,key,value);
        insertBTNode(rightChild,i,node->child[MID_KEY+i]);
        node->child[MID_KEY+i]=NULL;
    }
    printf("-------split--------node:%p\n",node);
    if(parent==NULL){
        BTNode* leftChild=NULL;
        //left child
        leftChild=createBTNode(node);
        insertBTNode(leftChild,0,node->child[0]);
        node->child[0]=NULL;
        for(int i=1;i<MID_KEY;i++){
            key=node->keys[i];
            value=node->data[i];
            node->keys[i]=0;
            node->data[i]=NULL;
            insertValue(leftChild,i,key,value);
            insertBTNode(leftChild,i,node->child[i]);
            node->child[i]=NULL;
        }
        key=node->keys[MID_KEY];
        value=node->data[MID_KEY];
        node->keys[MID_KEY]=0;
        node->data[MID_KEY]=NULL;
        node->keynum=0;
        insertBTNode(node,0,leftChild);
        insertValue(node,1,key,value);
        insertBTNode(node,1,rightChild);
        showBTree(node);
        showBTree(leftChild);
        showBTree(rightChild);
    }else{
        int index=1;
        index=serachIndex(parent,key);
        node->keynum=MID_KEY-1;
        node->keys[MID_KEY]=0;
        node->data[MID_KEY]=NULL;        
        insertValue(parent,index,key,value);
        //leftChild=node;
        insertBTNode(parent,index,rightChild);
        showBTree(parent);
        showBTree(node);
        showBTree(rightChild);
        if(parent->keynum>MAX_KEY)
            splitBTNode(parent);
    }
}

void bTreeInitalize(BTree *tree)
{
    if(tree==NULL)
        return;
    *tree=createBTNode(NULL);
}

eleType bTreeSearch(BTree tree, Key key)
{
    int i=1;
    BTNode* currNode=tree;
    while(currNode&&key!=currNode->keys[i]){
        i=serachIndex(currNode,key);
        if(key>currNode->keys[i])
            currNode=currNode->child[i];
        else if(key<currNode->keys[i])
            currNode=currNode->child[i-1];
    }
    if(currNode==NULL)
        return NULL;
    return currNode->data[i];
}

bool bTreeInsert(BTree tree, Key key, eleType value)
{
    int i=1;
    BTNode* preNode=NULL;
    BTNode* currNode=tree;
    while(currNode){
        i=serachIndex(currNode,key);
        if(key>currNode->keys[i]){
            preNode=currNode;
            currNode=currNode->child[i];
        }
        else if(key==currNode->keys[i]){
            return false;
        }
        else if(key<currNode->keys[i]){
            preNode=currNode;
            currNode=currNode->child[i-1];
        }
    }
    if(currNode==NULL)
        currNode=preNode;
    i=serachIndex(currNode,key);
    insertValue(currNode,i,key,value);
    if(currNode->keynum>MAX_KEY){
        splitBTNode(currNode);
    }
    return true;
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
    printf("----------end----------\n");
    while(!linkQueueIsEmpty(queue)){
        currNode=linkQueueFront(queue);
        linkQueueDequeue(queue);
        if(currNode->child[0]!=NULL){
            linkQueueEnqueue(queue,currNode->child[0]);
        }
        while(i<=currNode->keynum){
            if(currNode->child[i]!=NULL)
                linkQueueEnqueue(queue,currNode->child[i]);
            i++;
        }
        showBTree(currNode);
        free(currNode);
        i=1;
    }
    linkQueueFree(&queue);
}
