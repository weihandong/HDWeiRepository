#ifndef _COMMOM_H
#define _COMMOM_H


//#define DEBUG


/*
 * message queue
 */
#define RCV_MSGKEY 1024
#define SED_MSGKEY 1234

/*
 *   buffer size 
 */
#define BUFF_SIZE           1024
#define MESSAGE_MAX_LEN     256
#define MSG_BUFFER_SIZE     1024

/*
 * login information
 */
#define USERNAME_MAX_LEN    20
#define PASSWORD_MAX_LEN    45
#define IPADDRESS_MAX_LEN   16
#define PORTNO_MAX_LEN      6

/*
 * 登录消息负载结构体
 */
typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char ipaddress[IPADDRESS_MAX_LEN];
    char portno[PORTNO_MAX_LEN];
}loginfo_t;

/*
 *   sensors value struct
 */
typedef struct{
	int	temperature;
	int	humidity;
	int	noise;
}sensors_data_t;

/*
 * 事务处理返回响应，不带数据负载结构体
 */
typedef struct {
    int code;
    char message[MESSAGE_MAX_LEN];
}response_nopayload_t;

/*
 * 事务处理返回响应，带数据负载结构体
 */
typedef struct {
    int code;
    int value;
    char message[MESSAGE_MAX_LEN];
}response_payload_t;

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
    response_nopayload_t msg_response;
}rsp_msgqueue_t;

/*
 * 消息队列结构体型，登录消息负载结构体
 */
typedef struct {
    long msg_type;  
    loginfo_t msg_loginfo;
}loginfo_msgqueue_t;




#define  DEF_LOGIN_TYPE         1
#define  DEF_LOGOUT_TYPE        2

/*************************************************************************/
void request_Bad(char *json_string);
void request_Successed(char *json_string);
void request_Unauthorized(char *json_string);
void request_NoResources(char *json_string);
void request_ServerError(char *json_string);
void request_Unavailable(char *json_string);

void dealwith_request(char *json_str, int str_len, int msg_type);


#endif
