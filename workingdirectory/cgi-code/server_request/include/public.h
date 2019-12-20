#ifndef PUBLIC_H
#define PUBLIC_H

#define CODE_SUCCESS                0
#define MESSAGE_SUCCESS             "success"

#define CODE_PASSWORD_ERROR         1
#define MESSAGE_PASSWORD_ERROR      "password error"

#define CODE_DEV_CONNECT_FAILED     7
#define MESSAGE_DEV_CONNECT_FAILED  "device connect failed"

#define CODE_ORDER_ERROR            12
#define MESSAGE_ORDER_ERROR         "device operate out of order"

#define CODE_PARAMETER_ERROR        17
#define MESSAGE_PARAMETER_ERROR     "device parampeter error"

#define CODE_NOSUPPORT_ERROR        23
#define MESSAGE_NOSUPPORT_ERROR     "device no support"

#define CODE_DEV_OPRATEFAILED       29
#define MESSAGE_DEV_OPRATEFAILED    "device operate failed"

#define CODE_DEV_ERNOTEXIST         47
#define MESSAGE_DEV_ERNOTEXIST      "device not exist"



/*********************************************************************/
#define CODE_UNKNOWN_ERROR          30
#define MESSAGE_UNKNOWN_ERROR       "unknown error"

#define CODE_SENSOR_ERROR           31
#define MESSAGE_SENSOR_ERROR        "sensor collected data error"

#define MESSAGE_MAX_LEN     256
/*
 * 事务处理返回响应，不带数据负载结构体
 */
typedef struct {
    long code;
    char message[MESSAGE_MAX_LEN];
}response_t;

/*
 * 服务处理返回的code和对应的message 响应事件
 */
#ifndef RESPONSE_LIST 
#define RESPONSE_LIST 

const static response_t response_list[] = {
    {CODE_SUCCESS, MESSAGE_SUCCESS},
    {CODE_UNKNOWN_ERROR, MESSAGE_UNKNOWN_ERROR},
    {CODE_DEV_CONNECT_FAILED, MESSAGE_DEV_CONNECT_FAILED},
    {CODE_PASSWORD_ERROR, MESSAGE_PASSWORD_ERROR},
    {CODE_PARAMETER_ERROR, MESSAGE_PARAMETER_ERROR},
    {CODE_DEV_ERNOTEXIST, MESSAGE_DEV_ERNOTEXIST},
    {CODE_DEV_OPRATEFAILED, MESSAGE_DEV_OPRATEFAILED},
    {CODE_ORDER_ERROR, MESSAGE_ORDER_ERROR},
    {CODE_NOSUPPORT_ERROR, MESSAGE_NOSUPPORT_ERROR},
    {CODE_SENSOR_ERROR, MESSAGE_SENSOR_ERROR},
};
#endif

#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))



#endif
