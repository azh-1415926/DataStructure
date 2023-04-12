#include<stdlib.h>
#include "seqStack.h"
void seqStackInitalize(seqStack* ppStack,int capacity){
    *ppStack=(seqStack)malloc(sizeof(struct seqStack));
    (*ppStack)->bottom=(void**)malloc(sizeof(void*)*capacity);
    (*ppStack)->top=capacity;
    (*ppStack)->capacity=capacity;
}
void seqStackFree(seqStack* ppStack){
    free((*ppStack)->bottom);
    free(*ppStack);
    *ppStack=NULL;
}
bool seqStackIsEmpty(seqStack const stack){
    return stack->top==stack->capacity;
}
bool seqStackIsFull(seqStack const stack){
    return stack->top==0;
}
void seqStackPush(seqStack stack,void* const data){
    if(stack->top==0)
        return;
    stack->bottom[--stack->top]=data;
}
void* seqStackTop(seqStack const stack){
    if(stack->top==stack->capacity)
        return NULL;
    return stack->bottom[stack->top];
}
void seqStackPop(seqStack stack){
    if(stack->top==stack->capacity)
        return;
    stack->top++;
}