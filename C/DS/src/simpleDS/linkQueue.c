#include <simpleDS/linkQueue.h>
#include <stdlib.h>

linkQueue linkQueueInitalize(linkQueue* pQueue)
{
    *pQueue=(linkQueueNode*)malloc(sizeof(struct linkQueueNode));
    (*pQueue)->next=(eleType)0;
    return *pQueue;
}

void linkQueueFree(linkQueue* pQueue)
{
    linkQueue temp=(eleType)0;
    while((*pQueue)->next)
    {
        temp=(*pQueue)->next;
        (*pQueue)->next=temp->next;
        free(temp);
    }
    free(*pQueue);
    *pQueue=(eleType)0;
}

bool linkQueueIsEmpty(linkQueue queue)
{
    return queue->next==(eleType)0;
}

eleType linkQueueFront(const linkQueue queue)
{
    return queue->next->data;
}

void linkQueueEnqueue(linkQueue queue,const eleType data)
{
    linkQueue temp=queue;
    while(temp->next)
        temp=temp->next;
    temp->next=(linkQueueNode*)malloc(sizeof(struct linkQueueNode));
    temp=temp->next;
    temp->next=(eleType)0;
    temp->data=data;
}

void linkQueueDequeue(linkQueue pQueue)
{
    linkQueue temp=pQueue->next;
    pQueue->next=temp->next;
    free(temp);
}