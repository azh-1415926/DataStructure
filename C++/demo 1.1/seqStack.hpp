#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_
#include<iostream>
template<class Type,int size=10>
class seqStack {
    Type *pStack;
    int m_top;
    int m_capacity;
    public:
    seqStack();
    seqStack(seqStack<Type,size> const& stack);
    ~seqStack();
    bool empty();
    bool full();
    Type& top();
    void push(Type const& data);
    void pop();
};
template<class Type,int size>
seqStack<Type,size>::seqStack(){
    this->m_capacity=size;
    this->m_top=size;
    pStack=new Type[this->m_capacity];
}
template<class Type,int size>
seqStack<Type,size>::seqStack(seqStack<Type,size> const& stack)
    :m_top(stack.m_top)
    ,m_capacity(size)
{
    pStack=new Type[m_capacity];
    for(int i=0;i<m_capacity;i++)
        pStack[i]=stack.pStack[i];
}
template<class Type,int size>
seqStack<Type,size>::~seqStack(){
    delete[] pStack;
}
template<class Type,int size>
bool seqStack<Type,size>::empty(){
    return m_top==m_capacity;
}
template<class Type,int size>
bool seqStack<Type,size>::full(){
    return m_top==0;
}
template<class Type,int size>
Type& seqStack<Type,size>::top(){
    if(empty())
        throw std::out_of_range("top() error:stack is empty!");
    return pStack[m_top];
}
template<class Type,int size>
void seqStack<Type,size>::push(Type const& data){
    if(full())
        throw std::out_of_range("push() error:stack is full!");
    pStack[--m_top]=data;
}
template<class Type,int size>
void seqStack<Type,size>::pop(){
    if(empty())
        throw std::out_of_range("pop() error:stack is empty!");
    ++m_top;
}
#endif