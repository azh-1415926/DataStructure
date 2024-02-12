#ifndef SEQ_QUEUE_H
#define SEQ_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#define QUEUE_PUSH 1
#define QUEUE_POP 0

typedef void* eleType;

typedef struct seqQueue
{
    eleType* pQueue;
    int rear;
    int front;
    int capacity;
    int flag;
}*seqQueue;

void seqQueueInitalize(seqQueue* pQueue,int capacity);
void seqQueueFree(seqQueue* pQueue);
bool seqQueueIsEmpty(const seqQueue queue);
bool seqQueueIsFull(const seqQueue queue);
void seqQueueEnqueue(seqQueue queue,const eleType data);
eleType seqQueueFront(const seqQueue queue);
void seqQueueDequeue(seqQueue queue);

#ifdef __cplusplus
}
#endif

#endif