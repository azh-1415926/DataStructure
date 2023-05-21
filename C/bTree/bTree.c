#include "bTree.h"
#include "linkQueue.h"
#include<stdlib.h>
#include "debug.h"
static BTNode* createBTNode(BTNode* parent,pPair pair){
    BTNode* node=malloc(sizeof(BTNode));
    if(pair!=NULL){
        node->keynum=1;
        node->keys[1]=pair->key;
        node->data[1]=pair->value;
    }else
        node->keynum=0;
    node->parent=parent;
    for(int i=0;i<=M;i++){
        node->child[i]=NULL;
    }
    return node;
}

static int serachIndex(BTNode *node,Key key){
    int i=1;
    while(i<=node->keynum&&key>=node->keys[i])
        i++;
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
    printf("insert value to node:%p,pos:%d,key:%d,value:%d\n",node,index,pair->key,*(int*)pair->value);
    node->keynum++;
}

static void insertBTNode(BTNode* parent,int index,BTNode* node){
    int endPos=node->keynum+1;
    for(int i=0;i<endPos-index;i++)
        node->child[endPos-i]=node->child[endPos-i-1];
    node->child[index]=node;
}

static void splitBTNode(BTNode* node){
    int i=1;
    //save mid value
    Pair pair={node->keys[MID_KEY],node->data[MID_KEY]};
    BTNode* temp=NULL;
    if(node->parent==NULL){
        printf("currnode is root,start to split\n");
        //node is root,and node still is root
        //create left tree
        temp=createBTNode(node,NULL);
        printf("create node %p\n",temp);
        temp->child[0]=node->child[0];
        printf("node %p 's child[%d] set %p\n",temp,0,node->child[0]);
        for(int i=1;i<MID_KEY;i++){
            pair.key=node->keys[i];
            pair.value=node->data[i];
            insertValue(temp,i,&pair);
            temp->child[i]=node->child[i];
            node->child[i]=NULL;
            printf("node %p 's child[%d] set %p\n",temp,i,node->child[i]);
        }
        //the root's left tree
        node->child[0]=temp;
        printf("node %p 's left child set %p\n",node,temp);
        //use mid value
        node->keys[1]=node->keys[MID_KEY];
        node->data[1]=node->data[MID_KEY];
        //create right tree
        temp=createBTNode(node,NULL);
        printf("create node %p\n",temp);
        temp->child[0]=node->child[MID_KEY];
        for(int i=1;i<=node->keynum-MID_KEY;i++){
            pair.key=node->keys[MID_KEY+i];
            pair.value=node->data[MID_KEY+i];
            insertValue(temp,i,&pair);
            temp->child[i]=node->child[MID_KEY+i];
            node->child[MID_KEY+i]=NULL;
        }
        //the root's right tree
        node->child[1]=temp;
        printf("node %p 's right child set %p\n",node,temp);
        node->keynum=1;
    }else{
        i=serachIndex(node->parent,node->keys[MID_KEY]);
        //create right node
        temp=createBTNode(node->parent,NULL);
        insertBTNode(node->parent,i,temp);
        insertValue(node->parent,i,&pair);
        //temp->child[0]=node->child[MID_KEY];
        for(int i=1;i<node->keynum-MID_KEY;i++){
            pair.key=node->keys[MID_KEY+i];
            pair.value=node->data[MID_KEY+i];
            insertValue(temp,i,&pair);
            temp->child[i]=node->child[MID_KEY+i];
            node->child[MID_KEY+i]=NULL;
        }
        node->keynum=MID_KEY-1;
        if(node->parent->keynum>MAX_KEY)
            splitBTNode(node->parent);
    }
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
        // if(currNode->keynum==0)
        //     break;
        if(pair->key==currNode->keys[i]){
            return false;
        }
        if(i<currNode->keynum&&pair->key>currNode->keys[i]){
            preNode=currNode;
            currNode=currNode->child[i];
        }
        else{
            preNode=currNode;
            currNode=currNode->child[i-1];
        }
    }
    if(preNode!=NULL)
        currNode=preNode;
    insertValue(currNode,i,pair);
    //printf("insert to node:%p,key:%d,value:%d\n",currNode,pair->key,*(int*)pair->value);
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
        printf("delete Node:%p\n",currNode);
        showBTree(currNode);
        free(currNode);
        i=1;
    }
    linkQueueFree(&queue);
}
