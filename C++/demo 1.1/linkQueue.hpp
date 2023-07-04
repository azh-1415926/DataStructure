#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_
#include<iostream>
template<class Type>
class linkQueue {
    class node {
        public:
        Type data;
        node *next;
        node(Type _data,node *_next=nullptr):data(_data),next(_next){}
    };
    node* pHead;
    public:
    linkQueue();
    bool empty();
    Type& front();
    void enqueue(Type const& data);
    void dequeue();
    ~linkQueue();
};
template<class Type>
linkQueue<Type>::linkQueue(){
    pHead=new linkQueue<Type>::node(0);
}
template<class Type>
bool linkQueue<Type>::empty(){
    return pHead->next==nullptr;
}
template<class Type>
Type& linkQueue<Type>::front(){
    if(empty())
        throw std::out_of_range("front() error:queue is empty!");
    return pHead->next->data;
}
template<class Type>
void linkQueue<Type>::enqueue(Type const& data){
    linkQueue<Type>::node* pQueue=pHead;
    while(pQueue&&pQueue->next){
        pQueue=pQueue->next;
    }
    pQueue->next=new linkQueue<Type>::node(data);
}
template<class Type>
void linkQueue<Type>::dequeue(){
    if(empty())
        throw std::out_of_range("dequeue() error:queue is empty!");
    linkQueue<Type>::node* pQueue=pHead->next;
    pHead->next=pQueue->next;
    delete pQueue;
}
template<class Type>
linkQueue<Type>::~linkQueue(){
    linkQueue<Type>::node* pQueue=pHead;
    linkQueue<Type>::node* temp;
    while(pQueue){
        temp=pQueue;
        pQueue=pQueue->next;
        delete temp;
    }
}
#endif