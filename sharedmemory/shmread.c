#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "shmdata.h"
#include <string.h>

int main()
{
    int running = 1; //程序是否继续运行的标志
    void *shm = NULL;//分配的共享内存的原始首地址
    struct SHARED_DATA_ST *shared;//指向shm
    int shmid;//共享内存标识符
    //创建共享内存
    shmid = shmget((key_t)1234, sizeof(struct SHARED_DATA_ST), 0666|IPC_CREAT);
    if(shmid == -1)
    {
        printf("shmget failed========\n");
        exit(EXIT_FAILURE);
    }
    //将共享内存映射到当前进程的地址空间
    shm = shmat(shmid, 0, 0);
    if(shm == (void*)-1)
    {
        printf("shmat failed==============\n");
        exit(EXIT_FAILURE);
    }
    printf("\nMemory attached at %d\n", (int)shm);
    //设置共享内存
    shared = (struct SHARED_DATA_ST*)shm;
    shared->written = 0;
    while (running) //读取共享内存中的数据
    {
        //没有进程向共享内存写数据有数据可读取
        if(shared->written != 0)
        {
            printf("You write: %s\n", shared->text);
            sleep(rand() % 3);
            //读取完数据，设置written使共享内存段可写
            shared->written = 0;
            //输入了end,退出循环（程序）
            if(strncmp(shared->text, "end", 3) == 0)
                running = 0;
        }
        else //有其他进程在写数据，不能读取数据
        {
            sleep(1);
        }
    }
    //把共享内存从当前进程中分享
    if(shmdt(shm) == -1)
    {
        printf("shmdt failed===========\n");
        exit(EXIT_FAILURE);
    }
    //删除共享内存
    if(shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("shmctl(IPC_RMID) failed======\n");
        exit(EXIT_FAILURE);
    }
    printf("Hello World!\n");
    return 0;
}











