#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


int main(int argc, char *argv[])
{
	int   data_len;   /* 数据长度 */
	int   read_len = 0;
	char  *penv_str;
	char  *pRequestMethod;  /* METHOD 属性值 */
    char stdin_buff[BUFF_SIZE] = {0};

    /*从stdout中输出，告诉Web服务器返回的信息类型*/
    printf("Content-type:text/html\n\n");
    /*插入一个空行，结束头部信息*/
    //printf("\n");

#ifdef DEBUG
    strcpy(stdin_buff, "{\"active\" : \"login\",\"loginfo\":[{\"user\": \"admin\",\"passWord\": \"sshw1234\",\"Ip\": \"192.168.31.173\",\"port\": \"8000\"}]}");
    dealwith_request(stdin_buff, strlen(stdin_buff)i, DEF_LOGIN_TYPE);
#endif
/****************************************/
	/* 从环境变量REQUEST_METHOD中得到METHOD属性值 */
	pRequestMethod = getenv("REQUEST_METHOD");
	if(pRequestMethod == NULL)
	{
		//返回错误信息的json数据
		return 0;
	}
	if(strcasecmp(pRequestMethod,"POST") == 0){
		//从环境变量CONTENT_LENGTH中得到数据长度    
		penv_str = getenv("CONTENT_LENGTH");
		if (penv_str != NULL){
			data_len = atoi(penv_str);
		}
		else{
			data_len = 0;
		}

		read_len = fread(stdin_buff, 1, data_len, stdin);
		if (read_len != data_len){
			return -1;
		}

        dealwith_request(stdin_buff, read_len, DEF_LOGIN_TYPE);
	}
    else if(strcasecmp(pRequestMethod,"GET") == 0){
		//从环境变量QUERY_STRING中得到Form数据    
		penv_str = getenv("QUERY_STRING"); 
		if(penv_str != NULL){
			strncpy(stdin_buff, penv_str, sizeof(stdin_buff));
            dealwith_request(stdin_buff, read_len, DEF_LOGIN_TYPE);
		}
    }

    return 0;
}

