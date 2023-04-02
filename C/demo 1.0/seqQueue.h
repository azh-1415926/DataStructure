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
bool seqQueueInitalize(seqQueue* ppQueue,int capacity);
bool seqQueueIsEmpty(seqQueue queue);
bool seqQueueIsFull(seqQueue queue);
bool seqQueueEnqueue(seqQueue queue,Type data);
Type seqQueueDequeue(seqQueue queue);
bool seqQueueFree(seqQueue* queue);
#endif