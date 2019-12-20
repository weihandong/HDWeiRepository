#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
/******************************** 响应客户端数据请求 *************************************/

static int struct_Response_cJSON(char *json_context, response_nopayload_t *response)
{
	char *json_string = NULL;
	cJSON *json, *item;

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
		cJSON *array_sensors = cJSON_CreateArray();
		
		item = cJSON_CreateNumber(response->code);
		cJSON_AddItemToObject(root,"code",item);	
	
		cJSON *item = cJSON_CreateString(response->message);
		cJSON_AddItemToObject(root,"message",item);	
		
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

int struct_Array_To_cJSON(char *json_context, sensors_data_t arraydata)
{
	char *json_string = NULL;
	cJSON *json, *arrayItem, *item, *object;

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
		cJSON *array_sensors = cJSON_CreateArray();
		
		item = cJSON_CreateNumber(200);
		cJSON_AddItemToObject(root,"code",item);	
	
		cJSON *item = cJSON_CreateString("success");
		cJSON_AddItemToObject(root,"message",item);	
		
		
		cJSON *obj_sensors = cJSON_CreateObject();
		//温度
		item=cJSON_CreateNumber(arraydata.temperature);
		cJSON_AddItemToObject(obj_sensors,"temperature",item);
		//湿度
		item=cJSON_CreateNumber(arraydata.humidity);
		cJSON_AddItemToObject(obj_sensors,"humidity",item);
		//噪声
		item=cJSON_CreateNumber(arraydata.noise);
		cJSON_AddItemToObject(obj_sensors,"noise",item);
		
		cJSON_AddItemToArray(array_sensors,obj_sensors);
		cJSON_AddItemToObject(root,"data",array_sensors);

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

/******************************** 响应客户端结果请求 *************************************/
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

/********************************** 解析客户端请求 *********************************************/
//parse a object to struct
static int cJSON_To_Struct(char *json_string, loginfo_t *loginfo)
{
	cJSON *root, *arrayItem, *item, *object;

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
		cJSON *item = cJSON_GetObjectItem(root,"active");	
		if(item != NULL)
		{
			//memcpy(loginfo->active, item->valuestring,strlen(item->valuestring));
		}		
	
		arrayItem = cJSON_GetObjectItem(root,"loginfo");
		if(arrayItem != NULL)
		{
			int size = cJSON_GetArraySize(arrayItem);
			for(int i=0; i<size; i++)
			{
				object = cJSON_GetArrayItem(arrayItem,i);
				
				item = cJSON_GetObjectItem(object,"user");
				if(item != NULL)
				{
					memcpy(loginfo->username, item->valuestring,strlen(item->valuestring));
				}

				item = cJSON_GetObjectItem(object,"passWord");
				if(item != NULL)
				{
					memcpy(loginfo->password, item->valuestring,strlen(item->valuestring));
				}
				
				item = cJSON_GetObjectItem(object,"Ip");
				if(item != NULL)
				{
					memcpy(loginfo->ipaddress, item->valuestring,strlen(item->valuestring));
				}

				item = cJSON_GetObjectItem(object,"port");
				if(item != NULL)
				{
					memcpy(loginfo->portno, item->valuestring,strlen(item->valuestring));
				}				
			}
		}

		cJSON_Delete(root);
	}

	return 0;
}

/************************  message queue  *****************************/

static int msg_recv(rsp_msgqueue_t *rsp_msgs)
{
    int msgid;
    int read_len;
    int ret_value;

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

    read_len = msgrcv(msgid, rsp_msgs, sizeof(rsp_msgqueue_t), 0, 0);
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

static int msg_send(msg_queue_t *msg)
{
    int msgid;
    int read_len;
    int ret_value;

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

    ret_value = msgsnd(msgid, msg, sizeof(msg_queue_t), IPC_NOWAIT);
    if(ret_value < 0)
    {
#ifdef DEBUG
        perror("write pipe error:");
#else
        cout << "errno= " << errno << "==>" << strerror(errno) << endl;
#endif
        return -2;
    }
#ifdef DEBUG
    loginfo_t *loginfo = (loginfo_t*)msg->msg_content;
    cout << "type:" << msg->msg_type << endl;
    cout << "username:" << loginfo->username << endl;
    cout << "password:" << loginfo->password << endl;
    cout << "ipaddress:" << loginfo->ipaddress << endl;
    cout << "portno:" << loginfo->portno << endl; 
#endif

    return ret_value;
}

static int msg_send(loginfo_msgqueue_t *loginf_msg)
{
    int msgid;
    int read_len;
    int ret_value;

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

    ret_value = msgsnd(msgid, loginf_msg, sizeof(loginfo_msgqueue_t), IPC_NOWAIT);
    if(ret_value < 0)
    {
#ifdef DEBUG
        perror("write pipe error:");
#else
        cout << "errno= " << errno << "==>" << strerror(errno) << endl;
#endif
        return -2;
    }
#ifdef DEBUG
    cout << "username:" << loginf_msg->msg_loginfo.username << endl;
    cout << "password:" << loginf_msg->msg_loginfo.password << endl;
    cout << "ipaddress:" << loginf_msg->msg_loginfo.ipaddress << endl;
    cout << "portno:" << loginf_msg->msg_loginfo.portno << endl;
#endif

    return ret_value;
}


/********************************  具体译码和处理数据  ************************************/
static int DecodeAndProcessData(char *input, int data_len, int msg_type)
{
    //loginfo_msgqueue_t loginfo_msgs;
    msg_queue_t msg = {0};
    loginfo_t loginfo = {0};

    if(input == NULL || data_len <= 0)
        return -1;

    if(0 != cJSON_To_Struct(input, &loginfo))
        return -1;
#ifdef DEBUG
    int fd = 0;
    fd = open("./aa.txt",O_WRONLY|O_CREAT,0777);
	write(fd,input, data_len);
    close(fd);

    cout << "username:" << loginfo.username << endl;
    cout << "password:" << loginfo.password << endl;
    cout << "ipaddress:" << loginfo.ipaddress << endl;
    cout << "portno:" << loginfo.portno << endl;
#endif
    //loginfo_msgs.msg_loginfo = loginfo;
    msg.msg_type = msg_type;
    memcpy(msg.msg_content, (char*)&loginfo, sizeof(loginfo));

    //if(0 > msg_send(&loginfo_msgs)){
    if(0 > msg_send(&msg)){
        return -2;
    }

	return 0;
}


void dealwith_request(char *json_str, int str_len, int msg_type)
{
    rsp_msgqueue_t rsp_msgs = {0};

    if(0 != DecodeAndProcessData(json_str, str_len, msg_type)){
        return ;
    }
    
    if(0 > msg_recv(&rsp_msgs)){
        return ;
    }

    struct_Response_cJSON(stdout_buff, &rsp_msgs.msg_response);
    cout << stdout_buff << endl;
}

