#include <myDS/trie.h>
#include <simpleDS/linkQueue.h>
#include <stdlib.h>

static trieNode* createTrieNode()
{
    trieNode* trie=(trieNode*)malloc(sizeof(trieNode));
    trie->pass=0;
    trie->end=0;
    for(int i=0;i<26;i++)
        trie->next[i]=NULL;
    return trie;
}

void trieInitalize(Trie *tree)
{
    if(tree==NULL)
        return;
    *tree=createTrieNode();
}

void trieFree(Trie *tree)
{
    linkQueue queue;
    linkQueueInitalize(&queue);
    trieNode* currNode=NULL;
    linkQueueEnqueue(queue,*tree);
    *tree=NULL;
    while(!linkQueueIsEmpty(queue)){
        currNode=(trieNode*)linkQueueFront(queue);
        linkQueueDequeue(queue);
        for(int i=0;i<26;i++)
            if(currNode->next[i]!=NULL)
                linkQueueEnqueue(queue,currNode->next[i]);
        free(currNode);
    }
    linkQueueFree(&queue);
}

void trieInsert(Trie tree, const char *str)
{

}

void trieDelete(Trie tree, const char *str)
{

}

int trieSearch(Trie tree, const char *str)
{
    return 0;
}

int trieSearchByPrefix(Trie tree, const char *prefix)
{
    return 0;
}