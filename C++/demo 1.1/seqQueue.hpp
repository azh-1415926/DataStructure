#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_
#include<iostream>
const int QUEUE_PUSH=0;
const int QUEUE_POP=1;
template<class Type,int size=10>
class seqQueue {
    Type* pQueue;
    int head;
    int tail;
    int capacity;
    int flag;
    public:
        seqQueue();
        seqQueue(seqQueue<Type,size> const& queue);
        bool empty();
        bool full();
        Type& front();
        void enqueue(Type const& data);
        void dequeue();
        ~seqQueue();
};
template<class Type,int size>
seqQueue<Type,size>::seqQueue()
    :capacity(size)
{
    pQueue=new Type[capacity];
    for(int i=0;i<capacity;i++)
        pQueue[i]=0;
    head=tail=0;
    flag=QUEUE_POP;
}
template<class Type,int size>
seqQueue<Type,size>::seqQueue(seqQueue<Type,size> const& queue)
    :head(queue.head)
    ,tail(queue.tail)
    ,capacity(size)
    ,flag(queue.flag)
{
    pQueue=new Type[capacity];
    for(int i=0;i<capacity;i++)
        pQueue[i]=queue.pQueue[i];
}
template<class Type,int size>
bool seqQueue<Type,size>::empty(){
    return (head==tail)&&(flag==QUEUE_POP);
}
template<class Type,int size>
bool seqQueue<Type,size>::full(){
    return (tail==head)&&(flag==QUEUE_PUSH);
}
template<class Type,int size>
Type& seqQueue<Type,size>::front(){
    return pQueue[head];
}
template<class Type,int size>
void seqQueue<Type,size>::enqueue(Type const& data){
    if(full())
        return;
    pQueue[tail]=data;
    tail=(tail+1)%capacity;
    flag=QUEUE_PUSH;
}
template<class Type,int size>
void seqQueue<Type,size>::dequeue(){
    if(empty())
        return;
    head=(head+1)%capacity;
    flag=QUEUE_POP;
}
template<class Type,int size>
seqQueue<Type,size>::~seqQueue(){
    delete[] pQueue;
}
#endif