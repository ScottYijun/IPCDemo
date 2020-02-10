//
//  tcpClient_select.c
//  client
//
//  Created by chenyijun on 2020/2/10.
//  Copyright © 2020 chenyijun. All rights reserved.
//

#include "wrap.h"

#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 6666

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n;
    //if(argc != 2)
    //    printf("./Client IP\n");
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    inet_pton(AF_INET, "192.168.1.102", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);
    
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("==========================connect ok=======================\n");
    
    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        Write(sockfd, buf, strlen(buf));
        n = Read(sockfd, buf, MAXLINE);
        
        if(n == 0)
        {
            printf("the other side has been closed.\n");
            break;
        }
        else
        {
            Write(STDOUT_FILENO, buf, n);
        }
    }
    
    Close(sockfd);
    return 0;
}





