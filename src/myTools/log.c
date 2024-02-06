#include <myTools/log.h>

#include <time.h>
#include <stdlib.h>
#include <string.h>

bool exportLog(const char *fileName, const char *log)
{
    time_t now=time(NULL);
    struct tm* time;
    time=localtime(&now);
    char* format="%Y-%m-%d %H:%M:%S";
    char str[20];
    strftime(str,sizeof(str),format,time);
    FILE* f=fopen(fileName,"a");
    if(f==NULL)
        return false;
    fprintf(f,"%s\n%s\n%s\n%s\n",LOG_BEGIN,str,log,LOG_END);
    fclose(f);
    return true;
}

static int readLine(const char* str,int len)
{
    int end=0;
    while(end<len&&str[end++]!='\n');
    return end;
}

static int strCmp(const char* str1,const char* str2,int size)
{
    while(size-->0){
        if((*(str1+size)-*(str2+size))!=0)
            return (*(str1+size)-*(str2+size));
    }
    return 0;
}

static char* strCpy(char* str1,const char* str2,int size)
{
    while(size-->0)
        *(str1+size)=*(str2+size);
    return str1;
}

char **readLogs(const char *fileName, int *n)
{
    FILE* f=fopen(fileName,"r");
    if(f==NULL){
        *n=0;
        return NULL;
    }
    if(*n==-1)
        *n=BUFSIZ;
    char buf[BUFSIZ];
    char** logs=(char**)malloc(*n*sizeof(char*));
    char* temp=NULL;
    int index=0;
    int readSize=0;
    int flag=0;
    do{
        memset(buf,0,sizeof(buf));
        readSize=fread(buf,sizeof(buf),1,f);
        int start=0;
        int begin=0;
        int end=0;
        while(index<*n&&end<BUFSIZ-1){
            end=begin+readLine(buf+begin,BUFSIZ-begin);
            if(flag==0){
                if(end-begin-1==strlen(LOG_BEGIN)&&strCmp(buf+begin,LOG_BEGIN,strlen(LOG_BEGIN))==0){
                    start=end;
                    flag=1;
                }else{
                    if(temp!=NULL){
                        int len=strlen(temp);
                        if(strCmp(temp,LOG_BEGIN,len)==0&&strCmp(buf,LOG_BEGIN+strlen(LOG_BEGIN)-len,strlen(LOG_BEGIN)-len)){
                            begin=strlen(LOG_BEGIN)-len;
                        }
                    }
                    fclose(f);
                    logs[index]=NULL;
                    *n=index;
                    return logs;
                }
            }else if(flag==1){
                if(end-begin-1==strlen(LOG_END)&&strCmp(buf+begin,LOG_END,strlen(LOG_END))==0){
                    int len=0;
                    if(temp!=NULL)
                        len=strlen(temp);
                    logs[index]=(char*)malloc((begin-start+len+1)*sizeof(char));
                    strCpy(logs[index],temp,len);
                    strCpy(logs[index]+len,buf+start,begin-start);
                    logs[index][begin-start+len]='\0';
                    free(temp);
                    temp=NULL;
                    index++;
                    flag=0;
                }
            }
            begin=end;
        }
        if(flag==1){
            if(temp==NULL){
                temp=(char*)malloc((BUFSIZ-start+1)*sizeof(char));
                strCpy(temp,buf+start,BUFSIZ-start);
                temp[BUFSIZ-start]='\0';
            }else{
                int len=strlen(temp);
                char* temp2=(char*)malloc((BUFSIZ-start+len+1)*sizeof(char));
                strCpy(temp2,temp,len);
                strCpy(temp2+len,buf+start,BUFSIZ-start);
                temp[BUFSIZ-start+len]='\0';
                temp=temp2;
            }
        }
    }while(readSize);
    fclose(f);
    if(index<*n)
        logs[index]=NULL;
    *n=index;
    return logs;
}

void freeLogs(char **str, int n)
{
    if(str==NULL)
        return;
    for(int i=0;i<n;i++)
        free(str[i]);
}