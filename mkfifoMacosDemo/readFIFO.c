#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "myfifo"
#define BUFF_SIZE 1024

int main()
{
    char buff[BUFF_SIZE];
    int nread = 0;
    int fd;
    //access确定文件或文件夹的访问权限，即检查某个文件的存取方式
    //如果指定的存取方式有效，则函数返回0，否则函数返回-1，若不存在FIFO，则创建一个
    if(access(FIFO, F_OK) == -1)
    {
        if((mkfifo(FIFO, 0666) < 0) && (errno != EEXIST))
        {
            printf("Can not create fifo file!\n");
            exit(1);
        }
    }
    //以只读方式打开FIFO,返回文件描述符fd
    if((fd = open(FIFO, O_RDONLY)) == -1)
    {
        printf("Open fifo error!\n");
        exit(1);
    }
    // 调用read将fd指向的FIFO的内容，读到buff中，并打印
    while(1)
    {
        memset(buff, 0, BUFF_SIZE);
        if((nread = read(fd, buff, BUFF_SIZE)) > 0)
        {
            printf("Read from pipe: '%s'.\n", buff);
        }
    }
    close(fd);
    printf("Hello World!\n");
    return 0;
}


//read is server
//一个服务端可以对多个客户端
//
