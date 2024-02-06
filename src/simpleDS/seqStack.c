#include <simpleDS/seqStack.h>
#include <stdlib.h>

seqStack seqStackInitalize(seqStack* pStack,int capacity)
{
    *pStack=(seqStack)malloc(sizeof(struct seqStack));
    (*pStack)->data=(eleType*)malloc(sizeof(eleType)*capacity);
    (*pStack)->top=capacity;
    (*pStack)->capacity=capacity;
}

void seqStackFree(seqStack* pStack)
{
    free((*pStack)->data);
    free(*pStack);
    *pStack=(eleType)0;
}

bool seqStackIsEmpty(const seqStack stack)
{
    return stack->top==stack->capacity;
}

bool seqStackIsFull(const seqStack stack)
{
    return stack->top==0;
}

void seqStackPush(seqStack stack,eleType const data)
{
    if(stack->top==0)
        return;
    stack->data[--stack->top]=data;
}

eleType seqStackTop(const seqStack stack)
{
    if(stack->top==stack->capacity)
        return (eleType)0;
    return stack->data[stack->top];
}

void seqStackPop(seqStack stack)
{
    if(stack->top==stack->capacity)
        return;
    stack->top++;
}