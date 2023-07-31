#ifndef _TEST_CASE_H_
#define _TEST_CASE_H_

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int eleType;

void initalCase(void(*inital)(void*,int));
eleType* createCase(eleType* array,int n);
eleType* createCaseNoRepeat(eleType* array,int n,int leftRange,int rightRange);
void showCase(eleType* array,int n,void(*show)(void*));
bool verifyCase(eleType* array,int n,int(*compare)(void*,void*));

#ifdef __cplusplus
}
#endif

#endif /* _TEST_CASE_H_ */