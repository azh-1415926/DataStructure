#include "linkStack.h"
#include<stdlib.h>
bool linkStackInitalize(linkStack* ppStack){
    if(ppStack==NULL){
        printf("please input incorrect point,Initalize failed!\n");
        return false;
    }
    *ppStack=(linkStack)malloc(sizeof(struct linkStack));
    if(*ppStack==NULL){
        printf("malloc error,Initalize failed!\n");
        return false;
    }
    (*ppStack)->top=NULL;
    (*ppStack)->bottom=NULL;
    return true;
}
bool linkStackIsEmpty(linkStack stack){
    if(stack==NULL){
        printf("stack is null,please initalize it!\n");
        return true;
    }
    return stack->top==NULL;
}
bool linkStackPush(linkStack stack,Type data){
    if(stack==NULL){
        printf("stack is null,Push failed!\n");
        return false;
    }
    linkStackNode* pStack=stack->top;
    stack->top=(linkStackNode*)malloc(sizeof(struct linkStackNode));
    if(stack->top==NULL){
        printf("malloc error,Push failed!\n");
        stack->top=pStack;
        return false;
    }
    if(stack->bottom==NULL)
        stack->bottom=stack->top;
    stack->top->next=pStack;
    stack->top->data=data;
    return true;
}
Type linkStackTop(linkStack stack){
    if(stack==NULL){
        printf("stack is null,read Top element failed!\n");
        return 0;
    }else if(stack->top==NULL){
        printf("stack is empty,read Top element failed!\n");
        return 0;
    }
    return stack->top->data;
}
bool linkStackPop(linkStack stack){
    if(stack==NULL){
        printf("stack is null,Pop failed!\n");
        return false;
    }else if(stack->top==NULL){
        printf("stack is empty,Pop failed!\n");
        return false;
    }
    linkStackNode* pStack=stack->top;
    stack->top=pStack->next;
    free(pStack);
    if(stack->top==NULL)
        stack->bottom=stack->top;
    return true;
}
bool linkStackFree(linkStack* ppStack){
    if(ppStack==NULL){
        printf("stack is null,Free failed!\n");
        return false;
    }
    linkStackNode* pStack=NULL;
    while((*ppStack)->top){
        pStack=(*ppStack)->top;
        (*ppStack)->top=pStack->next;
        free(pStack);
    }
    free(*ppStack);
    *ppStack=NULL;
    return true;
}