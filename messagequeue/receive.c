#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
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
    int msgid = msgget(key, O_RDONLY);
    printf("msgid:============== %d\n", msgid);
    if(msgid < 0)
    {
        perror("msgget error!");
        exit(-1);
    }
    Msg rcv;
    long type;
    puts("please input type you want!");
    scanf("%ld", &type);
    msgrcv(msgid, &rcv, sizeof(rcv) - sizeof(type), type, 0);
    printf("receive--- name:%s age:%d\n", rcv.name, rcv.age);
    msgctl(msgid, IPC_RMID, NULL);//删除消息队列对象

    printf("Hello World!\n");
    return 0;
}
