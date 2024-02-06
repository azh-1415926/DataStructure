#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_

#include<iostream>

namespace azh
{
    template<class T,int size=10>
    class seqStack
    {
        T *m_Stack;
        int m_top;
        int m_capacity;
        public:
        seqStack();
        seqStack(const seqStack<T,size>& stack);
        ~seqStack();
        inline bool empty() const { return m_top==m_capacity; }
        inline bool full() const { return m_top==0; }
        inline T top() const
        {
            if(empty())
                throw std::out_of_range("top() error:stack is empty!");
            return m_Stack[m_top];
        }
        void push(T const& data);
        void pop();
    };

    template<class T,int size>
    seqStack<T,size>::seqStack()
    {
        this->m_capacity=size;
        this->m_top=size;
        m_Stack=new T[this->m_capacity];
    }

    template<class T,int size>
    seqStack<T,size>::seqStack(const seqStack<T,size>& stack)
        : m_top(stack.m_top)
        , m_capacity(size)
    {
        m_Stack=new T[m_capacity];
        for(int i=0;i<m_capacity;i++)
            m_Stack[i]=stack.m_Stack[i];
    }

    template<class T,int size>
    seqStack<T,size>::~seqStack()
    {
        delete[] m_Stack;
    }

    template<class T,int size>
    void seqStack<T,size>::push(T const& data)
    {
        if(full())
            throw std::out_of_range("push() error:stack is full!");
        m_Stack[--m_top]=data;
    }

    template<class T,int size>
    void seqStack<T,size>::pop()
    {
        if(empty())
            throw std::out_of_range("pop() error:stack is empty!");
        ++m_top;
    }
};

#endif