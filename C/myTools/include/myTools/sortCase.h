#ifndef _SORT_CASE_H_
#define _SORT_CASE_H_

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* eleType;

void initalCase(void(*inital)(eleType,int));
eleType* createCase(eleType* array,int n);
eleType* createCaseNoRepeat(eleType* array,int n,int leftRange,int rightRange);
void showCase(eleType* array,int n,void(*show)(const eleType));
bool verifyCase(eleType* array,int n,int(*compare)(const eleType,const eleType));

#ifdef __cplusplus
}
#endif

#endif /* _SORT_CASE_H_ */