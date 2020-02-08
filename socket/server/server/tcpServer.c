//
//  tcpServer.c
//  socket
//
//  Created by chenyijun on 2020/2/8.
//  Copyright © 2020 chenyijun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5555

int main(int argc, const char * argv[]) {
    // 1.创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        printf("server socket failed====\n");
        exit(-1);
    }
    else
    {
        printf("server socket success====\n");
    }
    //2.准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton("192.168.1.102", &addr.sin_addr);
    
    //3.绑定socket和通信地址
    int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if(-1 == res)
    {
        printf("server bind failed===========\n");
        exit(-1);
    }
    //4.监听端口
    res = listen(sockfd, 100);
    if(res == -1)
    {
        printf("sever listen failed=======\n");
        exit(-1);
    }
    printf("start listen %d port, wait client connect.....\n", PORT);
    //5.处理接收客户端的连接请求，
    //用于保存客户端地址信息
    struct sockaddr_in fromaddr;
    //len取0会是什么效果？
    socklen_t len = sizeof(fromaddr);
    int clientfd = accept(sockfd, (struct sockaddr *)&fromaddr, &len);
    if(-1 == clientfd)
    {
        printf("sever accept failed=========\n");
        exit(-1);
    }
    printf("have a client connent sever , is : %s\n", inet_ntoa(fromaddr.sin_addr));
    //6.处理客户端数据
    char buf[100] = {0};
    ssize_t count = recv(clientfd, buf, sizeof(buf), 0);
    printf("from client read %ld byte : %s\n", count, buf);
    char *str = "welcome you client";
    send(clientfd, str, strlen(str), 0);
    //关闭连接
    close(clientfd);
    close(sockfd);
    
    
    printf("Hello, World!\n");
    return 0;
}
