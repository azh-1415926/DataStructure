#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <simpleDS/linkQueue.hpp>

namespace azh
{
    template<class Type>
    class binaryTree
    {
        private:
            struct Node
            {
                Type data;
                Node* left;
                Node* right;
                Node(Type data=0,Node* leftNode=nullptr,Node* rightNode=nullptr):data(data),left(leftNode),right(rightNode){};
            };
            Node* m_Root;
            linkQueue<Type> dataQueue;
            
        public:
            binaryTree();
            ~binaryTree();
            binaryTree(Type* pArray,int size);
            bool preOrderCreate(Node* node=nullptr);
            bool inOrderTraversal(Node* node=nullptr) const;
            void breOrderTraversal(Node* node=nullptr) const;
    };

    template<class Type>
    binaryTree<Type>::binaryTree()
    {
        m_Root=new Node;
    }

    template<class Type>
    binaryTree<Type>::binaryTree(Type* pArray,int size)
    {
        m_Root=new Node;
        Node* pNode=m_Root;
        for(int i=0;i<size;++i)
            dataQueue.enqueue(pArray[i]);
        preOrderCreate(pNode);
    }

    template<class Type>
    binaryTree<Type>::~binaryTree()
    {
        linkQueue<Node*> queue;
        queue.enqueue(m_Root);
        Node* pNode=m_Root;
        while(queue.empty())
        {
            pNode=queue.front();
            queue.dequeue();
            if(pNode->left)
                queue.enqueue(pNode->left);
            if(pNode->right)
                queue.enqueue(pNode->right);
            delete pNode;
        }
    }

    template<class Type>
    bool binaryTree<Type>::preOrderCreate(Node *node)
    {
        if(dataQueue.empty())
            return false;
        Type e=dataQueue.front();
        dataQueue.dequeue();
        node->data=e;
        node->left=new Node;
        node->right=new Node;
        preOrderCreate(node->left);
        preOrderCreate(node->right);
        return true;
    }

    template<class Type>
    bool binaryTree<Type>::inOrderTraversal(Node *node) const
    {
        if(node==NULL)
            node=m_Root;
        if(node){
            if(node->left)
                inOrderTraversal(node->left);
            std::cout<<node->data<<" ";
            if(node->right)
                inOrderTraversal(node->right);
        };
        return true;
    }

    template<class Type>
    void binaryTree<Type>::breOrderTraversal(Node* node) const
    {
        if(node==NULL)
            node=m_Root;
        linkQueue<Node*> queue;
        queue.enqueue(m_Root);
        while(!queue.empty())
        {
            node=queue.front();
            queue.dequeue();
            std::cout<<node->data<<" ";
            if(node->left)
                queue.enqueue(node->left);
            if(node->right)
                queue.enqueue(node->right);
        }
        std::cout<<std::endl;
    }
}

#endif