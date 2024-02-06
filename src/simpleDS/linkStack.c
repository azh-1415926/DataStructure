#include <simpleDS/linkStack.h>
#include <stdlib.h>

linkStack linkStackInitalize(linkStack* pStack)
{
    *pStack=(linkStack)malloc(sizeof(struct linkStack));
    (*pStack)->bottom=(linkStackNode*)malloc(sizeof(struct linkStackNode));
    (*pStack)->bottom->next=(eleType)0;
    (*pStack)->top=(*pStack)->bottom->next;
}

void linkStackFree(linkStack* pStack)
{
    linkStackNode* temp=(eleType)0;
    while((*pStack)->top)
    {
        temp=(*pStack)->top;
        (*pStack)->top=temp->next;
        free(temp);
    }
    free(*pStack);
    *pStack=(eleType)0;
}

bool linkStackIsEmpty(const linkStack stack)
{
    return stack->top==(eleType)0;
}

eleType linkStackTop(const linkStack stack)
{
    if(stack->top==(eleType)0)
        return (eleType)0;
    return stack->top->data;
}

void linkStackPush(linkStack stack,const eleType data)
{
    linkStackNode* pStack=stack->top;
    stack->top=(linkStackNode*)malloc(sizeof(struct linkStackNode));
    stack->top->next=pStack;
    stack->top->data=data;
}

void linkStackPop(linkStack stack)
{
    if(stack->top==(eleType)0)
        return;
    linkStackNode* pStack=stack->top;
    stack->top=pStack->next;
    free(pStack);
}