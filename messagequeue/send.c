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
    printf("key:============== %d\n", key);
    int msgid = msgget(key, IPC_CREAT|O_WRONLY|0777);
    printf("msgid======%d\n", msgid);
    if(msgid < 0)
    {
        printf("msgget error!======\n");
        exit(-1);
    }
    Msg msg;
    puts("please input your type name age:");
    scanf("%ld%s%d", &msg.type, msg.name, &msg.age);
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(msg.type), 0);

    printf("Hello World!\n");
    return 0;
}


