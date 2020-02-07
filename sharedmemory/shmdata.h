#ifndef SHMDATA_H
#define SHMDATA_H

#define TEXT_SZ 2048

struct SHARED_DATA_ST
{
    int written;//作为一个标志，非0：表示可读，0表示可写
    char text[TEXT_SZ];//记录写入和读取的文件
};


#endif // SHMDATA_H
