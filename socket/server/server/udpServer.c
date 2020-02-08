//
//  udpServer.c
//  server
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

#define PORT 22222

int main()
{
    //1.创建socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == fd)
    {
        printf("udp server socket failed\n");
        exit(-1);
    }
    else
    {
        printf("udp server socket success\n");
    }
    
    //2.准备地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton("192.168.1.102", &addr.sin_addr);
    
    //3.socket addr 绑定
    int res = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(-1 == res)
    {
        printf("udp server bind failed\n");
        exit(-1);
    }
    
    //4.进行通信
    while(1)
    {
        char buf[100] = {0};
        struct sockaddr_in fromaddr;
        unsigned int len = sizeof(fromaddr);
        printf("udpServer len===========%d\n", len);
        //recvfrom是拥塞函数，没有数据就一直阻塞
        ssize_t recvCount = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&fromaddr, &len);
        printf("udpServer recvCount===========%ld\n", recvCount);
        printf("from client %s receive data:%s\n", inet_ntoa(fromaddr.sin_addr), buf);
        char *str = "alread receive data";
        ssize_t sendCount =  sendto(fd, str, strlen(str), 0, (struct sockaddr *)&fromaddr, sizeof(fromaddr));
        printf("udpServer sendCount===========%ld\n", sendCount);
    }
    close(fd);
    
    return 0;
}



