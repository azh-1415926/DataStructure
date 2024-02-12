#ifndef LINK_STACK_H
#define LINK_STACK_H

#include <iostream>

namespace azh
{
    template<class T>
    class linkStack
    {
        private:
            struct Node
            {   
                T data;
                Node* next;
                Node(T _data,Node* _next=nullptr):data(_data),next(_next){};
            };
            Node* m_Stack;
            
        public:
            linkStack();
            ~linkStack();
            inline bool empty() const { return m_Stack->next==NULL; };
            inline T top() const 
            {
                if(empty())
                    throw std::out_of_range("top() error,stack is empty!");
                return m_Stack->data;
            }
            void push(const T&  data);
            void pop();
    };

    template<class T>
    linkStack<T>::linkStack()
    {
        m_Stack=new linkStack<T>::Node(0);
        m_Stack->next=nullptr;
    }

    template<class T>
    linkStack<T>::~linkStack(){
        linkStack<T>::Node* temp=m_Stack;
        while(m_Stack->next){
            m_Stack=m_Stack->next;
            delete temp;
        }
    }

    template<class T>
    void linkStack<T>::push(T const& data)
    {
        linkStack<T>::Node* temp=m_Stack;
        m_Stack=new linkStack<T>::Node(data,temp);
    }

    template<class T>
    void linkStack<T>::pop()
    {
        if(empty())
            throw std::out_of_range("pop() error,stack is empty!");
        linkStack<T>::Node* temp=m_Stack;
        m_Stack=m_Stack->next;
        delete temp;
    }
};

#endif