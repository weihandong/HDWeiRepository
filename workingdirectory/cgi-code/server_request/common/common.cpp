#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>   
#include <sys/msg.h>
#include "cJSON.h"
#include "common.h"

using namespace std;


char stdout_buff[BUFF_SIZE];
/******************************** 响应客户端结果请求 **********************************/

/*
 *
 */
static int create_Response_cJSON(char *json_context, int code, char *message)
{
	char *json_string = NULL;
	cJSON *root = cJSON_CreateObject();
	
	if (!root)
	{
#ifdef DEBUG
		cout << "cjon structure error: " << cJSON_GetErrorPtr() << endl;
#endif
		return -1;	
	}
	else
	{
		cJSON *item = cJSON_CreateNumber(code);
		cJSON_AddItemToObject(root,"code",item);	
	
        item = NULL;
		item = cJSON_CreateString(message);
		cJSON_AddItemToObject(root,"message",item);		
		
 		json_string = cJSON_Print(root);
 		cJSON_Delete(root);
		
		if(json_string != NULL)
		{
			memcpy(json_context,json_string,strlen(json_string));
			free(json_string);
			json_string = NULL;
		}
	}

	return 0;
}

//请求成功
void request_Successed(char *json_string)
{
	create_Response_cJSON(json_string, 200, (char*)"OK");
    cout << json_string << endl;
}
//请求语法错误
void request_Bad(char *json_string)
{
	create_Response_cJSON(json_string, 400, (char*)"Bad Request");
    cout << json_string << endl;
}

//拒绝提供服务
void request_Unauthorized(char *json_string)
{
	create_Response_cJSON(json_string, 401, (char*)"Unauthorized");
    cout << json_string << endl;
}

//请求资源不存在
void request_NoResources(char *json_string)
{
	create_Response_cJSON(json_string, 404, (char*)"Not Found");
    cout << json_string << endl;
}

//服务器发生不可预期的错误
void request_ServerError(char *json_string)
{
	create_Response_cJSON(json_string, 500, (char*)"Internal Server Error");
    cout << json_string << endl;
}

//服务器当前不能处理客户端的请求
void request_Unavailable(char *json_string)
{
	create_Response_cJSON(json_string, 503, (char*)"Server Unavailable");
    cout << json_string << endl;
}

/************************  message queue  *****************************/

/*
 *
 */
int mqueue_Send(char *data, int len)
{
    int msgid;
    int ret_value;

    if(data == NULL || len <= 0)
        return 0;

    msgid = msgget(SED_MSGKEY, IPC_EXCL);/*检查消息队列是否存在 */ 
    if(msgid < 0)
    {
#ifdef DEBUG
        perror("====> open pipe error:");
#else
        cout << "====>" << strerror(errno) << endl;
        perror(" open pipe error:");
        request_Unavailable(stdout_buff);
#endif
        return -1;
    }

    ret_value = msgsnd(msgid, data, len, IPC_NOWAIT);
    if(ret_value < 0)
    {
#ifdef DEBUG
        perror("write pipe error:");
#else
        cout << "errno= " << errno << "==>" << strerror(errno) << endl;
#endif
        return -2;
    }

    return ret_value;
}

/*
 *
 */
int mqueue_Recv(char *data, int len)
{
    int msgid;
    int read_len;

    msgid = msgget(RCV_MSGKEY, IPC_EXCL);//检查消息队列是否存在
    if(msgid < 0)
    {
#ifdef DEBUG
        perror("====> open pipe error:");
#else
        cout << "====>" << strerror(errno) << endl;
        perror(" open pipe error:");
        request_Unavailable(stdout_buff);
#endif
        return -1;
    }

    read_len = msgrcv(msgid, data, len, 0, 0);
    if(-1 == read_len)
    {
#ifdef DEBUG
        perror("read pipe error:");
#else
        request_Unavailable(stdout_buff);
#endif
        return -1;
    }

    return read_len;
}

/********************************  具体译码和处理数据  ************************************/
int struct_ResponseJson(char *json_context, long result)
{
    long code = 0;
	char *json_string = NULL;

	cJSON *root = cJSON_CreateObject();
	if (!root)
	{
#ifdef DEBUG
		cout << "cjon structure error: " << cJSON_GetErrorPtr() << endl;
#endif
		return -1;
	}
	else
	{
        for(unsigned int i=0; i<ARRAY_SIZE(response_list); i++)
        {
            if(result == response_list[i].code){
                cJSON *item = NULL;
                
                code = response_list[i].code;
                item = cJSON_CreateNumber(code);
                cJSON_AddItemToObject(root,"code",item);
            
                item = NULL;
                item = cJSON_CreateString(response_list[i].message);
                cJSON_AddItemToObject(root,"message",item);	
                break;
            }
        }
		
        json_string = cJSON_Print(root);
		cJSON_Delete(root);
		if(json_string != NULL)
		{
			memcpy(json_context, json_string, strlen(json_string));
			free(json_string);
		}
    }

	return 0;
}

void dealwith_GetRequest(int msg_type, char *action)
{
    msg_queue_t msg = {0};
    rsp_msgqueue_t rsp_msgs = {0};

    msg.msg_type = msg_type;
    strcpy(msg.msg_content, action);

    if(0 > mqueue_Send((char*)&msg, sizeof(msg_queue_t))){
        return ;
    }
    
    if(0 > mqueue_Recv((char*)&rsp_msgs, sizeof(rsp_msgqueue_t))){
        return ;
    }

    struct_ResponseJson(stdout_buff, rsp_msgs.msg_result);
    cout << stdout_buff << endl;
}

/*
 *
 */
static int struct_ResponseSensor(char *json_context, long result,char* payload, char *sensorname)
{
    long code = 0;
	char *json_string = NULL;

	cJSON *root = cJSON_CreateObject();
	if (!root)
	{
#ifdef DEBUG
		cout << "cjon structure error: " << cJSON_GetErrorPtr() << endl;
#endif
		return -1;
	}
	else
	{
        cout << "result:" << result << endl;
        for(unsigned int i=0; i<ARRAY_SIZE(response_list); i++)
        {
            if(result == response_list[i].code){
                cJSON *item = NULL;
                
                code = response_list[i].code;
                item = cJSON_CreateNumber(code);
                cJSON_AddItemToObject(root,"code",item);
            
                item = NULL;
                item = cJSON_CreateString(response_list[i].message);
                cJSON_AddItemToObject(root,"message",item);	
                break;
            }
        }

        cJSON *obj = cJSON_CreateObject();
        if(obj != NULL){
		    cJSON *item = cJSON_CreateString(sensorname);
		    cJSON_AddItemToObject(obj,"name",item);	
	        item = NULL;

            int *psensorvalue = (int*)payload;
            item=cJSON_CreateNumber(*psensorvalue);
		    cJSON_AddItemToObject(obj, "value", item);	

		    cJSON_AddItemToObject(root, "sensor", obj);	
        }

        json_string = cJSON_Print(root);
		cJSON_Delete(root);
		if(json_string != NULL)
		{
			memcpy(json_context, json_string, strlen(json_string));
			free(json_string);
		}
	}

	return 0;
}


void dealwith_GetReqsensor(int msg_type, char *sensorname)
{
    char stdout_buff[BUFF_SIZE] = {0};
    rsp_msgqueue_t rsp_msgs = {0};
    msg_queue_t msg = {0};

    msg.msg_type = msg_type;
    if(0 > mqueue_Send((char*)&msg, sizeof(msg_queue_t))){
        return ;
    }

    if(0 > mqueue_Recv((char*)&rsp_msgs, sizeof(rsp_msgqueue_t))){
        return ;
    }

    struct_ResponseSensor(stdout_buff, rsp_msgs.msg_result, rsp_msgs.msg_payload, sensorname);
    cout << stdout_buff << endl;
}




