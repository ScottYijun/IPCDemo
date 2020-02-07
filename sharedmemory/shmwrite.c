#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "shmdata.h"

int main()
{
    int running = 1;
    void *shm = NULL;
    struct SHARED_DATA_ST *shared = NULL;
    char buffer[BUFSIZ + 1];// 用于保存输入的文本
    int shmid;
    //创建共享内存
    shmid = shmget((key_t)1234, sizeof(struct SHARED_DATA_ST), 0666|IPC_CREAT);
    if(shmid == -1)
    {
        printf("shmget failed=========\n");
        exit(EXIT_FAILURE);
    }
    //将共享内存映射到当前进程的地址空间
    shm = shmat(shmid, (void*)0, 0);
    if(shm == (void*)-1)
    {
        printf("shmat failed=======\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %lX\n", (unsigned long)shm);
    //设置共享内存
    shared = (struct SHARED_DATA_ST*)shm;
    while(running)//向共享内存中写数据
    {
        //数据还没有被读取，则等待数据被读取，不能向共享内存中写入文本
        while(shared->written == 1)
        {
            sleep(1);
            printf("Waiting.....\n");
        }
        //向共享内存中写入数据
        printf("Enter some text:\n");
        fgets(buffer, BUFSIZ, stdin);
        strncpy(shared->text, buffer, TEXT_SZ);
        //写完数据，设置written使共享内存段可读
        shared->written = 1;
        //输入了end，退出特环（程序）
        if(strncmp(buffer, "end", 3) == 0)
            running = 0;
    }
    //把共享内存从当前进程中分离
    if(shmdt(shm) == -1)
    {
        printf("shmdt failed=============\n");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    printf("Hello World!\n");
    return 0;
}
