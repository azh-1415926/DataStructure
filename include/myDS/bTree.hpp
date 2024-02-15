#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <functional>
#include <simpleDS/linkQueue.hpp>

namespace azh
{
    const int M=3;
    const int MAX_KEY=(M-1);
    const int MIN_KEY=((M-1)/2);
    const int MID_KEY=((M+1)/2);

    template<class eleType,class Key>
    class BTree;

    template<class eleType,class Key=int>
    class BTNode
    {
        friend class BTree<eleType,Key>;
        private:
            int keynum;
            Key keys[M+1];
            eleType data[M+1];
            BTNode<eleType,Key>* parent;
            BTNode<eleType,Key>* child[M+1];
            BTNode(BTNode<eleType,Key>* parent=nullptr);
            ~BTNode() {  }
            int searchIndex(Key key);
            void insertValue(int index,Key key,eleType value);
            void insertBTNode(int index,BTNode<eleType,Key>* node);
            eleType deleteValue(int index);
            BTNode<eleType,Key>* deleteBTNode(int index);
    };
    
    template<class eleType,class Key=int>
    class BTree
    {
        private:
            std::function<void(eleType)> m_FuncOfTraversal;
            BTNode<eleType,Key>* root;

            BTNode<eleType,Key>* searchBTNode(Key key);
            static void splitBTNode(BTNode<eleType,Key>* node);
            static void moveLeft(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* leftChild,int dataPos);
            static void moveRight(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* rightChild,int dataPos);
            static void combineBTNode(BTNode<eleType,Key>* parent,int index);
            static void balanceBTNode(BTNode<eleType,Key>* parent,int index);

        public:
            BTree();
            ~BTree();

            inline void setTraversalFunction(const std::function<void(eleType)>& func) { m_FuncOfTraversal=func; }

            eleType search(Key key);
            bool insert(Key key,eleType value);
            bool erase(Key key);
            void show();
            void preOrderTraversal(BTNode<eleType,Key>* node=nullptr);
            void inOrderTraversal(BTNode<eleType,Key>* node=nullptr);
            void levelOrderTraversal();
    };

    template<class eleType,class Key>
    BTNode<eleType,Key>::BTNode(BTNode<eleType,Key>* parent)
        : parent(parent)
    {
        this->keynum=0;
        for(int i=0;i<=M;i++){
            this->keys[i]=0;
            this->data[i]=0;
            this->child[i]=nullptr;
        }
    }

    template<class eleType,class Key>
    int BTNode<eleType,Key>::searchIndex(Key key)
    {
        int i=1;
        while(i<this->keynum&&key>this->keys[i])
            i++;
        return i;
    }

    template<class eleType,class Key>
    void BTNode<eleType,Key>::insertValue(int index,Key key,eleType value)
    {
        int endPos=this->keynum+1;
        for(int i=0;i<endPos-index;i++)
        {
            this->keys[endPos-i]=this->keys[endPos-i-1];
            this->data[endPos-i]=this->data[endPos-i-1];
        }
        this->keys[index]=key;
        this->data[index]=value;
        this->keynum++;
    }

    template<class eleType,class Key>
    void BTNode<eleType,Key>::insertBTNode(int index,BTNode<eleType,Key>* node)
    {
        int endPos=this->keynum;
        for(int i=0;i<endPos-index;i++)
            this->child[endPos-i]=this->child[endPos-i-1];
        this->child[index]=node;
        if(node!=NULL)
            node->parent=this;
    }

    template<class eleType,class Key>
    eleType BTNode<eleType,Key>::deleteValue(int index)
    {
        int endPos=this->keynum;
        eleType data=this->data[index];
        for(int i=index;i<endPos;i++){
            this->keys[i]=this->keys[i+1];
            this->data[i]=this->data[i+1];
        }
        this->keys[endPos]=0;
        //this->data[endPos]=NULL;
        this->keynum--;
        return data;
    }

    template<class eleType,class Key>
    BTNode<eleType,Key>* BTNode<eleType,Key>::deleteBTNode(int index)
    {
        int endPos=this->keynum;
        BTNode<eleType,Key>* child=this->child[index];
        if(child!=NULL)
            child->parent=NULL;
        for(int i=index;i<endPos;i++)
            this->child[index]=this->child[index+1];
        this->child[endPos]=NULL;
        return child;
    }

    template<class eleType,class Key>
    BTNode<eleType,Key>* BTree<eleType,Key>::searchBTNode(Key key)
    {
        int i=1;
        BTNode<eleType,Key>* currNode=root;
        while(currNode)
        {
            i=currNode->searchIndex(key);
            //i range is [1,keynum]
            if(key>currNode->keys[i])
            {
                //right
                currNode=currNode->child[i];
            }else if(key==currNode->keys[i])
            {
                //find it
                break;
            }else if(key<currNode->keys[i])
            {
                //key less than the first key
                currNode=currNode->child[i-1];
            }
        }
        return currNode;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::splitBTNode(BTNode<eleType,Key>* node)
    {
        Key key=0;
        eleType value;
        BTNode<eleType,Key>* parent=node->parent;
        BTNode<eleType,Key>* rightChild=NULL;
        //right child
        rightChild=new BTNode<eleType,Key>;
        rightChild->insertBTNode(0,node->child[MID_KEY]);
        node->child[MID_KEY]=NULL;
        for(int i=1;i<=node->keynum-MID_KEY;i++)
        {
            key=node->keys[MID_KEY+i];
            value=node->data[MID_KEY+i];
            node->keys[MID_KEY+i]=0;
            //node->data[MID_KEY+i]=NULL;
            rightChild->insertValue(i,key,value);
            rightChild->insertBTNode(i,node->child[MID_KEY+i]);
            node->child[MID_KEY+i]=NULL;
        }
        key=node->keys[MID_KEY];
        value=node->data[MID_KEY];
        if(parent==NULL){
            BTNode<eleType,Key>* leftChild=NULL;
            //left child
            leftChild=new BTNode<eleType,Key>;
            leftChild->insertBTNode(0,node->child[0]);
            node->child[0]=NULL;
            for(int i=1;i<MID_KEY;i++)
            {
                key=node->keys[i];
                value=node->data[i];
                node->keys[i]=0;
                //node->data[i]=NULL;
                leftChild->insertValue(i,key,value);
                leftChild->insertBTNode(i,node->child[i]);
                node->child[i]=NULL;
            }
            key=node->keys[MID_KEY];
            value=node->data[MID_KEY];
            node->keys[MID_KEY]=0;
            //node->data[MID_KEY]=NULL;
            node->keynum=0;
            node->insertBTNode(0,leftChild);
            node->insertValue(1,key,value);
            node->insertBTNode(1,rightChild);
        }
        else
        {
            int index=1;
            index=parent->searchIndex(key);
            node->keynum=MID_KEY-1;
            node->keys[MID_KEY]=0;
            //node->data[MID_KEY]=NULL;
            if(key>parent->keys[index])
                index++;
            parent->insertValue(index,key,value);
            //leftChild is node;
            parent->insertBTNode(index,rightChild);
            if(parent->keynum>MAX_KEY)
                splitBTNode(parent);
        }
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::moveLeft(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* leftChild,int dataPos)
    {
        BTNode<eleType,Key>* rightChild=parent->child[index];
        if(!(parent&&rightChild))
            return;
        if(leftChild!=NULL)
        {
            //left child move to left
            for(int i=dataPos;i<leftChild->keynum;i++)
            {
                leftChild->keys[i]=leftChild->keys[i+1];
                leftChild->data[i]=leftChild->data[i+1];
            }
            if(dataPos>leftChild->keynum)
            {
                leftChild->keynum++;
            }
            leftChild->keys[leftChild->keynum]=parent->keys[index];
            leftChild->data[leftChild->keynum]=parent->data[index];
        }
        leftChild->insertBTNode(leftChild->keynum,rightChild->deleteBTNode(0));
        //parent move to left
        parent->keys[index]=rightChild->keys[1];
        parent->data[index]=rightChild->data[1];
        //right child move to left
        for(int i=1;i<rightChild->keynum;i++)
        {
            rightChild->keys[i]=rightChild->keys[i+1];
            rightChild->data[i]=rightChild->data[i+1];
        }
        rightChild->keys[rightChild->keynum]=0;
        //rightChild->data[rightChild->keynum]=NULL;
        rightChild->keynum--;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::moveRight(BTNode<eleType,Key>* parent,int index,BTNode<eleType,Key>* rightChild,int dataPos){
        BTNode<eleType,Key>* leftChild=parent->child[index-1];
        if(!(parent&&leftChild))
            return;
        if(rightChild!=NULL){
            //right child move to left
            if(dataPos>rightChild->keynum)
            {
                rightChild->keynum++;
                dataPos=rightChild->keynum;
            }
            for(int i=dataPos;i>1;i--)
            {
                rightChild->keys[i]=rightChild->keys[i-1];
                rightChild->data[i]=rightChild->data[i-1];
            }
            rightChild->keys[1]=parent->keys[index];
            rightChild->data[1]=parent->data[index];
        }
        rightChild->insertBTNode(0,leftChild->deleteBTNode(leftChild->keynum));
        //parent move to left
        parent->keys[index]=leftChild->keys[leftChild->keynum];
        parent->data[index]=leftChild->data[leftChild->keynum];
        //left child move to left
        leftChild->keys[leftChild->keynum]=0;
        //leftChild->data[leftChild->keynum]=NULL;
        leftChild->keynum--;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::combineBTNode(BTNode<eleType,Key>* parent,int index)
    {
        if(!parent||index<1)
            return;
        BTNode<eleType,Key>* leftChild=parent->child[index-1];
        BTNode<eleType,Key>* rightChild=parent->child[index];
        if(!(leftChild&&rightChild))
            return;
        Key key=0;
        eleType value;
        if(leftChild->keynum<MIN_KEY)
        {
            //parent key move to left node
            leftChild->insertValue(leftChild->keynum+1,parent->keys[index],parent->data[index]);
            //right node's child move to left node
            leftChild->insertBTNode(leftChild->keynum,rightChild->child[0]);
            //right children move to left node
            for(int i=1;i<=rightChild->keynum;i++)
            {
                key=rightChild->keys[i];
                value=rightChild->data[i];
                leftChild->insertValue(leftChild->keynum+1,key,value);
                leftChild->insertBTNode(leftChild->keynum,rightChild->child[i]);
            }
            free(parent->deleteBTNode(index));
        }
        else if(rightChild->keynum<MIN_KEY)
        {
            //parent key move to right node
            rightChild->insertValue(1,parent->keys[index],parent->data[index]);
            rightChild->insertBTNode(0,leftChild->child[0]);
            for(int i=1;i<=leftChild->keynum;i++)
            {
                key=leftChild->keys[i];
                value=leftChild->data[i];
                rightChild->insertValue(1,key,value);
                rightChild->insertBTNode(i,leftChild->child[i]);
            }
            free(parent->deleteBTNode(index-1));
        }
        if(parent->parent==NULL)
        {
            parent->deleteValue(index);
            if(parent->keynum==0)
            {
                BTNode<eleType,Key>* node=parent->child[0];
                //copy leftChild to parent
                parent->keynum=node->keynum;
                parent->child[0]=node->child[0];
                if(node->child[0]!=NULL)
                    node->child[0]->parent=parent;
                for(int i=1;i<=parent->keynum;i++)
                {
                    parent->keys[i]=node->keys[i];
                    parent->data[i]=node->data[i];
                    parent->child[i]=node->child[i];
                    if(node->child[i]!=NULL)
                        node->child[i]->parent=parent;
                }
                free(node);
            }
        }
        else
        {
            //update node
            BTNode<eleType,Key>* node=parent;
            parent=node->parent;
            int j=parent->searchIndex(node->keys[index]);
            if(node->keys[index]<parent->keys[j])
                j--;
            node->deleteValue(index);
            if(node->keynum<MIN_KEY)
            {
                balanceBTNode(parent,j);
            }
        }
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::balanceBTNode(BTNode<eleType,Key>* parent,int index)
    {
        if(parent==NULL)
            return;
        //BTNode* parent=node->parent;
        BTNode<eleType,Key>* node=parent->child[index];
        //move to left
        if(index+1<=parent->keynum&&parent->child[index+1]->keynum>MIN_KEY)
        {
            //right node is rich node
            moveLeft(parent,index+1,node,node->keynum+1);
        }
        //move to right
        else if(index-1>=0&&parent->child[index-1]->keynum>MIN_KEY)
        {
            //left node is rich node
            moveRight(parent,index,node,node->keynum+1);
        }
        //right and left are not rich node
        else
        {
            if(index-1>=0)
            {
                //node is rightChild
            }
            else if(index+1<=parent->keynum)
            {
                //node is leftChild
                index++;
            }
            combineBTNode(parent,index);
        }
    }

    template<class eleType,class Key>
    BTree<eleType,Key>::BTree()
    {
        root=new BTNode<eleType,Key>;
    }

    template<class eleType,class Key>
    BTree<eleType,Key>::~BTree()
    {
        linkQueue<BTNode<eleType,Key>*> queue;
        BTNode<eleType,Key>* currNode=NULL;
        queue.enqueue(root);
        int i=1;
        while(!queue.empty())
        {
            currNode=queue.front();
            queue.dequeue();
            if(currNode->child[0]!=NULL)
            {
                queue.enqueue(currNode->child[0]);
                while(i<=currNode->keynum)
                {
                    if(currNode->child[i]!=NULL)
                        queue.enqueue(currNode->child[i]);
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
    bool BTree<eleType,Key>::insert(Key key,eleType value)
    {
        int i=1;
        BTNode<eleType,Key>* preNode=NULL;
        BTNode<eleType,Key>* currNode=root;
        while(currNode){
            i=currNode->searchIndex(key);
            if(key>currNode->keys[i])
            {
                preNode=currNode;
                currNode=currNode->child[i];
            }
            else if(key==currNode->keys[i])
            {
                return false;
            }
            else if(key<currNode->keys[i])
            {
                preNode=currNode;
                currNode=currNode->child[i-1];
            }
        }
        if(currNode==NULL)
            currNode=preNode;
        i=currNode->searchIndex(key);
        if(i==currNode->keynum&&key>currNode->keys[i])
            i++;
        currNode->insertValue(i,key,value);
        if(currNode->keynum>MAX_KEY)
        {
            splitBTNode(currNode);
        }
        return true;
    }

    template<class eleType,class Key>
    bool BTree<eleType,Key>::erase(Key key)
    {
        if(root==nullptr)
            throw std::out_of_range("earse() error,btree is empty!");
        //need to alter
        int i=1;
        BTNode<eleType,Key>* parent=NULL;
        BTNode<eleType,Key>* currNode=root;
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
        if(currNode->child[0]==NULL)
        {
            //key greater than min
            if(currNode->keynum>MIN_KEY)
            {
                currNode->deleteValue(i);
            //key equal to min
            }
            else
            {
                parent=currNode->parent;
                //leaf node is root
                if(parent==NULL)
                {
                    currNode->deleteValue(1);
                    return true;
                }
                //normal node
                int j=parent->searchIndex(currNode->keys[i]);
                if(currNode->keys[i]<parent->keys[j])
                    j--;
                currNode->deleteValue(i);
                balanceBTNode(parent,j);
            }
        }
        else
        {
            //get precursor key-value
            BTNode<eleType,Key>* target=currNode->child[i-1];
            parent=target->parent;
            int j=parent->searchIndex(target->keys[target->keynum]);
            if(target->keys[target->keynum]<parent->keys[j])
                j--;
            while(target->child[target->keynum]!=NULL)
                target=target->child[target->keynum];
            currNode->keys[i]=target->keys[target->keynum];
            currNode->data[i]=target->data[target->keynum];
            target->deleteValue(target->keynum);
            if(target->keynum<MIN_KEY)
            {
                balanceBTNode(target->parent,j);
            }
        }
        return true;
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::show()
    {
        linkQueue<BTNode<eleType,Key>*> queue;
        BTNode<eleType,Key>* currNode=NULL;
        queue.enqueue(root);
        int i=1;
        while(!queue.empty())
        {
            currNode=queue.front();
            queue.dequeue();
            if(currNode->child[0]!=NULL)
            {
                queue.enqueue(currNode->child[0]);
            }
            while(i<=currNode->keynum)
            {
                std::cout<<currNode->keys[i];
                if(i!=currNode->keynum)
                    std::cout<<",";
                else
                    std::cout<<" ";
                if(currNode->child[i]!=NULL)
                    queue.enqueue(currNode->child[i]);
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
            node=root;
        BTNode<eleType,Key>* currNode=node;
        for(int i=0;currNode&&i<=currNode->keynum;i++)
        {
            if(i+1<=currNode->keynum)
            {
                m_FuncOfTraversal(currNode->data[i+1]);
                std::cout<<" ";
            }
            if(currNode->child[i]!=NULL)
                preOrderTraversal(currNode->child[i]);
        }
        if(currNode&&currNode->parent==NULL)
            std::cout<<"\n";
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::inOrderTraversal(BTNode<eleType,Key>* node)
    {
        if(!m_FuncOfTraversal)
            throw std::exception("not set function of traversal!");
        if(node==nullptr)
            node=root;
        BTNode<eleType,Key>* currNode=node;
        for(int i=0;currNode&&i<=currNode->keynum;i++)
        {
            if(currNode->child[i]!=NULL)
                inOrderTraversal(currNode->child[i]);
            if(i+1<=currNode->keynum)
            {
                m_FuncOfTraversal(currNode->data[i+1]);
                std::cout<<" ";
            }
        }
        if(currNode&&currNode->parent==NULL)
            std::cout<<"\n";
    }

    template<class eleType,class Key>
    void BTree<eleType,Key>::levelOrderTraversal()
    {
        if(!m_FuncOfTraversal)
            throw std::exception("not set function of traversal!");
        linkQueue<BTNode<eleType,Key>*> queue;
        BTNode<eleType,Key>* currNode=NULL;
        queue.enqueue(root);
        int i=1;
        while(!queue.empty())
        {
            currNode=queue.front();
            queue.dequeue();
            if(currNode->child[0]!=NULL)
            {
                queue.enqueue(currNode->child[0]);
            }
            while(i<=currNode->keynum)
            {
                m_FuncOfTraversal(currNode->data[i]);
                printf(" ");
                if(currNode->child[i]!=NULL)
                    queue.enqueue(currNode->child[i]);
                i++;
            }
            i=1;
        }
        std::cout<<"\n";
    }
};

#endif /* B_TREE_H */