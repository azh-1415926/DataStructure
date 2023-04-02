#include<stdlib.h>
#include "seqStack.h"
bool seqStackInitalize(seqStack* ppStack,int capacity){
    if(ppStack==NULL){
        printf("please input incorrect point,Initalize failed!\n");
        return false;
    }
    *ppStack=(seqStack)malloc(sizeof(struct seqStack));
    if(*ppStack==NULL){
        printf("malloc error,Initalize failed!\n");
        return false;
    }
    (*ppStack)->bottom=(Type*)malloc(sizeof(Type)*capacity);
    (*ppStack)->top=capacity;
    (*ppStack)->capacity=capacity;
    return true;
}
bool seqStackIsEmpty(seqStack stack){
    if(stack==NULL){
        printf("stack is null,please initalize it!\n");
        return false;
    }
    return stack->top==stack->capacity;
}
bool seqStackIsFull(seqStack stack){
    if(stack==NULL){
        printf("stack is null,please initalize it!\n");
        return false;
    }
    return stack->top==0;
}
bool seqStackPush(seqStack stack,Type data){
    if(stack==NULL){
        printf("stack is null,Push failed!\n");
        return false;
    }
    if(stack->top==0){
        printf("stack is full,Push failed!\n");
        return false;
    }
    stack->bottom[--stack->top]=data;
    return true;
}
Type seqStackTop(seqStack stack){
    if(stack==NULL){
        printf("stack is null,get Top element failed!\n");
        return 0;
    }
    if(stack->top==stack->capacity){
        printf("stack is empty,get Top element failed!\n");
        return 0;
    }
    return stack->bottom[stack->top];
}
void seqStackPop(seqStack stack){
    if(stack==NULL){
        printf("stack is null,Pop failed!\n");
        return;
    }
    if(stack->top==stack->capacity){
        printf("stack is empty,Pop failed!\n");
        return;
    }
    stack->top++;
}
bool seqStackFree(seqStack* ppStack){
    if(ppStack==NULL){
        printf("stack is null,Free failed!\n");
        return false;
    }
    free((*ppStack)->bottom);
    free(*ppStack);
    *ppStack=NULL;
    return true;
}