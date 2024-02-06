#include <myDS/trie.h>

int main(){
    Trie tree;
    trieInitalize(&tree);
    const char* str1="test";
    const char* str2="test1";
    printf("Insert str:\"%s\",\"%s\"\n",str1,str2);
    trieInsert(tree,str1);
    trieInsert(tree,str2);
    printf("Search str:\"%s\",count is %d\n",str1,trieSearch(tree,str1));
    printf("Search prefix str:\"%s\",count is %d\n",str1,trieSearchByPrefix(tree,str1));
    printf("Sum is %d\n",trieGetSum(tree));
    printf("Delete str:\"%s\"\n",str1);
    trieDelete(tree,str1);
    printf("Sum is %d\n",trieGetSum(tree));
    printf("Delete str:\"%s\"\n",str2);
    trieDelete(tree,str2);
    printf("Sum is %d\n",trieGetSum(tree));
    printf("Search prefix str:\"%s\",count is %d\n",str1,trieSearchByPrefix(tree,str1));
    trieFree(&tree);
    return 0;
}