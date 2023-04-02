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
bool linkStackInitalize(linkStack* ppStack);
bool linkStackIsEmpty(linkStack stack);
bool linkStackPush(linkStack stack,Type data);
Type linkStackTop(linkStack stack);
bool linkStackPop(linkStack stack);
bool linkStackFree(linkStack* ppStack);
#endif