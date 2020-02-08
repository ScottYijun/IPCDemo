//
//  tcpClient.c
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
        printf("client socket failed========\n");
        exit(-1);
    }
    else
    {
        printf("client socket success========\n");
    }
    
    //2.准备通信地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    //设置为服务器进程的端口号
    addr.sin_port = htons(PORT);
    //服务器所在主机的IP地址
    inet_aton("192.168.1.102", &addr.sin_addr);
    //3.连接服务器
    int res = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if(-1 == res)
    {
        printf("connect failed========\n");
        exit(-1);
    }
    printf("connect server success=======\n");
    //4.和服务器交换数
    char buf[100] = {0};
    char *str = "this is scott";
    write(sockfd, str, strlen(str));
    read(sockfd, buf, sizeof(buf));
    printf("server say:%s\n", buf);
    
    printf("Hello, tcpClient!\n");
    return 0;
}
