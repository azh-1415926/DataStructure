#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

#include<iostream>

template<class Type>
class linkQueue
{
private:
    struct Node
    {
        public:
        Type data;
        Node *next;
        Node(Type _data,Node *_next=nullptr):data(_data),next(_next){}
    };
    Node* m_Head;
public:
    linkQueue();
    ~linkQueue();
    bool empty() const { return m_Head->next==nullptr; }
    inline Type front() const
    {
        if(empty())
            throw std::out_of_range("front() error:queue is empty!");
        return m_Head->next->data;
    };
    void enqueue(const Type& data);
    void dequeue();
};

template<class Type>
linkQueue<Type>::linkQueue()
{
    m_Head=new linkQueue<Type>::Node(0);
}

template<class Type>
linkQueue<Type>::~linkQueue()
{
    linkQueue<Type>::Node* pNode=m_Head;
    linkQueue<Type>::Node* temp;
    while(pNode)
    {
        temp=pNode;
        pNode=pNode->next;
        delete temp;
    }
}

template<class Type>
void linkQueue<Type>::enqueue(const Type& data)
{
    linkQueue<Type>::Node* pNode=m_Head;
    while(pNode&&pNode->next)
        pNode=pNode->next;
    pNode->next=new linkQueue<Type>::Node(data);
}

template<class Type>
void linkQueue<Type>::dequeue()
{
    if(empty())
        throw std::out_of_range("dequeue() error:queue is empty!");
    linkQueue<Type>::Node* pNode=m_Head->next;
    m_Head->next=pNode->next;
    delete pNode;
}

#endif