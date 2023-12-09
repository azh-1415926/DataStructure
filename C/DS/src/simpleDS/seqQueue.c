#include <simpleDS/seqQueue.h>
#include <stdlib.h>

void seqQueueInitalize(seqQueue* pQueue,int capacity)
{
    *pQueue=(seqQueue)malloc(sizeof(struct seqQueue));
    (*pQueue)->rear=0;
    (*pQueue)->front=0;
    (*pQueue)->pQueue=(eleType*)malloc(sizeof(eleType)*capacity);
    (*pQueue)->capacity=capacity;
    (*pQueue)->flag=QUEUE_POP;
}

void seqQueueFree(seqQueue* pQueue)
{
    free((*pQueue)->pQueue);
    free(*pQueue);
    *pQueue=(eleType)0;
}

bool seqQueueIsEmpty(seqQueue queue)
{
    return (queue->rear==queue->front)&&(queue->flag==QUEUE_POP);
}

bool seqQueueIsFull(seqQueue queue)
{
    return (queue->rear==queue->front)&&(queue->flag==QUEUE_PUSH);
}

void seqQueueEnqueue(const seqQueue queue,eleType const data)
{
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_PUSH))
        return;
    queue->pQueue[queue->rear]=data;
    queue->rear=(queue->rear+1)%(queue->capacity);
    queue->flag=QUEUE_PUSH;
}

eleType seqQueueFront(const seqQueue queue)
{
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_POP))
        return (eleType)0;
    return queue->pQueue[queue->front];
}

void seqQueueDequeue(seqQueue queue)
{
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_POP))
        return;
    queue->front=(queue->front+1)%(queue->capacity);
    queue->flag=QUEUE_POP;
}