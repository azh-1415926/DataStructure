#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_
#include<stdio.h>
#include<stdbool.h>
typedef struct seqStack {
    int top;
    void** bottom;
    int capacity;
}*seqStack;
void seqStackInitalize(seqStack* ppStack,int capacity);
void seqStackFree(seqStack* stack);
bool seqStackIsEmpty(seqStack const stack);
bool seqStackIsFull(seqStack const stack);
void seqStackPush(seqStack stack,void* const data);
void* seqStackTop(seqStack const stack);
void seqStackPop(seqStack stack);
#endif