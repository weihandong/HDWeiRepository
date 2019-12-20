#ifndef _COMMOM_H
#define _COMMOM_H

#include "public.h"

//#define DEBUG


#define ACTION_MAX_LEN      20
#define SENSOR_NAME_LEN     20
/*
 * message queue
 */
#define RCV_MSGKEY 1024
#define SED_MSGKEY 1234

/*
 *   buffer size 
 */
#define BUFF_SIZE           1024
//#define MESSAGE_MAX_LEN     256
#define MSG_BUFFER_SIZE     1024
#define PAYLOAD_MAX_SIZE    512

/*
 * login information
 */
#define USERNAME_MAX_LEN    20
#define PASSWORD_MAX_LEN    45
#define IPADDRESS_MAX_LEN   16

/*
 * 登录消息负载结构体
 */
typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char ipaddress[IPADDRESS_MAX_LEN];
    int  portno;
}loginfo_t;

/* 登录返回消息结构体
 *
 */
typedef struct {
    loginfo_t loginfo_PTZ;
    loginfo_t loginfo_TI;
    loginfo_t loginfo_NM;
}rsp_loginfo_t;

/* 配置速度
 *
 */
typedef struct{
    char action[ACTION_MAX_LEN];
	int	 deviceId;
	int	 speedvalue;
}speed_config_t;



/*
 * 消息队列数组型负载结构体
 */
typedef struct {
    long msg_type;  
    char msg_content[MSG_BUFFER_SIZE];
}msg_queue_t;

/*
 * 消息队列结构体型，响应负载结构体
 */
typedef struct {
    long msg_type;  
    long msg_result;
    char msg_payload[MSG_BUFFER_SIZE];
}rsp_msgqueue_t;



#define  DEF_LOGIN_TYPE         1
#define  DEF_LOGOUT_TYPE        2

#define  DEF_MVSTOP_TYPE        3
#define  DEF_TILT_UP_TYPE       4
#define  DEF_TILT_DOWN_TYPE     5
#define  DEF_PAN_LEFT_TYPE      6
#define  DEF_PAN_RIGHT_TYPE     7
 
#define  DEF_UP_LEFT_TYPE       8
#define  DEF_UP_RIGHT_TYPE      9
#define  DEF_DOWN_LEFT_TYPE     10
#define  DEF_DOWN_RIGHT_TYPE    11

#define  DEF_SET_SPEED_TYPE     12

#define  DEF_ZOOM_IN_TYPE       13
#define  DEF_ZOOM_OUT_TYPE      14
#define  DEF_FOCUS_NEAR_TYPE    15
#define  DEF_FOCUS_FAR_TYPE     16
#define  DEF_IRIS_OPEN_TYPE     17
#define  DEF_IRIS_CLOSE_TYPE    18

#define  DEF_CAPTURE_PICTURE_TYPE   19  
#define  DEF_START_RECORD_TYPE      20
#define  DEF_STOP_RECORD_TYPE       21

#define  DEF_GET_NOISE_TYPE         30  
#define  DEF_GET_TEMPERATURE_TYPE   31
#define  DEF_GET_HUMIDITY_TYPE      32
#define  DEF_GET_CO2_TYPE           33
/*************************************************************************/
/*********************************************************************/
void request_Bad(char *json_string);
void request_Successed(char *json_string);
void request_Unauthorized(char *json_string);
void request_NoResources(char *json_string);
void request_ServerError(char *json_string);
void request_Unavailable(char *json_string);

int mqueue_Send(char *data, int len);
int mqueue_Recv(char *data, int len);

int struct_ResponseJson(char *json_context, long result);

void dealwith_GetRequest(int msg_type, char *action);
void dealwith_GetReqsensor(int msg_type, char *action);

#endif
