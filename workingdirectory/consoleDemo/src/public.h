/*
 * Copyright(C) 2010,Hikvision Digital Technology Co., Ltd 
 * 
 * 文件名称：public.h
 * 描    述：
 * 当前版本：1.0
 * 作    者：潘亚东
 * 创建日期：2010年3月25日
 * 修改记录：
 */


#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#define  HPR_OK 0
#define  HPR_ERROR -1


#include "../include/HCNetSDK.h"

#define ACTIVE_MAX_LEN      10
#define USERNAME_MAX_LEN    20
#define PASSWORD_MAX_LEN    45
#define IPADDRESS_MAX_LEN   16
#define PORTNO_MAX_LEN      6

typedef struct {
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


typedef struct {
    long msg_type;  
    loginfo_t msg_loginfo;
}loginfo_msgqueue_t;


#define RCV_MSGKEY 1234
#define SED_MSGKEY 1024
#define MSG_BUFFER_SIZE 1024
typedef struct   
{  
    long msg_type;  
    char msg_content[MSG_BUFFER_SIZE];  

}msg_queue_t;



#define MESSAGE_MAX_LEN     45
#define ERRORNO_START       0
#define ERRORNO_END         200

#define CODE_SUCCESS                0
#define MESSAGE_SUCCESS             "success"

#define CODE_UNKNOWN_ERROR          1
#define MESSAGE_UNKNOWN_ERROR       "unknown error"

#define CODE_LOGIN_TIMEOUT          5
#define MESSAGE_LOGIN_TIMEOUT       "login timeout"

#define CODE_DEV_CONNECT_FAILED     7
#define MESSAGE_DEV_CONNECT_FAILED  "device connect failed"

typedef struct {
    int code;
    char message[MESSAGE_MAX_LEN];
}response_nopayload_t;

typedef struct {
    int code;
    int value;
    char *message;
}response_payload_t;

typedef struct {
    long msg_type;  
    response_nopayload_t msg_response;
}rsp_msgqueue_t;

#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))
#define DEFAULT_ERRORNO {CODE_UNKNOWN_ERROR, MESSAGE_UNKNOWN_ERROR};


#endif
