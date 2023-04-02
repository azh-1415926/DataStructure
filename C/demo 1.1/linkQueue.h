#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_
#include<stdio.h>
#include<stdbool.h>
typedef int Type;
typedef struct linkQueueNode {
    Type data;
    struct linkQueueNode *next;
}linkQueueNode,*linkQueue;
void linkQueueInitalize(linkQueue* ppQueue);
bool linkQueueIsEmpty(linkQueue queue);
void linkQueueEnqueue(linkQueue queue,Type data);
Type linkQueueFront(linkQueue queue);
void linkQueueDequeue(linkQueue queue);
void linkQueueFree(linkQueue* ppQueue);
#endif