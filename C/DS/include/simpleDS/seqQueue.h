#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdbool.h>

#define QUEUE_PUSH 1
#define QUEUE_POP 0

typedef struct seqQueue {
    int rear;
    int front;
    void** pQueue;
    int capacity;
    int flag;
}*seqQueue;

void seqQueueInitalize(seqQueue* ppQueue,int capacity);
void seqQueueFree(seqQueue* queue);
bool seqQueueIsEmpty(seqQueue const queue);
bool seqQueueIsFull(seqQueue const queue);
void seqQueueEnqueue(seqQueue queue,void* const data);
void* seqQueueFront(seqQueue const queue);
void seqQueueDequeue(seqQueue queue);

#ifdef __cplusplus
}
#endif

#endif