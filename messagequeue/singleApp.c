#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/ipc.h> //ftok()
#include <sys/msg.h>

typedef struct {
    long type;
    char name[20];
    int age;
}Msg;

int main()
{
    key_t key = ftok("/home/yijun/project", '6');
    
    int msgid = msgget(key, O_RDONLY);
    printf("key:============== %d msgid======%d\n", key, msgid);
    if(msgid < 0) //app not run
    {
    	printf("app not run======msgid======%d\n", msgid);
    	msgid = msgget(key, IPC_CREAT|0777);
    }
    else
    {
    	printf("app is run======msgid======%d\n", msgid);
    	exit(0);
    }
	
    if(msgid < 0)
    {
        printf("msgget error!======\n");
        exit(-1);
    }
    printf("app first run\n");
    while(1) //do work
    	;
    msgctl(msgid, IPC_RMID, NULL);//删除消息队列对象
    printf("app exit\n");
    return 0;
}


