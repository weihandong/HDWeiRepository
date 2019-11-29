#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>


#define FIFO_NAME ("/tmp/servehandlerfifo") // 设定FIFO的名字
#define MAXLINE (1024)

char *itoa_my(int value, char *string, int radix)
{
    char zm[37]="0123456789abcdefghijklmnopqrstuvwxyz";
    char aa[100]={0};

    int sum=value;
    char *cp=string;
    int i=0;

    if(radix<2 || radix>36)//增加了对错误的检测
    {
        return string;
    }

    if(value < 0)
    {
        return string;
    }

    while(sum > 0)
    {
        aa[i++]=zm[sum%radix];
        sum/=radix;
    }

    for(int j=i-1; j>=0; j--)
    {
        *cp++=aa[j];
    }
    *cp='\0';

    return string;
}



int main(int argc, char *argv[])
{
    int pipefd;
    char writebuff[MAXLINE];
    char readbuff[MAXLINE];
    size_t writelen = 0;
    int readlen = 0;
    size_t commdlen = 0;
    int command = -1;

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
        printf("请输入命令:");
        commdlen = scanf("%d",&command);
        if(command < 0 || command > 128)
        {
            printf("命令无效,请重新输入:\r\n");
        }else{
            // 写入执行状态
            itoa_my(command, writebuff, 10);
            printf("afsd:%s\r\n",writebuff);
            writelen = write(pipefd, writebuff, strlen(writebuff));
            if(writelen < 0)
            {
                perror("写入FIFO失败");
                exit(1);
            }

            readlen = read(pipefd, readbuff, MAXLINE);
            if(strcmp("successed",readbuff) == 0)
                printf("命令执行完成\r\n");
            else
                printf("命令执行失败\r\n");
        }
    }

    if(-1 == close(pipefd))
    {
        perror("关闭FIFO失败");
        unlink(FIFO_NAME);
        exit(1);
    }

    return 0;
}

