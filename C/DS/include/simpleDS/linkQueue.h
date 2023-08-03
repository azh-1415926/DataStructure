#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

typedef struct linkQueueNode {
    void* data;
    struct linkQueueNode *next;
}linkQueueNode,*linkQueue;

void linkQueueInitalize(linkQueue* ppQueue);
void linkQueueFree(linkQueue* ppQueue);
bool linkQueueIsEmpty(linkQueue const queue);
void linkQueueEnqueue(linkQueue queue,void* const data);
void* linkQueueFront(linkQueue const queue);
void linkQueueDequeue(linkQueue queue);

#ifdef __cplusplus
}
#endif

#endif