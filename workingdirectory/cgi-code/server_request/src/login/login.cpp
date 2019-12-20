#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "cJSON.h"
#include <iostream>
using namespace std;



//#define DEBUG
/********************************** 解析客户端请求 *********************************************/
/*
 *
 */
static int prase_LoginRequest(char *json_string, loginfo_t *loginfo)
{
	cJSON *root, *object;

	root = cJSON_Parse(json_string);
	if (!root){
#ifdef DEBUG
		cout << "cjon parse root error: " << cJSON_GetErrorPtr() << endl;
#endif
		return -1;
	}else{
		cJSON *item = cJSON_GetObjectItem(root,"action");	
		if(item != NULL){
			//memcpy(loginfo->active, item->valuestring,strlen(item->valuestring));
		}		
	
		object = cJSON_GetObjectItem(root,"loginfo");
		if(object != NULL){
            item = NULL;
            item = cJSON_GetObjectItem(object,"user");
            if(item != NULL){
                memcpy(loginfo->username, item->valuestring,strlen(item->valuestring));
            }

            item = NULL;
            item = cJSON_GetObjectItem(object,"passWord");
            if(item != NULL){
                memcpy(loginfo->password, item->valuestring,strlen(item->valuestring));
            }
            
            item = NULL;
            item = cJSON_GetObjectItem(object,"Ip");
            if(item != NULL){
                memcpy(loginfo->ipaddress, item->valuestring,strlen(item->valuestring));
            }

            item = NULL;
            item = cJSON_GetObjectItem(object,"port");
            if(item != NULL){
                loginfo->portno = item->valueint;
            }				
        }
		cJSON_Delete(root);
	}

	return 0;
}

/*
 *
 */
static int struct_LoginRespone(char *json_context, long result, char *payload)
{
    long code = 0;
	char *json_string = NULL;
	cJSON *item = NULL;

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
		
	    rsp_loginfo_t *rsploginfo = (rsp_loginfo_t*)payload;
        if(code == 0)
        {
            cJSON *obj_PTZ = cJSON_CreateObject();
            //用户名
            item=cJSON_CreateString(rsploginfo->loginfo_PTZ.username);
            cJSON_AddItemToObject(obj_PTZ, "UserName", item);
            item = NULL;
            //密码
            item=cJSON_CreateString(rsploginfo->loginfo_PTZ.password);
            cJSON_AddItemToObject(obj_PTZ, "PassWord", item);
            item = NULL;
            //IP地址
            item=cJSON_CreateString(rsploginfo->loginfo_PTZ.ipaddress);
            cJSON_AddItemToObject(obj_PTZ, "IpAddress", item);
            item = NULL;
            //端口号 
            item=cJSON_CreateNumber(rsploginfo->loginfo_PTZ.portno);
            cJSON_AddItemToObject(obj_PTZ, "Port", item);
            item = NULL;
            cJSON_AddItemToObject(root, "PTZ", obj_PTZ);

            cJSON *obj_TI = cJSON_CreateObject();
            //用户名
            item=cJSON_CreateString(rsploginfo->loginfo_TI.username);
            cJSON_AddItemToObject(obj_TI, "UserName", item);
            item = NULL;
            //密码
            item=cJSON_CreateString(rsploginfo->loginfo_TI.password);
            cJSON_AddItemToObject(obj_TI, "PassWord", item);
            item = NULL;
            //IP地址
            item=cJSON_CreateString(rsploginfo->loginfo_TI.ipaddress);
            cJSON_AddItemToObject(obj_TI, "IpAddress", item);
            item = NULL;
            //端口号 
            item=cJSON_CreateNumber(rsploginfo->loginfo_TI.portno);
            cJSON_AddItemToObject(obj_TI, "Port", item);
            item = NULL;
            cJSON_AddItemToObject(root,"TI", obj_TI);

            cJSON *obj_NM = cJSON_CreateObject();
            //用户名
            item=cJSON_CreateString(rsploginfo->loginfo_NM.username);
            cJSON_AddItemToObject(obj_NM, "UserName", item);
            item = NULL;
            //密码
            item=cJSON_CreateString(rsploginfo->loginfo_NM.password);
            cJSON_AddItemToObject(obj_NM, "PassWord", item);
            item = NULL;
            //IP地址
            item=cJSON_CreateString(rsploginfo->loginfo_NM.ipaddress);
            cJSON_AddItemToObject(obj_NM, "IpAddress", item);
            item = NULL;
            //端口号 
            item=cJSON_CreateNumber(rsploginfo->loginfo_NM.portno);
            cJSON_AddItemToObject(obj_NM, "Port", item);
            item = NULL;
            cJSON_AddItemToObject(root,"NM", obj_NM);
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

/*
 *
 */
static int decode_ProcessLogin(char *input, int data_len, int msg_type)
{
    msg_queue_t msg = {0};
    loginfo_t loginfo = {0};

    if(input == NULL || data_len <= 0)
        return -1;

    if(0 != prase_LoginRequest(input, &loginfo))
        return -1;
#ifdef DdEBUG
    int fd = 0;
    fd = open("./aa.txt",O_WRONLY|O_CREAT,0777);
	write(fd,input, data_len);
    close(fd);

    cout << "username:" << loginfo.username << endl;
    cout << "password:" << loginfo.password << endl;
    cout << "ipaddress:" << loginfo.ipaddress << endl;
    cout << "portno:" << loginfo.portno << endl;
#endif
    msg.msg_type = msg_type;
    memcpy(msg.msg_content, (char*)&loginfo, sizeof(loginfo));

    if(0 > mqueue_Send((char*)&msg, sizeof(msg_queue_t))){
        return -2;
    }

	return 0;
}

/*
 *
 */
void dealwith_LoginRequest(char *json_str, int str_len, int msg_type)
{
    char stdout_buff[BUFF_SIZE];
    rsp_msgqueue_t rsp_msgs = {0};

    if(0 != decode_ProcessLogin(json_str, str_len, msg_type)){
        return ;
    }
    
    if(0 > mqueue_Recv((char*)&rsp_msgs, sizeof(rsp_msgqueue_t))){
        return ;
    }

    struct_LoginRespone(stdout_buff, rsp_msgs.msg_result, rsp_msgs.msg_payload);
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

#ifdef DEBUG
    strcpy(stdin_buff, "{\"action\" : \"login\",\"loginfo\":{\"user\": \"admin\",\"passWord\": \"sshw1234\",\"Ip\": \"192.168.31.73\",\"port\": 8000}}");
    dealwith_LoginRequest(stdin_buff, strlen(stdin_buff), DEF_LOGIN_TYPE);
#endif
/****************************************/
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
        dealwith_LoginRequest(stdin_buff, read_len, DEF_LOGIN_TYPE);
	}
    else if(strcasecmp(pRequestMethod,"GET") == 0){
		//从环境变量QUERY_STRING中得到Form数据    
		penv_str = getenv("QUERY_STRING"); 
		if(penv_str != NULL){
			strncpy(stdin_buff, penv_str, sizeof(stdin_buff));
            dealwith_LoginRequest(stdin_buff, read_len, DEF_LOGIN_TYPE);
		}
    }

    return 0;
}

