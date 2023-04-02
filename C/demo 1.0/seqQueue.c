#include<stdlib.h>
#include "seqQueue.h"
bool seqQueueInitalize(seqQueue* ppQueue,int capacity){
    if(ppQueue==NULL){
        printf("please input incorrect point,Initalize failed!\n");
        return false;
    }
    *ppQueue=(seqQueue)malloc(sizeof(struct seqQueue));
    if(*ppQueue==NULL){
        printf("malloc error,Initalize failed!\n");
        return false;
    }
    (*ppQueue)->rear=0;
    (*ppQueue)->front=0;
    (*ppQueue)->pQueue=(Type*)malloc(sizeof(Type)*capacity);
    (*ppQueue)->capacity=capacity;
    (*ppQueue)->flag=QUEUE_POP;
    return true;
}
bool seqQueueIsEmpty(seqQueue queue){
    if(queue==NULL){
        printf("queue is null,please initalize it!\n");
        return true;
    }
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_POP)){
        return true;
    }
    return false;
}
bool seqQueueIsFull(seqQueue queue){
    if(queue==NULL){
        printf("queue is null,please initalize it!\n");
        return false;
    }
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_PUSH)){
        return true;
    }
    return false;
}
bool seqQueueEnqueue(seqQueue queue,Type data){
    if(queue==NULL){
        printf("queue is null,Enqueue failed!\n");
        return false;
    }
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_PUSH)){
        printf("queue is full,Enqueue failed!\n");
        return false;
    }
    queue->pQueue[queue->rear]=data;
    queue->rear=(queue->rear+1)%(queue->capacity);
    queue->flag=QUEUE_PUSH;
    return true;
}
Type seqQueueDequeue(seqQueue queue){
    if(queue==NULL){
        printf("queue is null,Dequeue failed!\n");
        return false;
    }
    if((queue->rear==queue->front)&&(queue->flag==QUEUE_POP)){
        printf("queue is empty,Dequeue failed!\n");
        return 0;
    }
    Type data=queue->pQueue[queue->front];
    queue->front=(queue->front+1)%(queue->capacity);
    queue->flag=QUEUE_POP;
    return data;
}
bool seqQueueFree(seqQueue* ppQueue){
    if(ppQueue==NULL){
        printf("queue is null,Free failed!\n");
        return false;
    }
    free((*ppQueue)->pQueue);
    free(*ppQueue);
    *ppQueue=NULL;
    return true;
}