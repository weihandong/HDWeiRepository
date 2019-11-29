#include "stdlib.h"
#include <sys/types.h>
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "string.h"
#include "arpa/inet.h"
#include <ctype.h>
#include "stdio.h"
#include <sys/stat.h>
#include "fcntl.h"


void send_and_recv(int sockfd, char * url, char * fun_type, char * accept_type, char * ip, int port, char * file_loc, char * body, char * connection_type);
//sockfd表示TCP链接的套接字，url请求服务的相对或者绝对地址，fun_type请求方法，accept_type接受类 型，ip,port请求的服务器的地址和端口，file_loc下载文件存放位置，body请求的主体，connection_type用来指定 connection的类型

int main(int argc, char *argv[]) 
{
        int sockfd;
        struct sockaddr_in serv_socket;
        int port = 80;
        char ip[] = "14.215.177.39"; //ip地址，可以通过gethostbyname来获取
        char file_loc[] = "/home/hdwei/WorkData/LHT-ROBOT/webserver/www/http/temp.html"; //下载的存放位置

        bzero(&serv_socket, sizeof(struct sockaddr_in));
        serv_socket.sin_family = AF_INET;
        serv_socket.sin_port = htons(port);
        inet_pton(AF_INET, ip, &serv_socket.sin_addr);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);       
        int flag = connect(sockfd, (struct sockaddr *)&serv_socket, sizeof(serv_socket)); //建立和HTTP服务器的TCP链接
        if(flag < 0) {
                printf("connect error!!! flag = %d\n", flag);
                exit(1);
        }

        send_and_recv(sockfd, "http://www.baidu.com/", "GET", "html/text", ip, port, file_loc, NULL, "Close"); //下载的主体函数
        close(sockfd);
        exit(0);
}

void send_and_recv(int sockfd, char * url, char * fun_type, char * accept_type, char * ip, int port, char * file_loc, char * body, char * connection_type) 
{
        char *request = (char*) malloc (4*1024*sizeof(char));
        if(body)
                sprintf(request, "%s %s HTTP/1.1\r\nAccept: %s\r\nHost: %s:%d\r\nConnection: %s\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-L \
ength: %d\r\n\r\n%s", fun_type, url, accept_type, ip, port, connection_type, body, strlen(body));
        else
                sprintf(request, "%s %s HTTP/1.1\r\nAccept: %s\r\nHost: %s:%d\r\nConnection: %s\r\n\r\n", fun_type, url, accept_type, ip, port, connection_type
);
//以上是在组织请求的头部，打印出的结果就是文章开头所写

        int send = write(sockfd, request, strlen(request));
        printf("%s", request);
        free(request);

	int file = -1;
        char * response = (char *) malloc (1024 * sizeof(char));
        if(file_loc) {
                if(-1 == (file=open(file_loc, O_RDWR|O_CREAT|O_APPEND)))
                {
                	int length;
                	do { 
                        	length = read(sockfd, response, 1024);
	                        printf("%s", response);
         	               if(!length)
                	                break;
	                } while(1);
			
		}
                int length;

                do {
                        length = read(sockfd, response, 1024);
                        char * loc = strstr(response, "\r\n\r\n"); //截获返回头部，以\r\n\r\n为标识
                        if(loc) {
                                int loci = loc - response + 4;
                                write(1, response, loci);        //如果是响应头部就打印至屏幕
                                write(file, loc, length - loci); //如果是响应主体就写入文件
                        } else {
                                write(file, response, length);
                        }
                        if(!length)//注意，因为之前采用的是close方法，也就是说一旦传输数据完毕，则服务器端会断开链接，则read函数会返回0，所以这里 会退出循环。如果采用的是Keep-Alive则服务器不关闭TCP链接，也就说程序将会被阻塞在read函数中，因此要注意的是自己判断是否读到了响应的结尾，然后在再次调用read之前退出循环。
                                break;
                } while(1);
                close(file);

        } else {
                int length;
                do { 
                        length = read(sockfd, response, 1024);
                        printf("%s", response);
                        if(!length)
                                break;
                } while(1);
        }
        free(response);
}
