#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include "cJSON.h"

using namespace std;

//#define DEBUG

#define MODE_MAX_LEN    	10
#define USERNAME_MAX_LEN    20
#define PASSWORD_MAX_LEN    45
#define IPADDRESS_MAX_LEN   16
#define PORTNO_MAX_LEN      6

typedef struct {
	char active[MODE_MAX_LEN];
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char ipaddress[IPADDRESS_MAX_LEN];
    char portno[PORTNO_MAX_LEN];
}loginfo_t;


typedef struct{
	int	temperature;
	int	humidity;
	int	noise;
}sensors_data_t;

/******************************** 响应客户端数据请求 *************************************/

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
static void request_Successed(char *json_string)
{
	create_Response_cJSON(json_string, 200, (char*)"OK");
    cout << json_string << endl;
}
//请求语法错误
static void request_Bad(char *json_string)
{
	create_Response_cJSON(json_string, 400, (char*)"Bad Request");
    cout << json_string << endl;
}

//拒绝提供服务
static void request_Unauthorized(char *json_string)
{
	create_Response_cJSON(json_string, 401, (char*)"Unauthorized");
    cout << json_string << endl;
}

//请求资源不存在
static void request_NoResources(char *json_string)
{
	create_Response_cJSON(json_string, 404, (char*)"Not Found");
    cout << json_string << endl;
}
//服务器发生不可预期的错误
static void request_ServerError(char *json_string)
{
	create_Response_cJSON(json_string, 500, (char*)"Internal Server Error");
    cout << json_string << endl;
}
//服务器当前不能处理客户端的请求
static void request_Unavailable(char *json_string)
{
	create_Response_cJSON(json_string, 503, (char*)"Server Unavailable");
    cout << json_string << endl;
}

/********************************** 解析客户端请求 *********************************************/
//parse a object to struct
int cJSON_To_Struct(char *json_string, loginfo_t *loginfo)
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
			memcpy(loginfo->active, item->valuestring,strlen(item->valuestring));
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

/****************************************/
#define FIFO_NAME ("/tmp/servehandlerfifo") // 设定FIFO的名字
#define MAXLINE (4096)
/****************************************/
#define BUFF_SIZE   4096

char stdin_buff[BUFF_SIZE];
char stdout_buff[BUFF_SIZE];

int DecodeAndProcessData(int pipefd, char *input, int data_len);    /*具体译码和处理数据，该函数代码略*/



int main(int argc, char *argv[])
{
    int   pipefd;
	int   data_len;   /* 数据长度 */
	int   read_len = 0;
	char  *pdata_len;
	char  *pRequestMethod;  /* METHOD 属性值 */

    printf("Content-type:text/html\n\n");     /*从stdout中输出，告诉Web服务器返回的信息类型*/
    printf("\n");                             /*插入一个空行，结束头部信息*/
/****************************************/

    // 打开FIFO
    pipefd = open(FIFO_NAME, O_RDWR, 0777);
    if(-1 == pipefd)
    {
#ifdef DEBUG
        perror("====> open pipe error:");
#else
        cout << "====>" << strerror(errno) << endl;
        perror(" open pipe error:");
        request_Unavailable(stdout_buff);
#endif
        exit(1);
    }

#ifdef DEBUG
    strcpy(stdin_buff, "{\"active\" : \"login\",\"loginfo\":[{\"user\": \"admin\",\"passWord\": \"sshw1234\",\"Ip\": \"192.168.31.173\",\"port\": \"8000\"}]}");
    	if(0 != DecodeAndProcessData(pipefd, stdin_buff, strlen(stdin_buff)))
            return -1;

        //读取处理返回
        memset(stdout_buff, 0 , BUFF_SIZE);
        read_len = read(pipefd, stdout_buff, BUFF_SIZE);
        if(-1 == read_len)
        {
#ifdef DEBUG
            perror("read pipe error:");
#else
            cout << "read pipe error" << endl;
            request_Unavailable(stdout_buff);
#endif
        }
        cout << stdout_buff << endl;
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
		pdata_len = getenv("CONTENT_LENGTH");     //从环境变量CONTENT_LENGTH中得到数据长度    
		if (pdata_len != NULL){
			data_len = atoi(pdata_len);
		}
		else{
			data_len = 0;
		}

		read_len = fread(stdin_buff, 1, data_len, stdin);
		if (read_len != data_len){
			return -1;
		}
		//具体译码和处理数据
    	if(0 != DecodeAndProcessData(pipefd, stdin_buff, read_len))
        {
            cout << "DecodeAndProcessData" << endl;
            request_Unavailable(stdout_buff);
            return -1;
        }
        //读取处理返回
        memset(stdout_buff, 0 , BUFF_SIZE);
        read_len = read(pipefd, stdout_buff, BUFF_SIZE);
        if(-1 == read_len)
        {
#ifdef DEBUG
            perror("read pipe error:");
#else
            request_Unavailable(stdout_buff);
#endif
        }
        cout << stdout_buff << endl;
	}
    else if (strcasecmp(pRequestMethod,"GET") == 0){
		pdata_len = getenv("QUERY_STRING");//从环境变量QUERY_STRING中得到Form数据    
		if(pdata_len != NULL){
			strncpy(stdin_buff, pdata_len, sizeof(stdin_buff));
			DecodeAndProcessData(pipefd, stdin_buff, atoi(pdata_len));    //具体译码和处理数据，该函数代码略 
		}
    }

    return   0;
}

 
int DecodeAndProcessData(int pipefd, char *input, int data_len)//具体译码和处理数据
{
	// 补充具体操;
    int pipe_writelen = 0;
    loginfo_t loginfo = {0};

    if(pipefd <= 0 || input == NULL || data_len <= 0)
        return -1;

   if(0 != cJSON_To_Struct(input, &loginfo))
        return -1;
#ifdef DEBUG
    int fd = 0;
    fd = open("./aa.txt",O_WRONLY|O_CREAT,0777);
	write(fd,stdin_buff, data_len);
    close(fd);

    cout << "active:" << loginfo.active << endl;
    cout << "username:" << loginfo.username << endl;
    cout << "password:" << loginfo.password << endl;
    cout << "ipaddress:" << loginfo.ipaddress << endl;
    cout << "portno:" << loginfo.portno << endl;
#endif
    pipe_writelen = write(pipefd, &loginfo, sizeof(loginfo));
    if(pipe_writelen < 0)
    {
#ifdef DEBUG
        perror("write pipe error:");
#endif
        return -2;
    }

	return 0;
}

 

