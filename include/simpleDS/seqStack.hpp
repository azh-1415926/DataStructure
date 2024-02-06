#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_

#include<iostream>

template<class Type,int size=10>
class seqStack
{
    Type *m_Stack;
    int m_top;
    int m_capacity;
    public:
    seqStack();
    seqStack(const seqStack<Type,size>& stack);
    ~seqStack();
    inline bool empty() const { return m_top==m_capacity; }
    inline bool full() const { return m_top==0; }
    inline Type top() const
    {
        if(empty())
            throw std::out_of_range("top() error:stack is empty!");
        return m_Stack[m_top];
    }
    void push(Type const& data);
    void pop();
};

template<class Type,int size>
seqStack<Type,size>::seqStack()
{
    this->m_capacity=size;
    this->m_top=size;
    m_Stack=new Type[this->m_capacity];
}

template<class Type,int size>
seqStack<Type,size>::seqStack(const seqStack<Type,size>& stack)
    : m_top(stack.m_top)
    , m_capacity(size)
{
    m_Stack=new Type[m_capacity];
    for(int i=0;i<m_capacity;i++)
        m_Stack[i]=stack.m_Stack[i];
}

template<class Type,int size>
seqStack<Type,size>::~seqStack()
{
    delete[] m_Stack;
}

template<class Type,int size>
void seqStack<Type,size>::push(Type const& data)
{
    if(full())
        throw std::out_of_range("push() error:stack is full!");
    m_Stack[--m_top]=data;
}

template<class Type,int size>
void seqStack<Type,size>::pop()
{
    if(empty())
        throw std::out_of_range("pop() error:stack is empty!");
    ++m_top;
}

#endif