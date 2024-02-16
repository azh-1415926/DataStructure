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
static void insertData(BTNode* node,int index,Key key,eleType data);
/* 插入指定节点对应下标处的子节点 */
static void insertBTNode(BTNode* parent,int index,BTNode* node);
/* 在指定节点中删除对应下标上的关键字及数据 */
static eleType deleteData(BTNode* node,int index);
/* 删除指定节点对应下标的子节点 */
static BTNode* deleteBTNode(BTNode* node,int index);
/* 指定节点执行分裂操作 */
static void splitBTNode(BTNode* node);
/* 将父节点指定下标的 */
static void moveLeft(BTNode* parent,int index,BTNode* leftChild,int removePos);
static void moveRight(BTNode* parent,int index,BTNode* rightChild,int removePos);
static void combineBTNode(BTNode* parent,int index);
static void balanceBTNode(BTNode* parent,int index);

static BTNode* createBTNode(BTNode* parent)
{
    /* 创建一个 BTNode 节点，设置好初始值后返回 */
    BTNode* node=(BTNode*)malloc(sizeof(BTNode));
    /* 关键字数 keynums 置零，父节点 parent 置为为传入的 parent */
    node->sumOfKey=0;
    node->parent=parent;
    /* 所有关键字 keys 置为 0，所有数据 data 置 NULL，子节点 children 置 NULL */
    for(int i=0;i<=M;i++)
    {
        // node->keys[i]=0;
        // node->data[i]=0;
        node->children[i]=NULL;
    }
    return node;
}

static int searchIndex(BTNode *node,Key key)
{
    /*
        查找 node 中 key (对应、对应子节点)的下标
        由于关键字下标范围 [1,sumOfKey]，下标 0 废弃，于是我们查找的下标从 1 开始
    */
    int i=1;
    /*
        查找节点 node 中关键字 key 在节点所在下标或插入该关键字的合适位置
        若某节点中关键字为 2、5、7，所查找的关键字为 1，那么查找到的下标为 1，即 key 应该(存在、插入到)下标为 1 对应的子节点中
    */
    while(i<node->sumOfKey&&key>node->keys[i])
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
    while(currNode)
    {
        /* 在当前节点中查找关键字 key 的下标 */
        i=searchIndex(currNode,key);
        /* 查找到的下标为 i*/
        if(key>currNode->keys[i])
        {
            /* 当 key 大于 i 位置的关键字时，表明 key 可能在 i 下标对应的子节点中，往下遍历 */
            currNode=currNode->children[i];
        }else if(key==currNode->keys[i])
        {
            /* 当 key 等于 i 位置的关键字时，视为查找成功 */
            break;
        }else if(key<currNode->keys[i])
        {
            /* 当 key 大小于 i 位置的关键字时，表明 key 可能在 i 下标对应左边的子节点中，往下遍历 */
            currNode=currNode->children[i-1];
        }
    }
    /* 当查找到对应的 key 时，currNode 便是 key 所在节点，否则 currNode 会一直遍历到为 NULL */
    return currNode;
}

static void insertData(BTNode* node,int index,Key key,eleType data)
{
    /*
        往 node 中下标 index 的位置插入关键字 key 和数据 data
        endPos 为最后位置的下标
    */
    int endPos=node->sumOfKey+1;
    /* 将 index 位置后的关键字、数据往后挪一位 */
    for(int i=0;i<endPos-index;i++)
    {
        node->keys[endPos-i]=node->keys[endPos-i-1];
        node->data[endPos-i]=node->data[endPos-i-1];
    }
    /* 将 index 位置的关键字和数据置为 key、value，关键字总数 +1 */
    node->keys[index]=key;
    node->data[index]=data;
    node->sumOfKey++;
}

static void insertBTNode(BTNode* parent,int index,BTNode* node)
{
    /*
        往 parent 中插入节点 node 到下标为 index 的位置
        endPos 为最后位置的下标
    */
    int endPos=parent->sumOfKey;
    /* 将 index 位置后的孩子指针往后挪一位 */
    for(int i=0;i<endPos-index;i++)
        parent->children[endPos-i]=parent->children[endPos-i-1];
    /* 将 index 位置的孩子指针置为 node，若 node 不为空，将 node 的父节点置为 parent */
    parent->children[index]=node;
    if(node!=NULL)
        node->parent=parent;
}

static eleType deleteData(BTNode* node,int index)
{
    /*
        删除 node 中下标 index 的位置的关键字和数据，返回被删除的数据
        endPos 为最后位置的下标
        data 存储下标 index 位置对应的数据
    */
    int endPos=node->sumOfKey;
    eleType data=node->data[index];
    /* 将 index 后的关键字、数据往前挪一位，覆盖原有关键字、数据 */
    for(int i=index;i<endPos;i++)
    {
        node->keys[i]=node->keys[i+1];
        node->data[i]=node->data[i+1];
    }
    /* 并将最后位置对应的关键字和数据置为 0、NULL，关键字总数-1 */
    // node->keys[endPos]=0;
    // node->data[endPos]=NULL;
    node->sumOfKey--;
    return data;
}

static BTNode* deleteBTNode(BTNode* node,int index)
{
    /*
        删除 node 中下标 index 的位置的孩子指针，返回被删除的孩子指针
        endPos 为最后位置的下标
        children 为删除的孩子指针，若 children 不为空，则将 children 父节点置为 NULL
    */
    int endPos=node->sumOfKey;
    BTNode* children=node->children[index];
    if(children!=NULL)
        children->parent=NULL;
    /* 将 index 后的孩子指针往前挪一位，覆盖原有孩子指针 */
    for(int i=index;i<endPos;i++)
        node->children[index]=node->children[index+1];
    /* 将最后位置的孩子指针置为 NULL */
    node->children[endPos]=NULL;
    return children;
}

static void splitBTNode(BTNode* node)
{
    /*
        将 node 分裂
        key、value 临时记录关键字、数据
        parent 记录父节点
        rightChild 节点存储下标 MID_KEY 对应位置右边的所有关键字、数据
    */
    Key key;//=0;
    eleType data;//=NULL;
    BTNode* parent=node->parent;
    BTNode* rightChild=NULL;
    /* 创建 rightChild 节点，以 node 为父节点 */
    rightChild=createBTNode(node);
    /* 将 MID_KEY 处的孩子节点插入到 rightChild 的下标 0 位置，并将 node 的该孩子指针置 NULL */
    insertBTNode(rightChild,0,node->children[MID_KEY]);
    node->children[MID_KEY]=NULL;
    /* 将 MID_KEY 右边的所有关键字、数据插入到 rightChild 中 */
    for(int i=1;i<=node->sumOfKey-MID_KEY;i++)
    {
        key=node->keys[MID_KEY+i];
        data=node->data[MID_KEY+i];
        // /* 并将 node 的关键字、数据置为 0、NULL */
        // node->keys[MID_KEY+i]=0;
        // node->data[MID_KEY+i]=NULL;
        /* 插入关键字、数据、孩子节点，并将 node 中该位置的孩子节点置为 NULL */
        insertData(rightChild,i,key,data);
        insertBTNode(rightChild,i,node->children[MID_KEY+i]);
        node->children[MID_KEY+i]=NULL;
    }
    /* key、value 记录 MID_KEY 位置的关键字、数据 */
    key=node->keys[MID_KEY];
    data=node->data[MID_KEY];
    /* 若 parent 为 NULL，表明 node 为根节点 */
    if(parent==NULL)
    {
        /* 我们不想重新设置根节点，那我们使 node 仍为根节点 */
        BTNode* leftChild=NULL;
        /* 创建 leftChild 节点，将下标为 0 位置的孩子指针插入 leftChild，并将 node 对应的孩子指针置为 NULL */
        leftChild=createBTNode(node);
        insertBTNode(leftChild,0,node->children[0]);
        node->children[0]=NULL;
        /* 将剩余关键字、数据存入 leftChild 中 */
        for(int i=1;i<MID_KEY;i++)
        {
            key=node->keys[i];
            data=node->data[i];
            // node->keys[i]=0;
            // node->data[i]=NULL;
            /* 插入关键字、数据、孩子节点，并将 node 中该位置的孩子节点置为 NULL */
            insertData(leftChild,i,key,data);
            insertBTNode(leftChild,i,node->children[i]);
            node->children[i]=NULL;
        }
        /* 由于 key、value 用于临时记录，重新记录 MID_KEY 位置的关键字、数据 */
        key=node->keys[MID_KEY];
        data=node->data[MID_KEY];
        // /* 并将 node 的对应关键字、数据置为 0、NULL，将 node 的关键字总数置为 0 */
        // node->keys[MID_KEY]=0;
        // node->data[MID_KEY]=NULL;
        node->sumOfKey=0;
        /* 将左孩子插入 node，并插入用于分隔的关键字、数据，再插入右孩子 */
        insertBTNode(node,0,leftChild);
        insertData(node,1,key,data);
        insertBTNode(node,1,rightChild);
    }
    else
    {
        /* index 用于查找父节点中适合插入 MID_KEY 的位置 */
        int index=1;
        index=searchIndex(parent,key);
        /*
            由于在此之前 key、value 已记录 MID_KEY 位置的关键字、数据
            故将 node 关键字总数-1，MID_KEY 位置对应关键字、数据置为 0、NULL
        */
        node->sumOfKey=MID_KEY-1;
        // node->keys[MID_KEY]=0;
        // node->data[MID_KEY]=NULL;
        /* 默认查找到的下标仍需要与 key 进行比较，若 key 仍大于下标 index 位置关键字便往前一位 */
        if(key>parent->keys[index])
            index++;
        /* 将 key、value 存储的 MID_KEY 插入到父节点中，并将生成的右孩子节点插入父节点中 */
        insertData(parent,index,key,data);
        insertBTNode(parent,index,rightChild);
        /* 若此时父节点的关键字总数超出最大关键字数，进行分裂操作(该操作是递归的) */
        if(parent->sumOfKey>MAX_KEY)
            splitBTNode(parent);
    }
}

static void moveLeft(BTNode* parent,int index,BTNode* leftChild,int removePos)
{
    /*
        左移
        1. 将 parent 中下标 index 位置关键字、数据移到其前驱节点，即 leftChild 中
        2. 然后将从后继节点，即 rightChild 中移动首个关键字、数据到 index 位置
        3. leftChild 中关键字、数据也需整体左移到 dataPos，将覆盖掉 removePos 位置的关键字、数据
        leftChild 为 index 位置的前驱节点，暂且叫它左孩子，rightChild 为后继节点，暂且叫它右孩子
    */
    BTNode* rightChild=parent->children[index];
    /* 当父节点或右孩子为空，则直接返回 */
    if(!(parent&&rightChild))
        return;
    /* 当左孩子不为空，则左移并覆盖 removePos 位置关键字、数据 */
    if(leftChild!=NULL)
    {
        for(int i=removePos;i<leftChild->sumOfKey;i++)
        {
            leftChild->keys[i]=leftChild->keys[i+1];
            leftChild->data[i]=leftChild->data[i+1];
        }
        if(removePos>leftChild->sumOfKey)
        {
            leftChild->sumOfKey++;
        }
        leftChild->keys[leftChild->sumOfKey]=parent->keys[index];
        leftChild->data[leftChild->sumOfKey]=parent->data[index];
    }
    /* 将右孩子中下标 0 对应的孩子指针删除，并插入到左孩子中 */
    insertBTNode(leftChild,leftChild->sumOfKey,deleteBTNode(rightChild,0));
    /* 父节点 index 位置关键字、数据将用右孩子的首位的关键字、数据覆盖，并删除 rightChild 的首位关键字、数据 */
    parent->keys[index]=rightChild->keys[1];
    parent->data[index]=rightChild->data[1];
    deleteData(rightChild,1);
}

static void moveRight(BTNode* parent,int index,BTNode* rightChild,int removePos)
{
    /*
        右移
        1. 将 parent 中下标 index 位置关键字、数据移到其后继节点，即 rightChild 中
        2. 然后将从前驱节点，即 leftChild 中移动末尾关键字、数据到 index 位置
        3. rightChild 中关键字、数据也需整体右移到 dataPos，将覆盖掉 removePos 位置的关键字、数据
        leftChild 为 index 位置的前驱节点，暂且叫它左孩子，rightChild 为后继节点，暂且叫它右孩子
    */
    BTNode* leftChild=parent->children[index-1];
    /* 当父节点或左孩子为空，则直接返回 */
    if(!(parent&&leftChild))
        return;
    /* 当右孩子不为空，则右移并覆盖 removePos 位置关键字、数据 */
    if(rightChild!=NULL)
    {
        //right children move to left
        if(removePos>rightChild->sumOfKey)
        {
            rightChild->sumOfKey++;
            removePos=rightChild->sumOfKey;
        }
        for(int i=removePos;i>1;i--)
        {
            rightChild->keys[i]=rightChild->keys[i-1];
            rightChild->data[i]=rightChild->data[i-1];
        }
        rightChild->keys[1]=parent->keys[index];
        rightChild->data[1]=parent->data[index];
    }
    /* 将左孩子中末尾下标对应的孩子指针删除，并插入到右孩子中 */
    insertBTNode(rightChild,0,deleteBTNode(leftChild,leftChild->sumOfKey));
    /* 父节点 index 位置关键字、数据将用左孩子的末尾的关键字、数据覆盖，并删除 leftChild 的末尾关键字、数据 */
    parent->keys[index]=leftChild->keys[leftChild->sumOfKey];
    parent->data[index]=leftChild->data[leftChild->sumOfKey];
    deleteData(leftChild,leftChild->sumOfKey);
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
    BTNode* leftChild=parent->children[index-1];
    BTNode* rightChild=parent->children[index];
    /* 当左孩子或右孩子为空，则直接返回 */
    if(!(leftChild&&rightChild))
        return;
    /* key、value 用于临时存储关键字、数据 */
    Key key;//=0;
    eleType data;//=NULL;
    /* 若左孩子关键字数量小于最小值 */
    if(leftChild->sumOfKey<MIN_KEY)
    {
        //parent key move to left node
        insertData(leftChild,leftChild->sumOfKey+1,parent->keys[index],parent->data[index]);
        //right node's children move to left node
        insertBTNode(leftChild,leftChild->sumOfKey,rightChild->children[0]);
        //right children move to left node
        for(int i=1;i<=rightChild->sumOfKey;i++)
        {
            key=rightChild->keys[i];
            data=rightChild->data[i];
            insertData(leftChild,leftChild->sumOfKey+1,key,data);
            insertBTNode(leftChild,leftChild->sumOfKey,rightChild->children[i]);
        }
        free(deleteBTNode(parent,index));
    /* 若右孩子关键字数量小于最小值 */
    }else if(rightChild->sumOfKey<MIN_KEY)
    {
        //parent key move to right node
        insertData(rightChild,1,parent->keys[index],parent->data[index]);
        insertBTNode(rightChild,0,leftChild->children[0]);
        for(int i=1;i<=leftChild->sumOfKey;i++)
        {
            key=leftChild->keys[i];
            data=leftChild->data[i];
            insertData(rightChild,1,key,data);
            insertBTNode(rightChild,i,leftChild->children[i]);
        }
        free(deleteBTNode(parent,index-1));
    }
    /* 若父节点的父节点为空，即 parent 若为根节点 */
    if(parent->parent==NULL)
    {
        deleteData(parent,index);
        if(parent->sumOfKey==0)
        {
            BTNode* node=parent->children[0];
            //copy leftChild to parent
            parent->sumOfKey=node->sumOfKey;
            parent->children[0]=node->children[0];
            if(node->children[0]!=NULL)
                node->children[0]->parent=parent;
            for(int i=1;i<=parent->sumOfKey;i++)
            {
                parent->keys[i]=node->keys[i];
                parent->data[i]=node->data[i];
                parent->children[i]=node->children[i];
                if(node->children[i]!=NULL)
                    node->children[i]->parent=parent;
            }
            free(node);
        }
    }
    else
    {
        //update node
        BTNode* node=parent;
        parent=node->parent;
        int j=searchIndex(parent,node->keys[index]);
        if(node->keys[index]<parent->keys[j])
            j--;
        deleteData(node,index);
        if(node->sumOfKey<MIN_KEY)
        {
            balanceBTNode(parent,j);
        }
    }
}

static void balanceBTNode(BTNode* parent,int index)
{
    /* 平衡 parent 中下标 index 位置的子节点 */
    if(parent==NULL)
        return;
    BTNode* node=parent->children[index];
    //move to left
    if(index+1<=parent->sumOfKey&&parent->children[index+1]->sumOfKey>MIN_KEY)
    {
        //right node is rich node
        moveLeft(parent,index+1,node,node->sumOfKey+1);
    }
    //move to right
    else if(index-1>=0&&parent->children[index-1]->sumOfKey>MIN_KEY)
    {
        //left node is rich node
        moveRight(parent,index,node,node->sumOfKey+1);
    }
    //right and left are not rich node
    else
    {
        if(index-1>=0)
        {
            //node is rightChild
        }else if(index+1<=parent->sumOfKey)
        {
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
    printf("\tkeynum:%d\n\t",node->sumOfKey);
    for(int i=1;i<=M;i++)
    {
        printf("%d ",node->keys[i]);
    }
    printf("\n");
    printf("\tparent:%p\n\t",node->parent);
    for(int i=0;i<=M;i++)
    {
        printf("%p ",node->children[i]);
    }
    printf("\n");
}

/* 层序遍历并打印 B 树所有关键字 */
void bTreeShow(BTree tree)
{
    if(tree==NULL)
        return;
    linkQueue queue;
    BTNode* currNode=NULL;
    linkQueueInitalize(&queue);
    linkQueueEnqueue(queue,tree);
    int i=1;
    while(!linkQueueIsEmpty(queue))
    {
        currNode=(BTNode*)linkQueueFront(queue);
        //showBTree(currNode);
        linkQueueDequeue(queue);
        if(currNode->children[0]!=NULL)
        {
            linkQueueEnqueue(queue,currNode->children[0]);
        }
        while(i<=currNode->sumOfKey)
        {
            printf("%d",currNode->keys[i]);
            if(i!=currNode->sumOfKey)
                printf(",");
            else
                printf(" ");
            if(currNode->children[i]!=NULL)
                linkQueueEnqueue(queue,currNode->children[i]);
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
    for(int i=0;currNode&&i<=currNode->sumOfKey;i++)
    {
        if(i+1<=currNode->sumOfKey)
            traversal(currNode->data[i+1]);
        if(currNode->children[i]!=NULL)
            bTreePreOrderTraversal(currNode->children[i],traversal);
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
    for(int i=0;currNode&&i<=currNode->sumOfKey;i++)
    {
        if(currNode->children[i]!=NULL)
            bTreeInOrderTraversal(currNode->children[i],traversal);
        if(i+1<=currNode->sumOfKey)
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
    while(!linkQueueIsEmpty(queue))
    {
        currNode=(BTNode*)linkQueueFront(queue);
        linkQueueDequeue(queue);
        if(currNode->children[0]!=NULL)
        {
            linkQueueEnqueue(queue,currNode->children[0]);
        }
        while(i<=currNode->sumOfKey)
        {
            traversal(currNode->data[i]);
            if(currNode->children[i]!=NULL)
                linkQueueEnqueue(queue,currNode->children[i]);
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
bool bTreeInsert(BTree tree, Key key, eleType data)
{
    /*
        insert data to b-tree by key
    */
    int i=1;
    BTNode* preNode=NULL;
    BTNode* currNode=tree;
    while(currNode)
    {
        i=searchIndex(currNode,key);
        if(key>currNode->keys[i])
        {
            preNode=currNode;
            currNode=currNode->children[i];
        }else if(key==currNode->keys[i])
        {
            return false;
        }else if(key<currNode->keys[i])
        {
            preNode=currNode;
            currNode=currNode->children[i-1];
        }
    }
    if(currNode==NULL)
        currNode=preNode;
    i=searchIndex(currNode,key);
    if(i==currNode->sumOfKey&&key>currNode->keys[i])
        i++;
    insertData(currNode,i,key,data);
    if(currNode->sumOfKey>MAX_KEY)
    {
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
    if(currNode->children[0]==NULL)
    {
        //key greater than min
        if(currNode->sumOfKey>MIN_KEY)
        {
            deleteData(currNode,i);
        //key equal to min
        }else{
            parent=currNode->parent;
            //leaf node is root
            if(parent==NULL)
            {
                deleteData(currNode,1);
                return data;
            }
            //normal node
            int j=searchIndex(parent,currNode->keys[i]);
            if(currNode->keys[i]<parent->keys[j])
                j--;
            deleteData(currNode,i);
            balanceBTNode(parent,j);
        }
    }else{
        //get precursor key-data
        BTNode* target=currNode->children[i-1];
        parent=target->parent;
        int j=searchIndex(parent,target->keys[target->sumOfKey]);
        if(target->keys[target->sumOfKey]<parent->keys[j])
            j--;
        while(target->children[target->sumOfKey]!=NULL)
            target=target->children[target->sumOfKey];
        currNode->keys[i]=target->keys[target->sumOfKey];
        currNode->data[i]=target->data[target->sumOfKey];
        deleteData(target,target->sumOfKey);
        if(target->sumOfKey<MIN_KEY)
        {
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
    while(!linkQueueIsEmpty(queue))
    {
        currNode=(BTNode*)linkQueueFront(queue);
        linkQueueDequeue(queue);
        if(currNode->children[0]!=NULL)
        {
            linkQueueEnqueue(queue,currNode->children[0]);
            while(i<=currNode->sumOfKey)
            {
                if(currNode->children[i]!=NULL)
                    linkQueueEnqueue(queue,currNode->children[i]);
                i++;
            }
        }
        free(currNode);
        i=1;
    }
    linkQueueFree(&queue);
}