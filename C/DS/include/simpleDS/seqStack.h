#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

typedef void* eleType;

typedef struct seqStack
{
    eleType* data;
    int top;
    int capacity;
}*seqStack;

seqStack seqStackInitalize(seqStack* pStack,int capacity);
void seqStackFree(seqStack* pStack);
bool seqStackIsEmpty(const seqStack stack);
bool seqStackIsFull(const seqStack stack);
void seqStackPush(seqStack stack,const eleType data);
eleType seqStackTop(const seqStack stack);
void seqStackPop(seqStack stack);

#ifdef __cplusplus
}
#endif

#endif