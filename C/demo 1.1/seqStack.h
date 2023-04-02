#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_
#include<stdio.h>
#include<stdbool.h>
typedef int Type;
typedef struct seqStack {
    Type top;
    Type* bottom;
    int capacity;
}*seqStack;
void seqStackInitalize(seqStack* ppStack,int capacity);
bool seqStackIsEmpty(seqStack stack);
bool seqStackIsFull(seqStack stack);
void seqStackPush(seqStack stack,Type data);
Type seqStackTop(seqStack stack);
void seqStackPop(seqStack stack);
void seqStackFree(seqStack* stack);
#endif