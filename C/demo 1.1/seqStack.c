#include<stdlib.h>
#include "seqStack.h"
void seqStackInitalize(seqStack* ppStack,int capacity){
    *ppStack=(seqStack)malloc(sizeof(struct seqStack));
    (*ppStack)->bottom=(Type*)malloc(sizeof(Type)*capacity);
    (*ppStack)->top=capacity;
    (*ppStack)->capacity=capacity;
}
bool seqStackIsEmpty(seqStack stack){
    return stack->top==stack->capacity;
}
bool seqStackIsFull(seqStack stack){
    return stack->top==0;
}
void seqStackPush(seqStack stack,Type data){
    if(stack->top==0)
        return;
    stack->bottom[--stack->top]=data;
}
Type seqStackTop(seqStack stack){
    if(stack->top==stack->capacity)
        return 0;
    return stack->bottom[stack->top];
}
void seqStackPop(seqStack stack){
    if(stack->top==stack->capacity)
        return;
    stack->top++;
}
void seqStackFree(seqStack* ppStack){
    free((*ppStack)->bottom);
    free(*ppStack);
    *ppStack=NULL;
}