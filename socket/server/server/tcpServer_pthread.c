//
//  udpServer_pthread.c
//  server
//
//  Created by chenyijun on 2020/2/8.
//  Copyright © 2020 chenyijun. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#define PORT 11111

void *read_func(void *argv)
{
    int fd = *(int *)argv;
    ssize_t ret = -1;
    char buf[10] = {'\0'};
    //读取客户端的信息
    ret = read(fd, buf, 9);
    if(ret < 0)
    {
        printf("server read data failed\n");
        pthread_exit(NULL);
    }
    
    while(1)
    {
        sleep(1);
        if(strncmp(buf, "hello", 5) == 0)
        {
            write(fd, "world", 6);
        }
        else
        {
            printf("is not [hello]\n");
            write(fd, "nothe", 6);
        }
    }
}

int main()
{
    int fd = -1;
    int new_fd = -1;
    int ret = 0;
    char buf[6];
    pthread_t th_id;
    struct sockaddr_in server_add;
    //1.建立socket连接
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        printf("tcp server pthread socket failed\n");
        exit(-1);
    }
    
    memset(&server_add, 0, sizeof(server_add));
    //2.设置sockaddr_in结构体中的相关参数
    server_add.sin_family = AF_INET;
    server_add.sin_port = htons(PORT);
    server_add.sin_addr.s_addr = inet_addr("192.168.1.102");
    //3.绑定
    ret = bind(fd, (struct sockaddr *)&server_add, sizeof(struct sockaddr));
    if(ret < 0)
    {
        printf("tcp server pthread bind failed\n");
    }
    else
    {
        printf("tcp server pthread bind success fd= %d\n", fd);
    }
    //4.监听，创建处理请求的队列
    int nListen = listen(fd, 5);
    printf("tcp server pthread nListen = %d\n", nListen);
    while(1)
    {
        //5.accept(),等待客户端的连接
        new_fd = accept(fd, NULL, NULL);
        if(new_fd < 0)
        {
            printf("server accept failed\n");
            exit(-1);
        }
        else
        {
            printf("server accept success new_fd = %d\n", new_fd);
        }
        //6.创建线程，用于读取客户端信息
        pthread_create(&th_id, NULL, read_func, &new_fd);
    }
    
    return 0;
}
