#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

#include<iostream>

template<class T>
class linkQueue
{
private:
    struct Node
    {
        public:
        T data;
        Node *next;
        Node(T _data,Node *_next=nullptr):data(_data),next(_next){}
    };
    Node* m_Head;
public:
    linkQueue();
    ~linkQueue();
    bool empty() const { return m_Head->next==nullptr; }
    inline T front() const
    {
        if(empty())
            throw std::out_of_range("front() error:queue is empty!");
        return m_Head->next->data;
    };
    void enqueue(const T& data);
    void dequeue();
};

template<class T>
linkQueue<T>::linkQueue()
{
    m_Head=new linkQueue<T>::Node(0);
}

template<class T>
linkQueue<T>::~linkQueue()
{
    linkQueue<T>::Node* pNode=m_Head;
    linkQueue<T>::Node* temp;
    while(pNode)
    {
        temp=pNode;
        pNode=pNode->next;
        delete temp;
    }
}

template<class T>
void linkQueue<T>::enqueue(const T& data)
{
    linkQueue<T>::Node* pNode=m_Head;
    while(pNode&&pNode->next)
        pNode=pNode->next;
    pNode->next=new linkQueue<T>::Node(data);
}

template<class T>
void linkQueue<T>::dequeue()
{
    if(empty())
        throw std::out_of_range("dequeue() error:queue is empty!");
    linkQueue<T>::Node* pNode=m_Head->next;
    m_Head->next=pNode->next;
    delete pNode;
}

#endif