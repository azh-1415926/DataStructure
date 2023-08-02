#include <simpleDS/seqQueue.h>
#include<stdlib.h>

void seqQueueInitalize(seqQueue* ppQueue,int capacity)
{
    *ppQueue=(seqQueue)malloc(sizeof(struct seqQueue));
    (*ppQueue)->rear=0;
    (*ppQueue)->front=0;
    (*ppQueue)->pQueue=(void**)malloc(sizeof(void*)*capacity);
    (*ppQueue)->capacity=capacity;
    (*ppQueue)->flag=QUEUE_POP;
}

void seqQueueFree(seqQueue* ppQueue)
{
    free((*ppQueue)->pQueue);
    free(*ppQueue);
    *ppQueue=NULL;
}

bool seqQueueIsEmpty(seqQueue queue)
{
    return (queue->rear==queue->front)&&(queue->flag==QUEUE_POP);
}

bool seqQueueIsFull(seqQueue queue)
{
    return (queue->rear==queue->front)&&(queue->flag==QUEUE_PUSH);
}

void seqQueueEnqueue(seqQueue const queue,void* const data)
{
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_PUSH))
        return;
    queue->pQueue[queue->rear]=data;
    queue->rear=(queue->rear+1)%(queue->capacity);
    queue->flag=QUEUE_PUSH;
}

void* seqQueueFront(seqQueue const queue)
{
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_POP))
        return NULL;
    return queue->pQueue[queue->front];
}

void seqQueueDequeue(seqQueue queue)
{
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_POP))
        return;
    queue->front=(queue->front+1)%(queue->capacity);
    queue->flag=QUEUE_POP;
}