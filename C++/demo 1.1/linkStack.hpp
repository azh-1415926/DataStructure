#ifndef _LINK_STACK_H_
#define _LINK_STACK_H_
#include <iostream>
template<class Type>
class linkStack {
    class node {
    public:    
        Type data;
        node* next;
        node(Type _data,node* _next=nullptr):data(_data),next(_next){};
    };
    node* pStack;
    public:
    linkStack();
    bool empty();
    void push(Type const& data);
    void pop();
    Type& top();
    ~linkStack();
};
template<class Type>
linkStack<Type>::linkStack(){
    pStack=new linkStack<Type>::node(0);
    pStack->next=nullptr;
}
template<class Type>
bool linkStack<Type>::empty(){
    return pStack->next==NULL;
}
template<class Type>
void linkStack<Type>::push(Type const& data){
    linkStack<Type>::node* temp=pStack;
    pStack=new linkStack<Type>::node(data,temp);
}
template<class Type>
void linkStack<Type>::pop(){
    if(empty())
        throw std::out_of_range("pop() error,stack is empty!");
    linkStack<Type>::node* temp=pStack;
    pStack=pStack->next;
    delete temp;
}
template<class Type>
Type& linkStack<Type>::top(){
    if(empty()){
        throw std::out_of_range("top() error,stack is empty!");
    }
    return pStack->data;
}
template<class Type>
linkStack<Type>::~linkStack(){
    linkStack<Type>::node* temp=pStack;
    while(pStack->next){
        pStack=pStack->next;
        delete temp;
    }
}
#endif