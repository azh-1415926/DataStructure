#ifndef _LOG_H_
#define _LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#define LOG_BEGIN "[ BEGIN ]"
#define LOG_END "[ END ]"

bool exportLog(const char* fileName,const char* log);
char** readLogs(const char* fileName,int* n);
void freeLogs(char** str,int n);

#ifdef __cplusplus
}
#endif

#endif /* _LOG_H_ */