#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>   
#include <sys/msg.h>
#include "common.h"
#include "cJSON.h"

#include <iostream>
using namespace std;


extern char stdout_buff[BUFF_SIZE];

static int cJSON_Parse(char *json_string, speed_config_t *speedcfg)
{
	cJSON *root, *item;

	root = cJSON_Parse(json_string);
	if (!root)
	{
#ifdef DEBUG
		cout << "cjon parse root error: " << cJSON_GetErrorPtr() << endl;
#endif
		return -1;
	}
	else
	{
		item = cJSON_GetObjectItem(root,"action");	
		if(item != NULL)
		{
			memcpy(speedcfg->action, item->valuestring,strlen(item->valuestring));
            item = NULL;
		}

		item = cJSON_GetObjectItem(root,"deviceId");	
		if(item != NULL)
		{
            speedcfg->deviceId = item->valueint;
            item = NULL;
		}

		item = cJSON_GetObjectItem(root,"speed");	
		if(item != NULL)
		{
            speedcfg->speedvalue = item->valueint;
            item = NULL;
		}		
    }
	
	return 0;
}



void dealwith_SpeedRequest(char *input, int str_len, int msg_type)
{
    msg_queue_t msg = {0};
    speed_config_t speedcfg = {0};
    rsp_msgqueue_t rsp_msg = {0};

    if(input == NULL || str_len <= 0)
        return ;

    if(0 != cJSON_Parse(input, &speedcfg))
        return ;
#ifdef DEBUG
    cout << "action:" << speedcfg.action << endl;
    cout << "deviceId:" << speedcfg.deviceId << endl;
    cout << "speedvalue:" << speedcfg.speedvalue << endl;
#endif
    msg.msg_type = msg_type;
    memcpy(msg.msg_content, (char*)&speedcfg, sizeof(speedcfg));

    if(0 > mqueue_Send((char*)&msg, sizeof(msg_queue_t))){
        return ;
    }
    
    if(0 > mqueue_Recv((char*)&rsp_msg, sizeof(rsp_msgqueue_t))){
        return ;
    }

    struct_ResponseJson(stdout_buff, rsp_msg.msg_result);
    cout << stdout_buff << endl;
}



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
    printf("\n");

    //char *json = "{\"action\":\"set\",\"deviceId\": 1,\"speed\":3}";

    //dealwith_SpeedRequest(json, strlen(json), DEF_SET_SPEED_TYPE);

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

	if(strcasecmp(pRequestMethod,"POST") == 0){
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

        dealwith_SpeedRequest(stdin_buff, read_len, DEF_SET_SPEED_TYPE);
	}

    return 0;
}

