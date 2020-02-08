//
//  udpClient.c
//  client
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
        printf("udp client socket failed\n");
        exit(-1);
    }
    else
    {
        printf("udp client socket success\n");
    }
    
    //2.准备地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton("192.168.1.102", &addr.sin_addr);
    //3.进行通信
    char *str = "udp client data222";
    ssize_t sendCount =  sendto(fd, str, strlen(str), 0, (struct sockaddr *)&addr, sizeof(addr));
    printf("udpClient sendCount===========%ld\n", sendCount);
    char buf[100] = {0};
    unsigned int len = sizeof(addr);
    //recvfrom是拥塞函数，没有数据就一直阻塞
    ssize_t recvCount = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &len);
    printf("udpClient recvCount===========%ld\n", recvCount);
    printf("sever say: %s\n", buf);
    close(fd);
    
    return 0;
}






