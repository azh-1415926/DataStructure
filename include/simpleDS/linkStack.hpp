#ifndef _LINK_STACK_H_
#define _LINK_STACK_H_

#include <iostream>

template<class Type>
class linkStack
{
private:
    struct Node
    {   
        Type data;
        Node* next;
        Node(Type _data,Node* _next=nullptr):data(_data),next(_next){};
    };
    Node* m_Stack;
public:
    linkStack();
    ~linkStack();
    inline bool empty() const { return m_Stack->next==NULL; };
    inline Type top() const 
    {
        if(empty())
            throw std::out_of_range("top() error,stack is empty!");
        return m_Stack->data;
    }
    void push(const Type&  data);
    void pop();
};

template<class Type>
linkStack<Type>::linkStack()
{
    m_Stack=new linkStack<Type>::Node(0);
    m_Stack->next=nullptr;
}

template<class Type>
linkStack<Type>::~linkStack(){
    linkStack<Type>::Node* temp=m_Stack;
    while(m_Stack->next){
        m_Stack=m_Stack->next;
        delete temp;
    }
}

template<class Type>
void linkStack<Type>::push(Type const& data)
{
    linkStack<Type>::Node* temp=m_Stack;
    m_Stack=new linkStack<Type>::Node(data,temp);
}

template<class Type>
void linkStack<Type>::pop()
{
    if(empty())
        throw std::out_of_range("pop() error,stack is empty!");
    linkStack<Type>::Node* temp=m_Stack;
    m_Stack=m_Stack->next;
    delete temp;
}

#endif