#ifndef _TRIE_H_
#define _TRIE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef struct trieNode
{
    int pass;
    int end;
    struct trieNode* next[26];
}trieNode,*Trie;

void trieInitalize(Trie* tree);
void trieFree(Trie* tree);
void trieInsert(Trie tree,const char* str);
void trieDelete(Trie tree,const char* str);
int trieSearch(Trie tree,const char* str);
int trieSearchByPrefix(Trie tree,const char* prefix);
int trieGetSum(Trie tree);

#ifdef __cplusplus
}
#endif

#endif /* _TRIE_H_ */