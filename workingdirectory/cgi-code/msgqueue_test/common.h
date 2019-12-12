#ifndef _COMMOM_H
#define _COMMOM_H


#define MESSAGE_MAX_LEN     45
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
    int code;
    char message[MESSAGE_MAX_LEN];
}response_nopayload_t;

typedef struct {
    int code;
    int value;
    char message[MESSAGE_MAX_LEN];
}response_payload_t;

#define BUFF_SIZE   4096

char stdin_buff[BUFF_SIZE];
char stdout_buff[BUFF_SIZE];

int DecodeAndProcessData(char *input, int data_len);
/*******************************************************************/
#define RCV_MSGKEY 1024
#define SED_MSGKEY 1234
#define MSG_BUFFER_SIZE 1024

typedef struct {
    long msg_type;  
    char msg_content[MSG_BUFFER_SIZE];
}msg_queue_t;


typedef struct {
    long msg_type;  
    loginfo_t msg_loginfo;
}loginfo_msgqueue_t;

typedef struct {
    long msg_type;  
    response_nopayload_t msg_response;
}rsp_msgqueue_t;

#define  DEF_LOGIN_TYPE         1
#define  DEF_LOGOUT_TYPE        2






#endif
