#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include "cJSON.h"
//头文件

//#define IPSTR "192.168.100.100"  //相册服务器Ip
//#define IPSTR "119.75.217.109"   //百度IP
#define PORT 80
#define BUFSIZE 1024

int main(int argc, char **argv)
{
    int sockfd, ret;
    struct sockaddr_in servaddr;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set   t_set;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
    printf("创建网络连接失败,本线程即将终止---socket error!\n");
    exit(0);
    };

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 ){
    printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
    exit(0);
    };

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
    printf("连接到服务器失败,connect error!\n");
    exit(0);
    }
    printf("与远端建立了连接\n");


    //发送数据
    memset(str2, 0, 4096);
//json格式 字符串的拼接
    strcat(str2, "content={ \n");
    strcat(str2, "\"SC\":    \"001cfe2fe7044aa691d4e6eff9bfb56c\",\n");
    strcat(str2,  "\"SV\":       \"ecec7fb2aacb4323b305bff28443ec43\",\n");
    strcat(str2,  "\"DeviceID\":  \"1609190000000011\",\n");
    strcat(str2,   "\"Token\":     \"5588bc46-f96b-48a5-9b6e-05c7843480f0\",\n");
    strcat(str2,   "}\n"); 
    printf("length=%d\n",strlen(str2)); 
    printf("%s\n",str2);


    str=(char *)malloc(4096);
    len = strlen(str2);
    sprintf(str, "%d", len);

    memset(str1, 0, 4096);
    //strcat(str1, "POST https://www.baidu.com/  HTTP/1.1\n");  百度IP
    strcat(str1, "POST http://api.chengzhangrj.com/api/2008009/Get_Album_Pics?App=album HTTP/1.1\n"); //相册获取照片地址
    strcat(str1, "Content-Type: application/x-www-form-urlencoded\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");

    strcat(str1, str2);
    strcat(str1, "\r\n\r\n");
   // printf("%s\n",str1);

    ret = write(sockfd,str1,strlen(str1));
    if (ret < 0) {
    printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
    exit(0);
    }else{
    printf("消息发送成功，共发送了%d个字节！\n\n", ret);
    printf("%s\n",str1);
    }

    FD_ZERO(&t_set);
    FD_SET(sockfd, &t_set);


    close(sockfd);


    return 0;
}
