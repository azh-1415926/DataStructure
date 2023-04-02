#ifndef _LINK_STACK_H_
#define _LINK_STACK_H_
#include<stdio.h>
#include<stdbool.h>
typedef int Type;
typedef struct linkStackNode {
    Type data;
    struct linkStackNode *next;
}linkStackNode;
typedef struct linkStack {
    struct linkStackNode *top;
    struct linkStackNode *bottom;
}*linkStack;
void linkStackInitalize(linkStack* ppStack);
bool linkStackIsEmpty(linkStack stack);
void linkStackPush(linkStack stack,Type data);
Type linkStackTop(linkStack stack);
void linkStackPop(linkStack stack);
void linkStackFree(linkStack* ppStack);
#endif