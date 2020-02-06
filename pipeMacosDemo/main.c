#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <wait.h>
#include <sys/types.h>


int main()
{
    int pipefd[2]; //定义一个大小为2的一个int类型的数组指针（两个文件描述符）
    int result;
    char buf[1024];
    int flag = 0;
    pid_t pid;
    result = pipe(pipefd);//创建一个管道
    if(result == -1)
    {
        perror("pipe create error======\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("pipe create success\n");
    }

    pid = fork();//创建一个子进程
    printf("pid===========%d\n", pid);
    if(pid == -1)// 创建进程失败
    {
        printf("fork error===========\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        //fd[0]:读取管道 fd[1]写入管道
        if((close(pipefd[1])) == -1)  //关闭写管道，只读管道
        {
            printf("close write pipe error=======\n");
            exit(EXIT_FAILURE);
        }
        while(1) // 循环读取数据
        {
            read(pipefd[0], buf, 1024); //最多读取1024个字节
            printf("read from pipe: %s\n", buf);
            //如果读取到的字符串是exit，这是父进程会接收到一人终止进程的信号，
            //父进程会回收子进程的资源
            if(strcmp(buf, "exit") == 0)
            {
                printf("0 exit()====pid=====%d\n", pid);
                exit(EXIT_SUCCESS);
            }
        }
    }
    else {
        //关闭读管道，
        if((close(pipefd[0])) == -1)
        {
            printf("close read pipe error======\n");
            exit(EXIT_FAILURE);
        }
        while(1) // 循环写入内容
        {
            //printf("waitpid()====pid=====%d\n", pid);
            //waitpid(pid, NULL, WNOHANG); //等待子进程退出
            if(flag == 1)
                exit(0);
            printf("write data: \n");
            scanf("%s", buf);
            write(pipefd[1], buf, strlen(buf) + 1); //具体写多少个字节
            if(strcmp(buf, "exit") == 0)
            {
                printf("1 exit()====pid=====%d\n", pid);
                flag = 1;
                sleep(1); //让子进程完全退出
            }
        }
    }

    printf("Hello World!\n");
    return 0;
}



//https://blog.csdn.net/ta893115871/article/details/7478779
