#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#define  HPR_OK 0
#define  HPR_ERROR -1


#include "../include/HCNetSDK.h"

#define ACTION_MAX_LEN      20
#define USERNAME_MAX_LEN    20
#define PASSWORD_MAX_LEN    45
#define IPADDRESS_MAX_LEN   16

typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char ipaddress[IPADDRESS_MAX_LEN];
    int  portno;
}loginfo_t;


typedef struct {
    loginfo_t loginfo_PTZ; //¿¿¿¿¿¿
    loginfo_t loginfo_TI;   //¿¿¿¿¿¿¿¿¿
    loginfo_t loginfo_NM;  //¿¿¿¿¿¿¿¿
}rsp_loginfo_t;

/* ¿¿¿¿¿¿¿¿ 
 *
 */
typedef struct{
    char action[ACTION_MAX_LEN];
	int	 deviceId;
	int	 speedvalue;
}speed_config_t;


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

typedef struct {
    long msg_type;
    long msg_result;
    char msg_payload[MSG_BUFFER_SIZE];
}rsp_msgqueue_t;


#define MESSAGE_MAX_LEN     45
#define PAYLOAD_MAX_SIZE    512
#define ERRORNO_START       0
#define ERRORNO_END         200

#define CODE_SUCCESS                0

#define CODE_PASSWORD_ERROR         1

#define CODE_DEV_CONNECT_FAILED     7

#define CODE_PARAMETER_ERROR        17

#define CODE_DEV_OPRATEFAILED       29

#define CODE_DEV_ERNOTEXIST         47



/*********************************************************************/
#define CODE_UNKNOWN_ERROR          30

#define CODE_SENSOR_ERROR           31

/*********************************************************************/

#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))
#define DEFAULT_ERRORNO {CODE_UNKNOWN_ERROR, MESSAGE_UNKNOWN_ERROR};

/**********************************************/
/*
 * ·þÎñ´¦ÀíÊÂ¼þÀàÐÍ
 */
#define  DEF_EVENT_START_TYPE       0

#define  DEF_LOGIN_TYPE             1
#define  DEF_LOGOUT_TYPE            2

#define  DEF_MVSTOP_TYPE            3
#define  DEF_TILT_UP_TYPE           4
#define  DEF_TILT_DOWN_TYPE         5
#define  DEF_PAN_LEFT_TYPE          6
#define  DEF_PAN_RIGHT_TYPE         7

#define  DEF_UP_LEFT_TYPE           8
#define  DEF_UP_RIGHT_TYPE          9
#define  DEF_DOWN_LEFT_TYPE         10
#define  DEF_DOWN_RIGHT_TYPE        11

#define  DEF_SET_SPEED_TYPE         12

#define  DEF_ZOOM_IN_TYPE           13
#define  DEF_ZOOM_OUT_TYPE          14
#define  DEF_FOCUS_NEAR_TYPE        15
#define  DEF_FOCUS_FAR_TYPE         16
#define  DEF_IRIS_OPEN_TYPE         17
#define  DEF_IRIS_CLOSE_TYPE        18

#define  DEF_CAPTURE_PICTURE_TYPE   19  
#define  DEF_START_RECORD_TYPE      20
#define  DEF_STOP_RECORD_TYPE       21

#define  DEF_GET_NOISE_TYPE         30  
#define  DEF_GET_TEMPERATURE_TYPE   31
#define  DEF_GET_HUMIDITY_TYPE      32
#define  DEF_GET_CO2_TYPE           33

#define  DEF_EVENT_END_TYPE     200
/**********************************************/
#endif
