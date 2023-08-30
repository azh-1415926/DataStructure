#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_

#include<iostream>

const int QUEUE_PUSH=0;
const int QUEUE_POP=1;

template<class Type,int size=10>
class seqQueue
{
private:
    Type* m_Queue;
    int m_Head;
    int m_Tail;
    int m_Capacity;
    int m_Flag;
public:
    seqQueue();
    seqQueue(const seqQueue<Type,size>& queue);
    ~seqQueue();
    inline bool empty() const { return (m_Head==m_Tail)&&(m_Flag==QUEUE_POP); }
    inline bool full() const { return (m_Tail==m_Head)&&(m_Flag==QUEUE_PUSH); }
    inline Type front() const
    {
        if(empty())
            throw std::out_of_range("front() error:queue is empty!");
        return m_Queue[m_Head];
    }
    void enqueue(const Type& data);
    void dequeue();
};

template<class Type,int size>
seqQueue<Type,size>::seqQueue()
    :m_Capacity(size)
{
    m_Queue=new Type[m_Capacity];
    for(int i=0;i<m_Capacity;i++)
        m_Queue[i]=0;
    m_Head=m_Tail=0;
    m_Flag=QUEUE_POP;
}

template<class Type,int size>
seqQueue<Type,size>::seqQueue(const seqQueue<Type,size>& queue)
    : m_Head(queue.m_Head), m_Tail(queue.m_Tail)
    , m_Capacity(size), m_Flag(queue.m_Flag)
{
    m_Queue=new Type[m_Capacity];
    for(int i=0;i<m_Capacity;i++)
        m_Queue[i]=queue.m_Queue[i];
}

template<class Type,int size>
seqQueue<Type,size>::~seqQueue(){
    delete[] m_Queue;
}

template<class Type,int size>
void seqQueue<Type,size>::enqueue(const Type& data){
    if(full())
        throw std::out_of_range("enqueue() error:queue is full!");
    m_Queue[m_Tail]=data;
    m_Tail=(m_Tail+1)%m_Capacity;
    m_Flag=QUEUE_PUSH;
}

template<class Type,int size>
void seqQueue<Type,size>::dequeue(){
    if(empty())
        throw std::out_of_range("dequeue() error:queue is empty!");
    m_Head=(m_Head+1)%m_Capacity;
    m_Flag=QUEUE_POP;
}

#endif