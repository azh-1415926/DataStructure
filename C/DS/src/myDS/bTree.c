#include <myDS/bTree.h>
#include <simpleDS/linkQueue.h>
#include <stdlib.h>

/* 创建一个 B 树节点 */
static BTNode* createBTNode(BTNode* parent);
/* 在指定节点中查找关键字的下标 */
static int searchIndex(BTNode *node,Key key);
/* 在指定节点中查找关键字对应的孩子节点 */
static BTNode* searchBTNode(BTNode* node,Key key);
/* 在指定节点中插入关键字和数据 */
static void insertValue(BTNode* node,int index,Key key,eleType value);
/* 插入指定节点对应下标处的子节点 */
static void insertBTNode(BTNode* parent,int index,BTNode* node);
/* 在指定节点中删除对应下标上的关键字及数据 */
static eleType deleteValue(BTNode* node,int index);
/* 删除指定节点对应下标的子节点 */
static BTNode* deleteBTNode(BTNode* node,int index);
/* 指定节点执行分裂操作 */
static void splitBTNode(BTNode* node);
/* 将父节点指定下标的 */
static void moveLeft(BTNode* parent,int index,BTNode* leftChild,int dataPos);
static void moveRight(BTNode* parent,int index,BTNode* rightChild,int dataPos);
static void combineBTNode(BTNode* parent,int index);
static void balanceBTNode(BTNode* parent,int index);

static BTNode* createBTNode(BTNode* parent)
{
    /* 创建一个 BTNode 节点，设置好初始值后返回 */
    BTNode* node=(BTNode*)malloc(sizeof(BTNode));
    /* 关键字数 keynums 置零，父节点 parent 置为为传入的 parent */
    node->keynum=0;
    node->parent=parent;
    /* 所有关键字 keys 置为 0，所有数据 data 置 NULL，子节点 child 置 NULL */
    for(int i=0;i<=M;i++){
        node->keys[i]=0;
        node->data[i]=0;
        node->child[i]=NULL;
    }
    return node;
}

static int searchIndex(BTNode *node,Key key)
{
    /*
        查找 node 中 key (对应、对应子节点)的下标
        由于关键字下标范围 [1,keynum]，下标 0 废弃，于是我们查找的下标从 1 开始
    */
    int i=1;
    /*
        查找节点 node 中关键字 key 在节点所在下标或插入该关键字的合适位置
        若某节点中关键字为 2、5、7，所查找的关键字为 1，那么查找到的下标为 1，即 key 应该(存在、插入到)下标为 1 对应的子节点中
    */
    while(i<node->keynum&&key>node->keys[i])
        i++;
    return i;
}

static BTNode* searchBTNode(BTNode* node,Key key)
{
    /*
        查找节点 node 中关键字 key 对应的节点，查找失败则返回 NULL
        i 为 key 所(对应节点、对应子节点)的下标
    */
    int i=1;
    /* currNode 为当前遍历的节点，我们从 node 开始遍历 */
    BTNode* currNode=node;
    while(currNode){
        /* 在当前节点中查找关键字 key 的下标 */
        i=searchIndex(currNode,key);
        /* 查找到的下标为 i*/
        if(key>currNode->keys[i]){
            /* 当 key 大于 i 位置的关键字时，表明 key 可能在 i 下标对应的子节点中，往下遍历 */
            currNode=currNode->child[i];
        }else if(key==currNode->keys[i]){
            /* 当 key 等于 i 位置的关键字时，视为查找成功 */
            break;
        }else if(key<currNode->keys[i]){
            /* 当 key 大小于 i 位置的关键字时，表明 key 可能在 i 下标对应左边的子节点中，往下遍历 */
            currNode=currNode->child[i-1];
        }
    }
    /* 当查找到对应的 key 时，currNode 便是 key 所在节点，否则 currNode 会一直遍历到为 NULL */
    return currNode;
}

static void insertValue(BTNode* node,int index,Key key,eleType value)
{
    /*
        往 node 中下标 index 的位置插入关键字 key 和数据 value
        endPos 为最后位置的下标
    */
    int endPos=node->keynum+1;
    /* 将 index 位置后的关键字、数据往后挪一位 */
    for(int i=0;i<endPos-index;i++){
        node->keys[endPos-i]=node->keys[endPos-i-1];
        node->data[endPos-i]=node->data[endPos-i-1];
    }
    /* 将 index 位置的关键字和数据置为 key、value，关键字总数 +1 */
    node->keys[index]=key;
    node->data[index]=value;
    node->keynum++;
}

static void insertBTNode(BTNode* parent,int index,BTNode* node)
{
    /*
        往 parent 中插入节点 node 到下标为 index 的位置
        endPos 为最后位置的下标
    */
    int endPos=parent->keynum;
    /* 将 index 位置后的孩子指针往后挪一位 */
    for(int i=0;i<endPos-index;i++)
        parent->child[endPos-i]=parent->child[endPos-i-1];
    /* 将 index 位置的孩子指针置为 node，若 node 不为空，将 node 的父节点置为 parent */
    parent->child[index]=node;
    if(node!=NULL)
        node->parent=parent;
}

static eleType deleteValue(BTNode* node,int index)
{
    /*
        删除 node 中下标 index 的位置的关键字和数据，返回被删除的数据
        endPos 为最后位置的下标
        data 存储下标 index 位置对应的数据
    */
    int endPos=node->keynum;
    eleType data=node->data[index];
    /* 将 index 后的关键字、数据往前挪一位，覆盖原有关键字、数据 */
    for(int i=index;i<endPos;i++){
        node->keys[i]=node->keys[i+1];
        node->data[i]=node->data[i+1];
    }
    /* 并将最后位置对应的关键字和数据置为 0、NULL，关键字总数-1 */
    node->keys[endPos]=0;
    node->data[endPos]=NULL;
    node->keynum--;
    return data;
}

static BTNode* deleteBTNode(BTNode* node,int index)
{
    /*
        删除 node 中下标 index 的位置的孩子指针，返回被删除的孩子指针
        endPos 为最后位置的下标
        child 为删除的孩子指针，若 child 不为空，则将 child 父节点置为 NULL
    */
    int endPos=node->keynum;
    BTNode* child=node->child[index];
    if(child!=NULL)
        child->parent=NULL;
    /* 将 index 后的孩子指针往前挪一位，覆盖原有孩子指针 */
    for(int i=index;i<endPos;i++)
        node->child[index]=node->child[index+1];
    /* 将最后位置的孩子指针置为 NULL */
    node->child[endPos]=NULL;
    return child;
}

static void splitBTNode(BTNode* node)
{
    /*
        将 node 分裂
        key、value 临时记录关键字、数据
        parent 记录父节点
        rightChild 节点存储下标 MID_KEY 对应位置右边的所有关键字、数据
    */
    Key key=0;
    eleType value=NULL;
    BTNode* parent=node->parent;
    BTNode* rightChild=NULL;
    /* 创建 rightChild 节点，以 node 为父节点 */
    rightChild=createBTNode(node);
    /* 将 MID_KEY 处的孩子节点插入到 rightChild 的下标 0 位置，并将 node 的该孩子指针置 NULL */
    insertBTNode(rightChild,0,node->child[MID_KEY]);
    node->child[MID_KEY]=NULL;
    /* 将 MID_KEY 右边的所有关键字、数据插入到 rightChild 中 */
    for(int i=1;i<=node->keynum-MID_KEY;i++){
        key=node->keys[MID_KEY+i];
        value=node->data[MID_KEY+i];
        /* 并将 node 的关键字、数据置为 0、NULL */
        node->keys[MID_KEY+i]=0;
        node->data[MID_KEY+i]=NULL;
        /* 插入关键字、数据、孩子节点，并将 node 中该位置的孩子节点置为 NULL */
        insertValue(rightChild,i,key,value);
        insertBTNode(rightChild,i,node->child[MID_KEY+i]);
        node->child[MID_KEY+i]=NULL;
    }
    /* key、value 记录 MID_KEY 位置的关键字、数据 */
    key=node->keys[MID_KEY];
    value=node->data[MID_KEY];
    /* 若 parent 为 NULL，表明 node 为根节点 */
    if(parent==NULL){
        /* 我们不想重新设置根节点，那我们使 node 仍为根节点 */
        BTNode* leftChild=NULL;
        /* 创建 leftChild 节点，将下标为 0 位置的孩子指针插入 leftChild，并将 node 对应的孩子指针置为 NULL */
        leftChild=createBTNode(node);
        insertBTNode(leftChild,0,node->child[0]);
        node->child[0]=NULL;
        /* 将剩余关键字、数据存入 leftChild 中 */
        for(int i=1;i<MID_KEY;i++){
            key=node->keys[i];
            value=node->data[i];
            node->keys[i]=0;
            node->data[i]=NULL;
            /* 插入关键字、数据、孩子节点，并将 node 中该位置的孩子节点置为 NULL */
            insertValue(leftChild,i,key,value);
            insertBTNode(leftChild,i,node->child[i]);
            node->child[i]=NULL;
        }
        /* 由于 key、value 用于临时记录，重新记录 MID_KEY 位置的关键字、数据 */
        key=node->keys[MID_KEY];
        value=node->data[MID_KEY];
        /* 并将 node 的对应关键字、数据置为 0、NULL，将 node 的关键字总数置为 0 */
        node->keys[MID_KEY]=0;
        node->data[MID_KEY]=NULL;
        node->keynum=0;
        /* 将左孩子插入 node，并插入用于分隔的关键字、数据，再插入右孩子 */
        insertBTNode(node,0,leftChild);
        insertValue(node,1,key,value);
        insertBTNode(node,1,rightChild);
    }else{
        /* index 用于查找父节点中适合插入 MID_KEY 的位置 */
        int index=1;
        index=searchIndex(parent,key);
        /*
            由于在此之前 key、value 已记录 MID_KEY 位置的关键字、数据
            故将 node 关键字总数-1，MID_KEY 位置对应关键字、数据置为 0、NULL
        */
        node->keynum=MID_KEY-1;
        node->keys[MID_KEY]=0;
        node->data[MID_KEY]=NULL;
        /* 默认查找到的下标仍需要与 key 进行比较，若 key 仍大于下标 index 位置关键字便往前一位 */
        if(key>parent->keys[index])
            index++;
        /* 将 key、value 存储的 MID_KEY 插入到父节点中，并将生成的右孩子节点插入父节点中 */
        insertValue(parent,index,key,value);
        insertBTNode(parent,index,rightChild);
        /* 若此时父节点的关键字总数超出最大关键字数，进行分裂操作(该操作是递归的) */
        if(parent->keynum>MAX_KEY)
            splitBTNode(parent);
    }
}

static void moveLeft(BTNode* parent,int index,BTNode* leftChild,int dataPos)
{
    /*
        左移
        1. 将 parent 中下标 index 位置关键字、数据移到其前驱节点，即 leftChild 中
        2. 然后将从后继节点，即 rightChild 中移动首个关键字、数据到 index 位置
        3. leftChild 中关键字、数据也需整体左移到 dataPos，将覆盖掉 dataPos 位置的关键字、数据
        leftChild 为 index 位置的前驱节点，暂且叫它左孩子，rightChild 为后继节点，暂且叫它右孩子
    */
    BTNode* rightChild=parent->child[index];
    /* 当父节点或右孩子为空，则直接返回 */
    if(!(parent&&rightChild))
        return;
    /* 当左孩子不为空，则左移并覆盖 dataPos 位置关键字、数据 */
    if(leftChild!=NULL){
        for(int i=dataPos;i<leftChild->keynum;i++){
            leftChild->keys[i]=leftChild->keys[i+1];
            leftChild->data[i]=leftChild->data[i+1];
        }
        if(dataPos>leftChild->keynum){
            leftChild->keynum++;
        }
        leftChild->keys[leftChild->keynum]=parent->keys[index];
        leftChild->data[leftChild->keynum]=parent->data[index];
    }
    /* 将右孩子中下标 0 对应的孩子指针删除，并插入到左孩子中 */
    insertBTNode(leftChild,leftChild->keynum,deleteBTNode(rightChild,0));
    /* 父节点 index 位置关键字、数据将用右孩子的首位的关键字、数据覆盖，并删除 rightChild 的首位关键字、数据 */
    parent->keys[index]=rightChild->keys[1];
    parent->data[index]=rightChild->data[1];
    deleteValue(rightChild,1);
}

static void moveRight(BTNode* parent,int index,BTNode* rightChild,int dataPos)
{
    /*
        右移
        1. 将 parent 中下标 index 位置关键字、数据移到其后继节点，即 rightChild 中
        2. 然后将从前驱节点，即 leftChild 中移动末尾关键字、数据到 index 位置
        3. rightChild 中关键字、数据也需整体右移到 dataPos，将覆盖掉 dataPos 位置的关键字、数据
        leftChild 为 index 位置的前驱节点，暂且叫它左孩子，rightChild 为后继节点，暂且叫它右孩子
    */
    BTNode* leftChild=parent->child[index-1];
    /* 当父节点或左孩子为空，则直接返回 */
    if(!(parent&&leftChild))
        return;
    /* 当右孩子不为空，则右移并覆盖 dataPos 位置关键字、数据 */
    if(rightChild!=NULL){
        //right child move to left
        if(dataPos>rightChild->keynum){
            rightChild->keynum++;
            dataPos=rightChild->keynum;
        }
        for(int i=dataPos;i>1;i--){
            rightChild->keys[i]=rightChild->keys[i-1];
            rightChild->data[i]=rightChild->data[i-1];
        }
        rightChild->keys[1]=parent->keys[index];
        rightChild->data[1]=parent->data[index];
    }
    /* 将左孩子中末尾下标对应的孩子指针删除，并插入到右孩子中 */
    insertBTNode(rightChild,0,deleteBTNode(leftChild,leftChild->keynum));
    /* 父节点 index 位置关键字、数据将用左孩子的末尾的关键字、数据覆盖，并删除 leftChild 的末尾关键字、数据 */
    parent->keys[index]=leftChild->keys[leftChild->keynum];
    parent->data[index]=leftChild->data[leftChild->keynum];
    deleteValue(leftChild,leftChild->keynum);
}

static void combineBTNode(BTNode* parent,int index)
{
    /*
        合并 parent 中下标 index 对应的前驱和后继节点
        1. 找出前驱节点、后继结点中关键字总数小于最小值的作为被销毁的节点
        2. 然后下标 index 对应的 、被销毁节点的关键字、数据移入未被销毁的节点中
        3. 释放那个关键字总数小于最小值的节点
    */
    if(!parent||index<1)
        return;
    /* leftChild 为 index 位置的前驱节点，暂且叫它左孩子，rightChild 为后继节点，暂且叫它右孩子 */
    BTNode* leftChild=parent->child[index-1];
    BTNode* rightChild=parent->child[index];
    /* 当左孩子或右孩子为空，则直接返回 */
    if(!(leftChild&&rightChild))
        return;
    /* key、value 用于临时存储关键字、数据 */
    Key key=0;
    eleType value=NULL;
    /* 若左孩子关键字数量小于最小值 */
    if(leftChild->keynum<MIN_KEY){
        //parent key move to left node
        insertValue(leftChild,leftChild->keynum+1,parent->keys[index],parent->data[index]);
        //right node's child move to left node
        insertBTNode(leftChild,leftChild->keynum,rightChild->child[0]);
        //right children move to left node
        for(int i=1;i<=rightChild->keynum;i++){
            key=rightChild->keys[i];
            value=rightChild->data[i];
            insertValue(leftChild,leftChild->keynum+1,key,value);
            insertBTNode(leftChild,leftChild->keynum,rightChild->child[i]);
        }
        free(deleteBTNode(parent,index));
    /* 若右孩子关键字数量小于最小值 */
    }else if(rightChild->keynum<MIN_KEY){
        //parent key move to right node
        insertValue(rightChild,1,parent->keys[index],parent->data[index]);
        insertBTNode(rightChild,0,leftChild->child[0]);
        for(int i=1;i<=leftChild->keynum;i++){
            key=leftChild->keys[i];
            value=leftChild->data[i];
            insertValue(rightChild,1,key,value);
            insertBTNode(rightChild,i,leftChild->child[i]);
        }
        free(deleteBTNode(parent,index-1));
    }
    /* 若父节点的父节点为空，即 parent 若为根节点 */
    if(parent->parent==NULL){
        deleteValue(parent,index);
        if(parent->keynum==0){
            BTNode* node=parent->child[0];
            //copy leftChild to parent
            parent->keynum=node->keynum;
            parent->child[0]=node->child[0];
            if(node->child[0]!=NULL)
                node->child[0]->parent=parent;
            for(int i=1;i<=parent->keynum;i++){
                parent->keys[i]=node->keys[i];
                parent->data[i]=node->data[i];
                parent->child[i]=node->child[i];
                if(node->child[i]!=NULL)
                    node->child[i]->parent=parent;
            }
            free(node);
        }
    }else{
        //update node
        BTNode* node=parent;
        parent=node->parent;
        int j=searchIndex(parent,node->keys[index]);
        if(node->keys[index]<parent->keys[j])
            j--;
        deleteValue(node,index);
        if(node->keynum<MIN_KEY){
            balanceBTNode(parent,j);
        }
    }
}

static void balanceBTNode(BTNode* parent,int index)
{
    /* 平衡 parent 中下标 index 位置的子节点 */
    if(parent==NULL)
        return;
    BTNode* node=parent->child[index];
    //move to left
    if(index+1<=parent->keynum&&parent->child[index+1]->keynum>MIN_KEY){
        //right node is rich node
        moveLeft(parent,index+1,node,node->keynum+1);
    }
    //move to right
    else if(index-1>=0&&parent->child[index-1]->keynum>MIN_KEY){
        //left node is rich node
        moveRight(parent,index,node,node->keynum+1);
    }
    //right and left are not rich node
    else{
        if(index-1>=0){
            //node is rightChild
        }else if(index+1<=parent->keynum){
            //node is leftChild
            index++;
        }
        combineBTNode(parent,index);
    }
}

/* 初始化 B 树 */
void bTreeInitalize(BTree *tree)
{
    /* 创建一个父节点为 NULL 的 B 树节点作为 B 树，即根节点 */
    if(tree==NULL)
        return;
    *tree=createBTNode(NULL);
}

/* 打印 B 树节点，用于调试 */
void bTreeShowNode(BTNode* node)
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

/* 层序遍历并打印 B 树所有关键字 */
void bTreeShow(BTree tree){
    if(tree==NULL)
        return;
    linkQueue queue;
    BTNode* currNode=NULL;
    linkQueueInitalize(&queue);
    linkQueueEnqueue(queue,tree);
    int i=1;
    while(!linkQueueIsEmpty(queue)){
        currNode=(BTNode*)linkQueueFront(queue);
        //showBTree(currNode);
        linkQueueDequeue(queue);
        if(currNode->child[0]!=NULL){
            linkQueueEnqueue(queue,currNode->child[0]);
        }
        while(i<=currNode->keynum){
            printf("%d",currNode->keys[i]);
            if(i!=currNode->keynum)
                printf(",");
            else
                printf(" ");
            if(currNode->child[i]!=NULL)
                linkQueueEnqueue(queue,currNode->child[i]);
            i++;
        }
        i=1;
    }
    printf("\n");
    linkQueueFree(&queue);
}

/* 先序遍历 B 树 */
void bTreePreOrderTraversal(BTree tree, void (*traversal)(void *))
{
    if(tree==NULL)
        return;
    BTNode* currNode=tree;
    for(int i=0;currNode&&i<=currNode->keynum;i++){
        if(i+1<=currNode->keynum)
            traversal(currNode->data[i+1]);
        if(currNode->child[i]!=NULL)
            bTreePreOrderTraversal(currNode->child[i],traversal);
    }
    if(currNode->parent==NULL)
        printf("\n");
}

/* 中序遍历 B 树 */
void bTreeInOrderTraversal(BTree tree, void (*traversal)(void *))
{
    if(tree==NULL)
        return;
    BTNode* currNode=tree;
    for(int i=0;currNode&&i<=currNode->keynum;i++){
        if(currNode->child[i]!=NULL)
            bTreeInOrderTraversal(currNode->child[i],traversal);
        if(i+1<=currNode->keynum)
            traversal(currNode->data[i+1]);
    }
    if(currNode->parent==NULL)
        printf("\n");
}

/* 层序遍历 B 树 */
void bTreeLevelOrderTraversal(BTree tree, void (*traversal)(void *))
{
    if(tree==NULL)
        return;
    //queue
    linkQueue queue;
    BTNode* currNode=NULL;
    linkQueueInitalize(&queue);
    linkQueueEnqueue(queue,tree);
    int i=1;
    while(!linkQueueIsEmpty(queue)){
        currNode=(BTNode*)linkQueueFront(queue);
        linkQueueDequeue(queue);
        if(currNode->child[0]!=NULL){
            linkQueueEnqueue(queue,currNode->child[0]);
        }
        while(i<=currNode->keynum){
            traversal(currNode->data[i]);
            if(currNode->child[i]!=NULL)
                linkQueueEnqueue(queue,currNode->child[i]);
            i++;
        }
        i=1;
    }
    printf("\n");
    linkQueueFree(&queue);
}

/* 在 B 树中查找关键字对应的数据 */
eleType bTreeSearch(BTree tree, Key key)
{
    /*
        search data by key in b-tree
    */
    int i=1;
    BTNode* node=searchBTNode(tree,key);
    if(node!=NULL)
        i=searchIndex(node,key);
    return node!=NULL?node->data[i]:NULL;
}

/* 往 B 树中插入关键字、数据 */
bool bTreeInsert(BTree tree, Key key, eleType value)
{
    /*
        insert data to b-tree by key
    */
    int i=1;
    BTNode* preNode=NULL;
    BTNode* currNode=tree;
    while(currNode){
        i=searchIndex(currNode,key);
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
    i=searchIndex(currNode,key);
    if(i==currNode->keynum&&key>currNode->keys[i])
        i++;
    insertValue(currNode,i,key,value);
    if(currNode->keynum>MAX_KEY){
        splitBTNode(currNode);
    }
    return true;
}

/* 在 B 树中删除某个关键字及数据 */
eleType bTreeDelete(BTree tree, Key key)
{
    /*
        delete data on b-tree by key
    */
    if(tree==NULL)
        return NULL;
    int i=1;
    BTNode* parent=NULL;
    BTNode* currNode=tree;
    eleType data=NULL;
    currNode=searchBTNode(tree,key);
    if(currNode==NULL)
        return NULL;
    i=searchIndex(currNode,key);
    //save data
    data=currNode->data[i];
    //this node is leaf node
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
            int j=searchIndex(parent,currNode->keys[i]);
            if(currNode->keys[i]<parent->keys[j])
                j--;
            deleteValue(currNode,i);
            balanceBTNode(parent,j);
        }
    }else{
        //get precursor key-value
        BTNode* target=currNode->child[i-1];
        parent=target->parent;
        int j=searchIndex(parent,target->keys[target->keynum]);
        if(target->keys[target->keynum]<parent->keys[j])
            j--;
        while(target->child[target->keynum]!=NULL)
            target=target->child[target->keynum];
        currNode->keys[i]=target->keys[target->keynum];
        currNode->data[i]=target->data[target->keynum];
        deleteValue(target,target->keynum);
        if(target->keynum<MIN_KEY){
            balanceBTNode(target->parent,j);
        }
    }
    return data;
}

/* 释放 B 树 */
void bTreeFree(BTree *tree)
{
    /*
        free b-tree
    */
    if(tree==NULL&&*tree==NULL)
        return;
    //queue
    linkQueue queue;
    BTNode* currNode=NULL;
    linkQueueInitalize(&queue);
    linkQueueEnqueue(queue,*tree);
    *tree=NULL;
    int i=1;
    while(!linkQueueIsEmpty(queue)){
        currNode=(BTNode*)linkQueueFront(queue);
        linkQueueDequeue(queue);
        if(currNode->child[0]!=NULL){
            linkQueueEnqueue(queue,currNode->child[0]);
            while(i<=currNode->keynum){
                if(currNode->child[i]!=NULL)
                    linkQueueEnqueue(queue,currNode->child[i]);
                i++;
            }
        }
        free(currNode);
        i=1;
    }
    linkQueueFree(&queue);
}