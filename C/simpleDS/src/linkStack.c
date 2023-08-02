#include "linkStack.h"
#include<stdlib.h>
void linkStackInitalize(linkStack* ppStack){
    *ppStack=(linkStack)malloc(sizeof(struct linkStack));
    (*ppStack)->bottom=(linkStackNode*)malloc(sizeof(struct linkStackNode));
    (*ppStack)->bottom->next=NULL;
    (*ppStack)->top=(*ppStack)->bottom->next;
}
void linkStackFree(linkStack* ppStack){
    linkStackNode* pStack=NULL;
    while((*ppStack)->top){
        pStack=(*ppStack)->top;
        (*ppStack)->top=pStack->next;
        free(pStack);
    }
    free(*ppStack);
    *ppStack=NULL;
}
bool linkStackIsEmpty(linkStack const stack){
    return stack->top==NULL;
}
void linkStackPush(linkStack stack,void* const data){
    linkStackNode* pStack=stack->top;
    stack->top=(linkStackNode*)malloc(sizeof(struct linkStackNode));
    stack->top->next=pStack;
    stack->top->data=data;
}
void* linkStackTop(linkStack const stack){
    if(stack->top==NULL)
        return NULL;
    return stack->top->data;
}
void linkStackPop(linkStack stack){
    if(stack->top==NULL)
        return;
    linkStackNode* pStack=stack->top;
    stack->top=pStack->next;
    free(pStack);
}