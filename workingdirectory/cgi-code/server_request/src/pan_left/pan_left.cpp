#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


int main(int argc, char *argv[])
{
	char  *pRequestMethod;  /* METHOD 属性值 */

    /*从stdout中输出，告诉Web服务器返回的信息类型*/
    printf("Content-type:text/html\n\n");
    /*插入一个空行，结束头部信息*/
    printf("\n");

	/* 从环境变量REQUEST_METHOD中得到METHOD属性值 */
	pRequestMethod = getenv("REQUEST_METHOD");
	if(pRequestMethod == NULL)
	{
		//返回错误信息的json数据
        char stdout_buff[BUFF_SIZE] = {0};
        request_Unavailable(stdout_buff);
        printf("%s", stdout_buff);

		return 0;
	}
    
    if(strcasecmp(pRequestMethod,"GET") == 0)
    {
        dealwith_GetRequest(DEF_PAN_LEFT_TYPE, (char*)"pan_left");
    }

    return 0;
}

