#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "servereq.h"

/********** fifo ***********/ 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_NAME ("/tmp/servehandlerfifo")                 // 设定FIFO的名字
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)   // 设定创建FIFO的权限
#define BUFF_SIZE (1024)

extern bool do_reqs(const int reqno);
void do_req1(void *data);
void do_req2(void *data);


int main(int argc, char *argv[])
{
    int reqno = -1;
    int pipefd = -1;
    char readbuff[BUFF_SIZE];
    char writebuff[BUFF_SIZE];
    int readlen = 0;
    int writelen = 0;

    // 创建FIFO
    if(mkfifo(FIFO_NAME, FILE_MODE) < 0)
    {
        if(EEXIST == errno)
        {
            printf("FIFO：%s已经存在，不能重新创建\r\n", FIFO_NAME);
        }else{
            perror("create FIFO error");
            exit(1);
        }
    }

    request_initial();
    addto_reqitem("req1",do_req1, "hello world. I am req1");
    addto_reqitem("req2",do_req2, "hello world. I am req2");
    addto_reqitem("req3",do_req2, "hello world. I am req3");
    addto_reqitem("req4",do_req2, "hello world. I am req4");
    addto_reqitem("req5",do_req2, "hello world. I am req5");
    addto_reqitem("req6",do_req2, "hello world. I am req6");
    addto_reqitem("req7",do_req2, "hello world. I am req7");
    // 打开FIFO
    pipefd = open(FIFO_NAME, O_RDWR, 0);
    if(-1 == pipefd)
    {
        perror("打开FIFO失败");
        unlink(FIFO_NAME);
        exit(1);
    }
    
    while(1)
    {
        readlen = 0;
        writelen = 0;
        memset(readbuff, 0, BUFF_SIZE);
        memset(writebuff, 0, BUFF_SIZE);

        // 读取FIFO
        readlen = read(pipefd, readbuff, BUFF_SIZE);
        if(-1 == readlen)
        {
            printf("管道读取失败，退出\r\n");
            exit(1);
        }
        int command = atoi(readbuff);
        printf("管道接收数据长度:%d,内容：%d \r\n",readlen, command);

        if(!do_reqs(command))
        {
            memcpy(writebuff,"successed",sizeof("successed"));
            printf("执行失败，没有这个指令功能\r\n");
        }else{
            memcpy(writebuff,"falied",sizeof("failed"));
        }
        write(pipefd, write, strlen(writebuff));
    }

    // 关闭FIFO
    if(-1 == close(pipefd))
    {
        perror("关闭FIFO失败");
        unlink(FIFO_NAME);
         exit(1);
    }

    // 删除FIFO
    unlink(FIFO_NAME);

    return 0;
}

void do_req1(void *data)
{
    char *pdata = (char*)data;
    printf("req1 data: %s\r\n",pdata);
}

void do_req2(void *data)
{
    char *pdata = (char*)data;
    printf("data: %s\r\n",pdata);
}
