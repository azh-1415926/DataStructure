#include "linkQueue.h"
#include<stdlib.h>
bool linkQueueInitalize(linkQueue* ppQueue){
    if(ppQueue==NULL){
        printf("please input incorrect point,Initalize failed!\n");
        return false;
    }
    *ppQueue=(linkQueueNode*)malloc(sizeof(struct linkQueueNode));
    if(*ppQueue==NULL){
        printf("malloc error,Initalize failed!\n");
        return false;
    }
    (*ppQueue)->next=NULL;
    return true;
}
bool linkQueueIsEmpty(linkQueue queue){
    if(queue==NULL){
        printf("queue is null,please initalize it!\n");
        return true;
    }
    return queue->next==NULL;
}
bool linkQueueEnqueue(linkQueue queue,Type data){
    if(queue==NULL){
        printf("queue is null,Enqueue failed!\n");
        return false;
    }
    linkQueue pQueue=queue->next;
    queue->next=(linkQueueNode*)malloc(sizeof(struct linkQueueNode));
    if(queue->next==NULL){
        printf("malloc error,Enqueue failed!\n");
        queue->next=pQueue;
        return false;
    }
    queue->next->next=pQueue;
    queue->next->data=data;
    return true;
}
Type linkQueueFront(linkQueue queue){
    if(queue==NULL){
        printf("queue is null,get Front element failed!\n");
        return 0;
    }else if(queue->next==NULL){
        printf("queue is empty,get Front element failed!\n");
        return 0;
    }
    return queue->next->data;
}
bool linkQueueDequeue(linkQueue queue){
    if(queue==NULL){
        printf("queue is null,Dequeue failed!\n");
        return false;
    }else if(queue->next==NULL){
        printf("queue is empty,Dequeue failed!\n");
        return false;
    }
    linkQueue pQueue=queue->next;
    queue->next=pQueue->next;
    free(pQueue);
    return true;
}
bool linkQueueFree(linkQueue* ppQueue){
    if((*ppQueue)==NULL){
        printf("queue is null,Free failed!\n");
        return false;
    }
    linkQueue pQueue=NULL;
    while((*ppQueue)->next){
        pQueue=(*ppQueue)->next;
        (*ppQueue)->next=pQueue->next;
        free(pQueue);
    }
    free(*ppQueue);
    *ppQueue=NULL;
    return true;
}