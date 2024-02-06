#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

typedef void* eleType;

typedef struct linkQueueNode
{
    eleType data;
    struct linkQueueNode *next;
}linkQueueNode,*linkQueue;

linkQueue linkQueueInitalize(linkQueue* pQueue);
void linkQueueFree(linkQueue* pQueue);
bool linkQueueIsEmpty(const linkQueue queue);
eleType linkQueueFront(const linkQueue queue);
void linkQueueEnqueue(linkQueue queue,const eleType data);
void linkQueueDequeue(linkQueue queue);

#ifdef __cplusplus
}
#endif

#endif