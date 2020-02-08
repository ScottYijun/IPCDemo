//
//  tcpClient_pthread.c
//  client
//
//  Created by chenyijun on 2020/2/8.
//  Copyright © 2020 chenyijun. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 11111

void *recv_func(void *argv)
{
    char buf[10] = {'\0'};
    int fd = *(int *)argv;
    ssize_t ret = -1;
    
    while(1)
    {
        ret = read(fd, buf, 6);
        if(0 == ret)
        {
            printf("server is exit\n");
            exit(-1);
        }
        if(ret < 0)
        {
            printf("tcp client pthread read data failed\n");
            pthread_exit(NULL);
        }
        printf("tcp client pthread read data: %s\n", buf);
    }
}

int main()
{
    int fd = -1;
    int new_fd = -1;
    int ret = 0;
    char buf[10];
    pthread_t th_id;
    struct sockaddr_in client_add;
    //1.建立socket连接
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        perror("tcp client pthread socket failed\n");
        exit(-1);
    }
    else
    {
        printf("tcp client pthread socket success fd==%d\n", fd);
    }
    //2.设置sockaddr_in结构体中的相关参数
    client_add.sin_family = AF_INET;
    client_add.sin_port = htons(PORT);
    client_add.sin_addr.s_addr = inet_addr("192.168.1.102");
    //3.连接服务器
    ret = connect(fd, (struct sockaddr *)&client_add, sizeof(struct sockaddr));
    if(ret < 0)
    {
        perror("tcp client pthread connect failed\n");
        exit(-1);
    }
    //4.创建一个线程，用于接收服务器信息
    pthread_create(&th_id, NULL, recv_func, &fd);
    
    while (1)
    {
        memset(buf, 0, 6);
        fgets(buf, 6, stdin);
        write(fd, buf, 6);
        printf("tcp_client_pthread read: %s\n", buf);
    }
    
    close(fd);
    
    return 0;
}



