#include "bTree.h"
#include "linkQueue.h"
#include<stdlib.h>
#include "debug.h"
static BTNode* createBTNode(BTNode* parent)
{
    /*
        create a BTNode

        keynum set 0 and set parent
        all the keys set 0,all the value set NULL,all the child set NULL
    */
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

static int serachIndex(BTNode *node,Key key)
{
    /*
        search node

        index start at 1,the range is [1,keynum]
    */
    int i=1;
    while(i<node->keynum&&key>node->keys[i])
        i++;
    return i;
}

static void insertValue(BTNode* node,int index,Key key,eleType value)
{
    /*
        insert key-value to BTNode
    */
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

static void insertBTNode(BTNode* parent,int index,BTNode* node)
{
    /*
        insert BTNode* to node's child
    */
    int endPos=parent->keynum;
    for(int i=0;i<endPos-index;i++)
        parent->child[endPos-i]=parent->child[endPos-i-1];
    parent->child[index]=node;
    if(node!=NULL){
        node->parent=parent;
        printf("node %p 's child[%d] set %p\n",parent,index,node->child[index]);
    }
}

static eleType deleteValue(BTNode* node,int index)
{
    /*
        delete key-value of position index
    */
    int endPos=node->keynum;
    eleType data=node->data[index];
    for(int i=index;i<endPos;i++){
        node->keys[index]=node->keys[index+1];
        node->data[index]=node->data[index+1];
    }
    node->keys[endPos]=0;
    node->data[endPos]=NULL;
    printf("delete value on node:%p,pos:%d\n",node,index);
    node->keynum--;
    return data;
}

static void splitBTNode(BTNode* node)
{
    /*
        split the node
    */

    //save mid value
    Key key=0;
    eleType value=NULL;
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
    key=node->keys[MID_KEY];
    value=node->data[MID_KEY];
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
        if(key>parent->keys[index])
            index++;
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

static void moveLeft(BTNode* parent,int index,BTNode* leftChild,int dataPos)
{
    /*
        move a key-value to left

        delete data at datapos position
        move parent's begin data to leftChild's end position
        move rightChild's begin data to parent's end position
    */
    BTNode* rightChild=parent->child[index];
    if(!(parent&&leftChild&&rightChild))
        return;
    //left child move to left
    for(int i=dataPos;i<leftChild->keynum;i++){
        leftChild->keys[i]=leftChild->keys[i];
        leftChild->data[i]=leftChild->data[i];
    }
    leftChild->keys[leftChild->keynum]=parent->keys[index];
    leftChild->data[leftChild->keynum]=parent->data[index];
    //parent move to left
    parent->keys[index]=rightChild->keys[1];
    parent->data[index]=rightChild->data[1];
    //right child move to left
    for(int i=1;i<rightChild->keynum;i++){
        rightChild->keys[i]=rightChild->keys[i+1];
        rightChild->data[i]=rightChild->data[i+1];
    }
    rightChild->keys[rightChild->keynum]=0;
    rightChild->data[rightChild->keynum]=NULL;
    rightChild->keynum--;
}

static void moveRight(BTNode* parent,int index,BTNode* rightChild,int dataPos)
{
    /*
        move a key-value to right

        delete data at datapos position
        move parent's end data to rightChild's begin position
        move leftChild's end data to parent's begin position
    */
    BTNode* leftChild=parent->child[index-1];
    if(!(parent&&leftChild&&rightChild))
        return;
    //right child move to left
    for(int i=dataPos;i>1;i--){
        rightChild->keys[i]=rightChild->keys[i-1];
        rightChild->data[i]=rightChild->data[i-1];
    }
    rightChild->keys[1]=parent->keys[index];
    rightChild->data[1]=parent->data[index];
    //parent move to left
    parent->keys[index]=leftChild->keys[leftChild->keynum];
    parent->data[index]=leftChild->data[leftChild->keynum];
    //left child move to left
    leftChild->keys[leftChild->keynum]=0;
    leftChild->data[leftChild->keynum]=NULL;
    leftChild->keynum--;
}

static void combineNode()
{
    /*
        combine two child node
    */
}

static BTNode* getPrecursor(BTNode* node)
{
    // //if node not leaf,should have child
    // if(node==NULL||node->parent!=NULL&&node->child[0]==NULL)
    //     return NULL;
    // BTNode* parent=node->parent;
    // BTNode* target=NULL;
    // if(parent!=NULL){
    //     //leaf node
    //     //node don't have child
    //     int i=serachIndex(parent,node->keys[1]);
    //     if(node->keys[1]<parent->keys[i])
    //         i--;
    //     if(i==0)
    //         return node->child[0];
    //     target=parent->child[i-1];
    // }else{
    //     //node have child
    //     target=node->child[0];
    //     //get the right node
    //     while(target->child[target->keynum]!=NULL)
    //         target=target->child[target->keynum];
    // }
    // return target;
}

static BTNode* getSuccessor(BTNode* node)
{
    
}

void bTreeInitalize(BTree *tree)
{
    /*
        inital b-tree

        create a node,parent is NULL
    */
    if(tree==NULL)
        return;
    *tree=createBTNode(NULL);
}

eleType bTreeSearch(BTree tree, Key key)
{
    /*
        search data by key in b-tree
    */
    int i=1;
    BTNode* currNode=tree;
    while(currNode){
        i=serachIndex(currNode,key);
        if(key>currNode->keys[i]){
            currNode=currNode->child[i];
        }else if(key==currNode->keys[i]){
            break;
        }else if(key<currNode->keys[i]){
            currNode=currNode->child[i-1];
        }
    }
    if(currNode==NULL)
        return NULL;
    return currNode->data[i];
}

bool bTreeInsert(BTree tree, Key key, eleType value)
{
    /*
        insert data to b-tree by key
    */
    int i=1;
    BTNode* preNode=NULL;
    BTNode* currNode=tree;
    while(currNode){
        i=serachIndex(currNode,key);
        if(key>currNode->keys[i]){
            preNode=currNode;
            currNode=currNode->child[i];
        }else if(key==currNode->keys[i]){
            return false;
        }else if(key<currNode->keys[i]){
            preNode=currNode;
            currNode=currNode->child[i-1];
        }
    }
    if(currNode==NULL)
        currNode=preNode;
    i=serachIndex(currNode,key);
    if(i==currNode->keynum&&key>currNode->keys[i])
        i++;
    insertValue(currNode,i,key,value);
    if(currNode->keynum>MAX_KEY){
        splitBTNode(currNode);
    }
    return true;
}

eleType bTreeDelete(BTree tree, Key key)
{
    /*
        delete data to b-tree by key
    */
    if(tree==NULL)
        return false;
    int i=1;
    BTNode* parent=NULL;
    BTNode* currNode=tree;
    eleType data=NULL;
    while(currNode){
        i=serachIndex(currNode,key);
        if(key>currNode->keys[i]){
            currNode=currNode->child[i];
        }else if(key==currNode->keys[i]){
            break;
        }else if(key<currNode->keys[i])
            currNode=currNode->child[i-1];
    }
    if(currNode==NULL)
        return NULL;
    i=serachIndex(currNode,key);
    //save data
    data=currNode->data[i];
    printf("key:%d,value:%d\n",currNode->keys[i],*(int*)currNode->data[i]);
    //leaf node
    if(currNode->child[0]==NULL){
        //key greater than min
        if(currNode->keynum>MIN_KEY){
            deleteValue(currNode,i);
        //key equal to min
        }else{
            parent=currNode->parent;
            //leaf node is root
            if(parent==NULL){
                deleteValue(currNode,1);
                return data;
            }
            //normal node
            int j=serachIndex(parent,currNode->keys[i]);
            BTNode* leftChild=NULL;
            BTNode* rightChild=NULL;
            if(currNode->keys[i]<parent->keys[j])
                j--;
            //right node is rich node
            //move to left
            if(j+1<=parent->keynum&&parent->child[j+1]->keynum>MIN_KEY){
                moveLeft(parent,j+1,currNode,i);
                return data;
            }
            //left node is rich node
            //move to right
            if(j-1>=0&&parent->child[j-1]->keynum>MIN_KEY){
                moveRight(parent,j,currNode,i);
                return data;
            }
            //right and left are not rich node

        }
    }
    return data;
}

void bTreeFree(BTree *tree)
{
    /*
        free b-tree
    */
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
