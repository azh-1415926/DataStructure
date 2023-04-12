#ifndef _LINK_STACK_H_
#define _LINK_STACK_H_
#include<stdio.h>
#include<stdbool.h>
typedef struct linkStackNode {
    void* data;
    struct linkStackNode *next;
}linkStackNode;
typedef struct linkStack {
    struct linkStackNode *top;
    struct linkStackNode *bottom;
}*linkStack;
void linkStackInitalize(linkStack* ppStack);
void linkStackFree(linkStack* ppStack);
bool linkStackIsEmpty(linkStack const stack);
void linkStackPush(linkStack stack,void* const data);
void* linkStackTop(linkStack const stack);
void linkStackPop(linkStack stack);
#endif