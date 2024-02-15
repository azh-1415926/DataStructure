#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <functional>
#include <simpleDS/linkQueue.hpp>

namespace azh
{
    /* M 为 B 树的阶数，当前为 3 阶 B 树，即 2-3 树 */
    const int M=3;
    const int MAX_KEY=(M-1);
    const int MIN_KEY=((M-1)/2);
    const int MID_KEY=((M+1)/2);

    /* BTree 模板类的前置声明，方便 BTNode 将其设为友元类 */
    template<class eleType,class Key>
    class BTree;

    /*
        BTNode 为 B 树的节点
            模板参数介绍
                eleType 为数据类型
                Key 为关键字类型
                    若需要使用其他关键字，请重载 Key 类型的一些运算符
                后续将调整 eleType、Key 的顺序
    */
    template<class eleType,class Key=int>
    class BTNode
    {
        /* 将 BTree 模板类设为友元类，方便访问当前类的私有成员 */
        friend class BTree<eleType,Key>;
        private:
            /* m_SumOfKey 为当前节点的关键字数量 */
            int m_SumOfKey;
            /* keys、data 用于存放关键字、数据 */
            Key m_Keys[M+1];
            eleType m_Data[M+1];
            /* parent 为父节点，默认为空 */
            BTNode<eleType,Key>* m_Parent;
            /* child 为所有子节点 */
            BTNode<eleType,Key>* m_Children[M+1];
            /* 构造一个空的节点 */
            BTNode(BTNode<eleType,Key>* parent=nullptr);
            ~BTNode() {  }
            /* 查找当前节点中大于等于指定关键字 key 的最大下标 */
            int searchIndex(Key key);
            /* 插入数据到指定下标位置，且将关键字数量加一 */
            void insertData(int index,Key key,eleType data);
            /* 插入子节点指针到指定下标位置，关键字数量将不变 */
            void insertBTNode(int index,BTNode<eleType,Key>* node);
            /* 删除指定下标位置的数据，关键字数量将减一 */
            eleType deleteData(int index);
            /* 删除指定下标位置的子节点指针，关键字数量将不变，需要手动释放其返回删除的子节点 */
            BTNode<eleType,Key>* deleteBTNode(int index);
    };
    
    template<class eleType,class Key=int>
    class BTree
    {
        private:
            /* m_FuncOfTraversal 是用于遍历的函数，m_Root 为该 B 树的根节点 */
            std::function<void(eleType)> m_FuncOfTraversal;
            BTNode<eleType,Key>* m_Root;

            /* 根据 key 在全局查找指定节点，若不存在该关键字则返回 nullptr */
            BTNode<eleType,Key>* searchBTNode(Key key);
            /* 分裂指定节点，传入的 node 仍然为分裂后的根节点 */
            static void splitBTNode(BTNode<eleType,Key>* node);
            /* 将父节点中下标位置为 index 的关键字左移到 index 关键字对应的左子节点，到其 dataPos 位置停下（即覆盖 dataPos 位置的关键字、数据），若左子节点为空，则将父节点的第一个关键字覆盖，不处理左子节点 */
            static void moveLeft(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* leftChild,int dataPos);
            /* 同理，将父节点中下标位置为 index 的关键字右移到 index 关键字对应的右子节点，到其 dataPos 位置停下，若右子节点为空，则将父节点的最后一个关键字覆盖，不处理右子节点 */
            static void moveRight(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* rightChild,int dataPos);
            /* 合并父节点中指定下标位置的左右子节点 */
            static void combineBTNode(BTNode<eleType,Key>* parent,int index);
            /* 平衡父节点中指定下标位置的左右子节点 */
            static void balanceBTNode(BTNode<eleType,Key>* parent,int index);

        public:
            /* 构造 B 树，即创建根节点 */
            BTree(): m_Root(new BTNode<eleType,Key>) {  };
            ~BTree();

            /* 设置遍历函数 */
            inline void setTraversalFunction(const std::function<void(eleType)>& func) { m_FuncOfTraversal=func; }

            /* 查找 key 对应的数据 */
            eleType search(Key key);
            /* 创建关键字为 key、数据为 data 的节点，并插入到 B 树中 */
            bool insert(Key key,eleType data);
            /* 在 B 树中删除关键字为 key 的节点 */
            bool erase(Key key);
            /* 遍历关键字 */
            void show();
            /* 前序遍历 */
            void preOrderTraversal(BTNode<eleType,Key>* node=nullptr);
            /* 中序遍历 */
            void inOrderTraversal(BTNode<eleType,Key>* node=nullptr);
            /* 层序遍历 */
            void levelOrderTraversal();
    };

    template<class eleType,class Key>
    BTNode<eleType,Key>::BTNode(BTNode<eleType,Key>* parent)
        : m_Parent(parent)
    {
        /* 默认关键字数量为 0，子节点全部设为 nullptr */
        m_SumOfKey=0;
        for(int i=0;i<=M;i++) m_Children[i]=nullptr;
    }

    template<class eleType,class Key>
    int BTNode<eleType,Key>::searchIndex(Key key)
    {
        /* 因为下标 0 弃用，从 1 开始检索，当 i 未超出关键字数量且小于 key 的值时，i++ */
        int i=1;
        while(i<m_SumOfKey&&key>m_Keys[i]) i++;
        return i;
    }

    template<class eleType,class Key>
    void BTNode<eleType,Key>::insertData(int index,Key key,eleType data)
    {
        /* 往 index 下标插入 key、value，将 index 后的数据往后挪一位 */
        int endPos=m_SumOfKey+1;
        for(int i=0;i<endPos-index;i++)
        {
            m_Keys[endPos-i]=m_Keys[endPos-i-1];
            m_Data[endPos-i]=m_Data[endPos-i-1];
        }
        m_Keys[index]=key;
        m_Data[index]=data;
        m_SumOfKey++;
    }

    template<class eleType,class Key>
    void BTNode<eleType,Key>::insertBTNode(int index,BTNode<eleType,Key>* node)
    {
        int endPos=m_SumOfKey;
        for(int i=0;i<endPos-index;i++) m_Children[endPos-i]=m_Children[endPos-i-1];
        m_Children[index]=node;
        if(node!=nullptr)
            node->m_Parent=this;
    }

    template<class eleType,class Key>
    eleType BTNode<eleType,Key>::deleteData(int index)
    {
        int endPos=m_SumOfKey;
        eleType data=m_Data[index];
        for(int i=index;i<endPos;i++)
        {
            m_Keys[i]=m_Keys[i+1];
            m_Data[i]=m_Data[i+1];
        }
        // m_Keys[endPos]=0;
        // m_Data[endPos]=nullptr;
        m_SumOfKey--;
        return data;
    }

    template<class eleType,class Key>
    BTNode<eleType,Key>* BTNode<eleType,Key>::deleteBTNode(int index)
    {
        int endPos=m_SumOfKey;
        BTNode<eleType,Key>* child=m_Children[index];
        if(child!=nullptr)              child->m_Parent=nullptr;
        for(int i=index;i<endPos;i++)   m_Children[index]=m_Children[index+1];
        m_Children[endPos]=nullptr;
        return child;
    }

    template<class eleType,class Key>
    BTNode<eleType,Key>* BTree<eleType,Key>::searchBTNode(Key key)
    {
        int i=1;
        BTNode<eleType,Key>* currNode=m_Root;
        while(currNode)
        {
            /* i 下标位置的关键字大于等于 key
                当 key 大于 i 位置关键字时当往右子节点继续查找
                当 key 等于 i 位置关键字时退出循环，表明查找成功
                当 key 小于 i 位置关键字时当往左子节点继续查找
            */
            i=currNode->searchIndex(key);
            //i range is [1,m_SumOfKey]
            if(key>currNode->m_Keys[i])         currNode=currNode->m_Children[i];   /* right */
            else if(key==currNode->m_Keys[i])   break;                              /* find it */
            else if(key<currNode->m_Keys[i])    currNode=currNode->m_Children[i-1]; /* left */
        }
        return currNode;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::splitBTNode(BTNode<eleType,Key>* node)
    {
        Key key;
        eleType data;
        BTNode<eleType,Key>* parent=node->m_Parent;
        BTNode<eleType,Key>* rightChild=nullptr;
        //right child
        rightChild=new BTNode<eleType,Key>;
        rightChild->insertBTNode(0,node->m_Children[MID_KEY]);
        node->m_Children[MID_KEY]=nullptr;
        for(int i=1;i<=node->m_SumOfKey-MID_KEY;i++)
        {
            key=node->m_Keys[MID_KEY+i];
            data=node->m_Data[MID_KEY+i];
            // node->m_Keys[MID_KEY+i]=0;
            // node->data[MID_KEY+i]=nullptr;
            rightChild->insertData(i,key,data);
            rightChild->insertBTNode(i,node->m_Children[MID_KEY+i]);
            node->m_Children[MID_KEY+i]=nullptr;
        }
        key=node->m_Keys[MID_KEY];
        data=node->m_Data[MID_KEY];
        if(parent==nullptr){
            BTNode<eleType,Key>* leftChild=nullptr;
            //left child
            leftChild=new BTNode<eleType,Key>;
            leftChild->insertBTNode(0,node->m_Children[0]);
            node->m_Children[0]=nullptr;
            for(int i=1;i<MID_KEY;i++)
            {
                key=node->m_Keys[i];
                data=node->m_Data[i];
                // node->m_Keys[i]=0;
                // node->data[i]=nullptr;
                leftChild->insertData(i,key,data);
                leftChild->insertBTNode(i,node->m_Children[i]);
                node->m_Children[i]=nullptr;
            }
            key=node->m_Keys[MID_KEY];
            data=node->m_Data[MID_KEY];
            // node->m_Keys[MID_KEY]=0;
            // node->data[MID_KEY]=nullptr;
            node->m_SumOfKey=0;
            node->insertBTNode(0,leftChild);
            node->insertData(1,key,data);
            node->insertBTNode(1,rightChild);
        }
        else
        {
            int index=1;
            index=parent->searchIndex(key);
            node->m_SumOfKey=MID_KEY-1;
            // node->m_Keys[MID_KEY]=0;
            // node->data[MID_KEY]=nullptr;
            if(key>parent->m_Keys[index])
                index++;
            parent->insertData(index,key,data);
            // leftChild is node;
            parent->insertBTNode(index,rightChild);
            if(parent->m_SumOfKey>MAX_KEY)
                splitBTNode(parent);
        }
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::moveLeft(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* leftChild,int dataPos)
    {
        BTNode<eleType,Key>* rightChild=parent->m_Children[index];
        if(!(parent&&rightChild))
            return;
        if(leftChild!=nullptr)
        {
            //left child move to left
            for(int i=dataPos;i<leftChild->m_SumOfKey;i++)
            {
                leftChild->m_Keys[i]=leftChild->m_Keys[i+1];
                leftChild->m_Data[i]=leftChild->m_Data[i+1];
            }
            if(dataPos>leftChild->m_SumOfKey)
            {
                leftChild->m_SumOfKey++;
            }
            leftChild->m_Keys[leftChild->m_SumOfKey]=parent->m_Keys[index];
            leftChild->m_Data[leftChild->m_SumOfKey]=parent->m_Data[index];
        }
        leftChild->insertBTNode(leftChild->m_SumOfKey,rightChild->deleteBTNode(0));
        //parent move to left
        parent->m_Keys[index]=rightChild->m_Keys[1];
        parent->m_Data[index]=rightChild->m_Data[1];
        //right child move to left
        for(int i=1;i<rightChild->m_SumOfKey;i++)
        {
            rightChild->m_Keys[i]=rightChild->m_Keys[i+1];
            rightChild->m_Data[i]=rightChild->m_Data[i+1];
        }
        // rightChild->m_Keys[rightChild->m_SumOfKey]=0;
        // rightChild->data[rightChild->m_SumOfKey]=nullptr;
        rightChild->m_SumOfKey--;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::moveRight(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* rightChild,int dataPos){
        BTNode<eleType,Key>* leftChild=parent->m_Children[index-1];
        if(!(parent&&leftChild))
            return;
        if(rightChild!=nullptr){
            //right child move to left
            if(dataPos>rightChild->m_SumOfKey)
            {
                rightChild->m_SumOfKey++;
                dataPos=rightChild->m_SumOfKey;
            }
            for(int i=dataPos;i>1;i--)
            {
                rightChild->m_Keys[i]=rightChild->m_Keys[i-1];
                rightChild->m_Data[i]=rightChild->m_Data[i-1];
            }
            rightChild->m_Keys[1]=parent->m_Keys[index];
            rightChild->m_Data[1]=parent->m_Data[index];
        }
        rightChild->insertBTNode(0,leftChild->deleteBTNode(leftChild->m_SumOfKey));
        //parent move to left
        parent->m_Keys[index]=leftChild->m_Keys[leftChild->m_SumOfKey];
        parent->m_Data[index]=leftChild->m_Data[leftChild->m_SumOfKey];
        //left child move to left
        // leftChild->m_Keys[leftChild->m_SumOfKey]=0;
        // leftChild->data[leftChild->m_SumOfKey]=nullptr;
        leftChild->m_SumOfKey--;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::combineBTNode(BTNode<eleType,Key>* parent,int index)
    {
        if(!parent||index<1)
            return;
        BTNode<eleType,Key>* leftChild=parent->m_Children[index-1];
        BTNode<eleType,Key>* rightChild=parent->m_Children[index];
        if(!(leftChild&&rightChild))
            return;
        Key key;//=0;
        eleType data;
        if(leftChild->m_SumOfKey<MIN_KEY)
        {
            //parent key move to left node
            leftChild->insertData(leftChild->m_SumOfKey+1,parent->m_Keys[index],parent->m_Data[index]);
            //right node's child move to left node
            leftChild->insertBTNode(leftChild->m_SumOfKey,rightChild->m_Children[0]);
            //right children move to left node
            for(int i=1;i<=rightChild->m_SumOfKey;i++)
            {
                key=rightChild->m_Keys[i];
                data=rightChild->m_Data[i];
                leftChild->insertData(leftChild->m_SumOfKey+1,key,data);
                leftChild->insertBTNode(leftChild->m_SumOfKey,rightChild->m_Children[i]);
            }
            free(parent->deleteBTNode(index));
        }
        else if(rightChild->m_SumOfKey<MIN_KEY)
        {
            //parent key move to right node
            rightChild->insertData(1,parent->m_Keys[index],parent->m_Data[index]);
            rightChild->insertBTNode(0,leftChild->m_Children[0]);
            for(int i=1;i<=leftChild->m_SumOfKey;i++)
            {
                key=leftChild->m_Keys[i];
                data=leftChild->m_Data[i];
                rightChild->insertData(1,key,data);
                rightChild->insertBTNode(i,leftChild->m_Children[i]);
            }
            free(parent->deleteBTNode(index-1));
        }
        if(parent->m_Parent==nullptr)
        {
            parent->deleteData(index);
            if(parent->m_SumOfKey==0)
            {
                BTNode<eleType,Key>* node=parent->m_Children[0];
                //copy leftChild to parent
                parent->m_SumOfKey=node->m_SumOfKey;
                parent->m_Children[0]=node->m_Children[0];
                if(node->m_Children[0]!=nullptr)
                    node->m_Children[0]->m_Parent=parent;
                for(int i=1;i<=parent->m_SumOfKey;i++)
                {
                    parent->m_Keys[i]=node->m_Keys[i];
                    parent->m_Data[i]=node->m_Data[i];
                    parent->m_Children[i]=node->m_Children[i];
                    if(node->m_Children[i]!=nullptr)
                        node->m_Children[i]->m_Parent=parent;
                }
                free(node);
            }
        }
        else
        {
            //update node
            BTNode<eleType,Key>* node=parent;
            parent=node->m_Parent;
            int j=parent->searchIndex(node->m_Keys[index]);
            if(node->m_Keys[index]<parent->m_Keys[j])
                j--;
            node->deleteData(index);
            if(node->m_SumOfKey<MIN_KEY)
            {
                balanceBTNode(parent,j);
            }
        }
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::balanceBTNode(BTNode<eleType,Key>* parent,int index)
    {
        if(parent==nullptr)
            return;
        //BTNode* parent=node->m_Parent;
        BTNode<eleType,Key>* node=parent->m_Children[index];
        //move to left
        if(index+1<=parent->m_SumOfKey&&parent->m_Children[index+1]->m_SumOfKey>MIN_KEY)
        {
            //right node is rich node
            moveLeft(parent,index+1,node,node->m_SumOfKey+1);
        }
        //move to right
        else if(index-1>=0&&parent->m_Children[index-1]->m_SumOfKey>MIN_KEY)
        {
            //left node is rich node
            moveRight(parent,index,node,node->m_SumOfKey+1);
        }
        //right and left are not rich node
        else
        {
            if(index-1>=0)
            {
                //node is rightChild
            }
            else if(index+1<=parent->m_SumOfKey)
            {
                //node is leftChild
                index++;
            }
            combineBTNode(parent,index);
        }
    }

    template<class eleType,class Key>
    BTree<eleType,Key>::~BTree()
    {
        linkQueue<BTNode<eleType,Key>*> queue;
        BTNode<eleType,Key>* currNode=nullptr;
        queue.enqueue(m_Root);
        int i=1;
        while(!queue.empty())
        {
            currNode=queue.front();
            queue.dequeue();
            if(currNode->m_Children[0]!=nullptr)
            {
                queue.enqueue(currNode->m_Children[0]);
                while(i<=currNode->m_SumOfKey)
                {
                    if(currNode->m_Children[i]!=nullptr)
                        queue.enqueue(currNode->m_Children[i]);
                    i++;
                }
            }
            delete currNode;
            i=1;
        }
    }
    template<class eleType,class Key>
    eleType BTree<eleType,Key>::search(Key key)
    {
        int i=1;
        BTNode<eleType,Key>* node=searchBTNode(key);
        eleType data;
        if(node!=nullptr)
        {
            i=node->searchIndex(key);
            data=node->data[i];
        }
        return data;
    }

    template<class eleType,class Key>
    bool BTree<eleType,Key>::insert(Key key,eleType data)
    {
        int i=1;
        BTNode<eleType,Key>* preNode=nullptr;
        BTNode<eleType,Key>* currNode=m_Root;
        while(currNode){
            i=currNode->searchIndex(key);
            if(key>currNode->m_Keys[i])
            {
                preNode=currNode;
                currNode=currNode->m_Children[i];
            }
            else if(key==currNode->m_Keys[i])
            {
                return false;
            }
            else if(key<currNode->m_Keys[i])
            {
                preNode=currNode;
                currNode=currNode->m_Children[i-1];
            }
        }
        if(currNode==nullptr)
            currNode=preNode;
        i=currNode->searchIndex(key);
        if(i==currNode->m_SumOfKey&&key>currNode->m_Keys[i])
            i++;
        currNode->insertData(i,key,data);
        if(currNode->m_SumOfKey>MAX_KEY)
        {
            splitBTNode(currNode);
        }
        return true;
    }

    template<class eleType,class Key>
    bool BTree<eleType,Key>::erase(Key key)
    {
        if(m_Root==nullptr)
            throw std::out_of_range("earse() error,btree is empty!");
        //need to alter
        int i=1;
        BTNode<eleType,Key>* parent=nullptr;
        BTNode<eleType,Key>* currNode=m_Root;
        //eleType data;
        currNode=searchBTNode(key);
        if(currNode==nullptr)
        {
            std::cout<<"Can't find the data by the key!\n";
            return false;
        }
        i=currNode->searchIndex(key);
        //save data
        //data=currNode->data[i];
        //this node is leaf node
        if(currNode->m_Children[0]==nullptr)
        {
            //key greater than min
            if(currNode->m_SumOfKey>MIN_KEY)
            {
                currNode->deleteData(i);
            //key equal to min
            }
            else
            {
                parent=currNode->m_Parent;
                //leaf node is m_Root
                if(parent==nullptr)
                {
                    currNode->deleteData(1);
                    return true;
                }
                //normal node
                int j=parent->searchIndex(currNode->m_Keys[i]);
                if(currNode->m_Keys[i]<parent->m_Keys[j])
                    j--;
                currNode->deleteData(i);
                balanceBTNode(parent,j);
            }
        }
        else
        {
            //get precursor key-data
            BTNode<eleType,Key>* target=currNode->m_Children[i-1];
            parent=target->m_Parent;
            int j=parent->searchIndex(target->m_Keys[target->m_SumOfKey]);
            if(target->m_Keys[target->m_SumOfKey]<parent->m_Keys[j])
                j--;
            while(target->m_Children[target->m_SumOfKey]!=nullptr)
                target=target->m_Children[target->m_SumOfKey];
            currNode->m_Keys[i]=target->m_Keys[target->m_SumOfKey];
            currNode->m_Data[i]=target->m_Data[target->m_SumOfKey];
            target->deleteData(target->m_SumOfKey);
            if(target->m_SumOfKey<MIN_KEY)
            {
                balanceBTNode(target->m_Parent,j);
            }
        }
        return true;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::show()
    {
        linkQueue<BTNode<eleType,Key>*> queue;
        BTNode<eleType,Key>* currNode=nullptr;
        queue.enqueue(m_Root);
        int i=1;
        while(!queue.empty())
        {
            currNode=queue.front();
            queue.dequeue();
            if(currNode->m_Children[0]!=nullptr)
            {
                queue.enqueue(currNode->m_Children[0]);
            }
            while(i<=currNode->m_SumOfKey)
            {
                std::cout<<currNode->m_Keys[i];
                if(i!=currNode->m_SumOfKey)
                    std::cout<<",";
                else
                    std::cout<<" ";
                if(currNode->m_Children[i]!=nullptr)
                    queue.enqueue(currNode->m_Children[i]);
                i++;
            }
            i=1;
        }
        std::cout<<"\n";
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::preOrderTraversal(BTNode<eleType,Key>* node)
    {
        if(!m_FuncOfTraversal)
            throw std::exception("not set function of traversal!");
        if(node==nullptr)
            node=m_Root;
        BTNode<eleType,Key>* currNode=node;
        for(int i=0;currNode&&i<=currNode->m_SumOfKey;i++)
        {
            if(i+1<=currNode->m_SumOfKey)
            {
                m_FuncOfTraversal(currNode->m_Data[i+1]);
                std::cout<<" ";
            }
            if(currNode->m_Children[i]!=nullptr)
                preOrderTraversal(currNode->m_Children[i]);
        }
        if(currNode&&currNode->m_Children==nullptr)
            std::cout<<"\n";
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::inOrderTraversal(BTNode<eleType,Key>* node)
    {
        if(!m_FuncOfTraversal)
            throw std::exception("not set function of traversal!");
        if(node==nullptr)
            node=m_Root;
        BTNode<eleType,Key>* currNode=node;
        for(int i=0;currNode&&i<=currNode->m_SumOfKey;i++)
        {
            if(currNode->m_Children[i]!=nullptr)
                inOrderTraversal(currNode->m_Children[i]);
            if(i+1<=currNode->m_SumOfKey)
            {
                m_FuncOfTraversal(currNode->m_Data[i+1]);
                std::cout<<" ";
            }
        }
        if(currNode&&currNode->m_Parent==nullptr)
            std::cout<<"\n";
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::levelOrderTraversal()
    {
        if(!m_FuncOfTraversal)
            throw std::exception("not set function of traversal!");
        linkQueue<BTNode<eleType,Key>*> queue;
        BTNode<eleType,Key>* currNode=nullptr;
        queue.enqueue(m_Root);
        int i=1;
        while(!queue.empty())
        {
            currNode=queue.front();
            queue.dequeue();
            if(currNode->m_Children[0]!=nullptr)
            {
                queue.enqueue(currNode->m_Children[0]);
            }
            while(i<=currNode->m_SumOfKey)
            {
                m_FuncOfTraversal(currNode->data[i]);
                printf(" ");
                if(currNode->m_Children[i]!=nullptr)
                    queue.enqueue(currNode->m_Children[i]);
                i++;
            }
            i=1;
        }
        std::cout<<"\n";
    }
};

#endif /* B_TREE_H */