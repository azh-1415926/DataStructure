#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_
#include<stdio.h>
#include<stdbool.h>
typedef int Type;
typedef struct linkQueueNode {
    Type data;
    struct linkQueueNode *next;
}linkQueueNode,*linkQueue;
bool linkQueueInitalize(linkQueue* ppQueue);
bool linkQueueIsEmpty(linkQueue queue);
bool linkQueueEnqueue(linkQueue queue,Type data);
Type linkQueueFront(linkQueue queue);
bool linkQueueDequeue(linkQueue queue);
bool linkQueueFree(linkQueue* ppQueue);
#endif