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
    if(tree==NULL)
        return;
    trieNode* currNode=tree;
    for(int i=0;str[i]!='\0';i++){
        // no that road
        if(currNode->next[str[i]-'a']==NULL){
            currNode->next[str[i]-'a']=createTrieNode();
        }
        currNode->pass++;
        currNode=currNode->next[str[i]-'a'];
    }
    if(currNode!=tree){
        currNode->pass++;
        currNode->end++;
    }
}

void trieDelete(Trie tree, const char *str)
{
    if(tree==NULL||trieSearch(tree,str)==0)
        return;
    trieNode* currNode=tree;
    for(int i=0;str[i]!='\0';i++){
        if(--currNode->pass==0){
            if(currNode!=tree)
                trieFree(&currNode);
            else
                trieFree(&currNode->next[str[i]-'a']);
            return;
        }
        currNode=currNode->next[str[i]-'a'];
    }
    currNode->pass--;
    currNode->end--;
}

int trieSearch(Trie tree, const char *str)
{
    if(tree==NULL)
        return 0;
    trieNode* currNode=tree;
    for(int i=0;str[i]!='\0';i++){
        // no that road
        if(currNode->next[str[i]-'a']==NULL)
            break;
        currNode=currNode->next[str[i]-'a'];
    }
    return currNode->end;
}

int trieSearchByPrefix(Trie tree, const char *prefix)
{
    if(tree==NULL)
        return 0;
    trieNode* currNode=tree;
    for(int i=0;prefix[i]!='\0';i++){
        // no that road
        if(currNode->next[prefix[i]-'a']==NULL)
            break;
        currNode=currNode->next[prefix[i]-'a'];
    }
    return currNode->pass;
}
int trieGetSum(Trie tree)
{
    if(tree==NULL)
        return 0;
    return tree->pass;
}