#ifndef LINK_STACK_H
#define LINK_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

typedef void* eleType;

typedef struct linkStackNode
{
    eleType data;
    struct linkStackNode *next;
}linkStackNode;

typedef struct linkStack
{
    struct linkStackNode *top;
    struct linkStackNode *bottom;
}*linkStack;

linkStack linkStackInitalize(linkStack* pStack);
void linkStackFree(linkStack* pStack);
bool linkStackIsEmpty(const linkStack stack);
eleType linkStackTop(const linkStack stack);
void linkStackPush(linkStack stack,const eleType data);
void linkStackPop(linkStack stack);

#ifdef __cplusplus
}
#endif

#endif