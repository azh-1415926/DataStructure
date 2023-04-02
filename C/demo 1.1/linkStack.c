#include "linkStack.h"
#include<stdlib.h>
void linkStackInitalize(linkStack* ppStack){
    *ppStack=(linkStack)malloc(sizeof(struct linkStack));
    (*ppStack)->top=NULL;
    (*ppStack)->bottom=NULL;
}
bool linkStackIsEmpty(linkStack stack){
    return stack->top==NULL;
}
void linkStackPush(linkStack stack,Type data){
    linkStackNode* pStack=stack->top;
    stack->top=(linkStackNode*)malloc(sizeof(struct linkStackNode));
    if(stack->bottom==NULL)
        stack->bottom=stack->top;
    stack->top->next=pStack;
    stack->top->data=data;
}
Type linkStackTop(linkStack stack){
    if(stack->top==NULL)
        return 0;
    return stack->top->data;
}
void linkStackPop(linkStack stack){
    if(stack->top==NULL)
        return;
    linkStackNode* pStack=stack->top;
    stack->top=pStack->next;
    free(pStack);
    if(stack->top==NULL)
        stack->bottom=stack->top;
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