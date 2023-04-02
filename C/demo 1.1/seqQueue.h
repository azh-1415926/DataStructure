#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_
#include<stdio.h>
#include<stdbool.h>
#define QUEUE_PUSH 1
#define QUEUE_POP 0
typedef int Type;
typedef struct seqQueue {
    Type rear;
    Type front;
    Type *pQueue;
    int capacity;
    int flag;
}*seqQueue;
void seqQueueInitalize(seqQueue* ppQueue,int capacity);
bool seqQueueIsEmpty(seqQueue queue);
bool seqQueueIsFull(seqQueue queue);
void seqQueueEnqueue(seqQueue queue,Type data);
Type seqQueueFront(seqQueue queue);
void seqQueueDequeue(seqQueue queue);
void seqQueueFree(seqQueue* queue);
#endif