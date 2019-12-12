#include <iostream>
#include "GetStream.h"
#include "public.h"
#include "ConfigParams.h"
#include "Alarm.h"
#include "CapPicture.h"
#include "Contral.h"
#include "PTZPCruise.h"
#include "playback.h"
#include "Voice.h"
#include "tool.h"
#include <string.h>

#include "sensor_measure.h"
#include "execution_instruction.h"
using namespace std;

#define USE_MSGQUEUE

typedef struct {
    int rcv_msgid;
    int sed_msgid;
    int uart_hand;
}GLOBAL_HEADLE_T;

GLOBAL_HEADLE_T g_headle;

int get_rcvmsgid(void)
{
    return g_headle.rcv_msgid;
}

int get_sedmsgid(void)
{
    return g_headle.sed_msgid;
}


const static response_nopayload_t response_nopayload_list[] = {
    {CODE_SUCCESS, MESSAGE_SUCCESS},
    {CODE_LOGIN_TIMEOUT, MESSAGE_LOGIN_TIMEOUT},
    {CODE_DEV_CONNECT_FAILED, MESSAGE_DEV_CONNECT_FAILED},
};

bool get_error_event(int errorno, response_nopayload_t *response)
{

    if(errorno < ERRORNO_START || errorno > ERRORNO_END)
        return false;

    for(unsigned int i=0; i<ARRAY_SIZE(response_nopayload_list); i++)
    {
        if(errorno == response_nopayload_list[i].code){
            response->code = response_nopayload_list[i].code;
            strcpy(response->message, response_nopayload_list[i].message);
        }
    }
    
    return true;
}
/**********************************************/
#define BEGIN_PROTOCOL_MAP static const ProtocolMap ProtocolMapEntries[] = \
{
#define END_PROTOCOL_MAP    {0,0},\
};

typedef int PackdefType;
     
#define  DEF_EVENT_START_TYPE   0
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
#define  DEF_EVENT_END_TYPE     200


struct ProtocolMap
{
    int  m_ntype;
    char *m_action;
    void (*func)(char*action, char *data);
};

void do_response_nopayload(int errorno, int msg_type);
void do_reqLog(char* action, char*data);
void do_reqContrl(char* action, char*data);


BEGIN_PROTOCOL_MAP
{ DEF_LOGIN_TYPE, "login", &do_reqLog },
{ DEF_LOGOUT_TYPE, "logout", &do_reqLog },
{ DEF_MVSTOP_TYPE, "mv_stop", &do_reqContrl },
{ DEF_TILT_UP_TYPE, "up_left", &do_reqContrl },
{ DEF_UP_RIGHT_TYPE, "up_right", &do_reqContrl },
{ DEF_DOWN_LEFT_TYPE, "down_left", &do_reqContrl },
{ DEF_DOWN_RIGHT_TYPE, "down_right", &do_reqContrl },
{ DEF_TILT_UP_TYPE, "tilt_up", &do_reqContrl },
{ DEF_TILT_DOWN_TYPE, "tilt_down", &do_reqContrl },
{ DEF_PAN_LEFT_TYPE, "pan_left", &do_reqContrl },
{ DEF_PAN_RIGHT_TYPE, "pan_right", &do_reqContrl },
END_PROTOCOL_MAP

char *get_rawdata(char *pdata)
{
    char *ptmp_data = NULL;
    msg_queue_t *pmsg = (msg_queue_t*)pdata;

    if(pdata == pmsg->msg_content)
        return NULL;
    ptmp_data = pmsg->msg_content;

    return ptmp_data;
}


void DealData(char *szbuf)
{
    int i = 0;
    char *raw_data;
    //判断报类型
    PackdefType *ptype = (PackdefType *)szbuf;
    raw_data = get_rawdata(szbuf);

    if(*ptype <= DEF_EVENT_START_TYPE || *ptype > DEF_EVENT_END_TYPE)
    {
        do_response_nopayload(CODE_UNKNOWN_ERROR, *ptype);
        return ;
    }

    while(1)
    {
        if(ProtocolMapEntries[i].m_ntype == *ptype && ProtocolMapEntries[i].m_ntype != 0){
            (*ProtocolMapEntries[i].func)(ProtocolMapEntries[i].m_action, raw_data);
            break;
        }

        i++;
    }
}



/********** msgqueue ***********/ 
#include <sys/ipc.h>   
#include <sys/msg.h>




void msgProc()
{
    //loginfo_msgqueue_t login_msgs = {0};
    msg_queue_t msg = {0};
    int ret_value;
    bool running = true;
    
    int rcv_msgid;
    rcv_msgid = msgget(RCV_MSGKEY, IPC_EXCL);//检查消息队列是否存在
    if(rcv_msgid < 0){
        rcv_msgid = msgget(RCV_MSGKEY, IPC_CREAT|0666);//创建消息队列
        if(rcv_msgid < 0){
            msgctl(rcv_msgid, IPC_RMID, NULL);
        }
    }
    cout << "asdafs:" << rcv_msgid << endl;
    while(running)
    {
        //ret_value = msgrcv(rcv_msgid, &login_msgs, sizeof(msg_queue_t), 0, 0);
        ret_value = msgrcv(rcv_msgid, &msg, sizeof(msg_queue_t), 0, 0);
        if(-1 == ret_value)
        {
            cout << "msgrcv failed" << endl;
//            running = false;
        }
/*
     cout << "type:" << login_msgs.msg_type << endl;
     cout << "username:" << login_msgs.msg_loginfo.username << endl;
     cout << "password:" << login_msgs.msg_loginfo.password << endl;
     cout << "ipaddress:" << login_msgs.msg_loginfo.ipaddress << endl;
     cout << "portno:" << login_msgs.msg_loginfo.portno << endl; 
     DealData((char*)&login_msgs);
*/


        loginfo_t *loginfo = (loginfo_t*)msg.msg_content;

        cout << "type:" << msg.msg_type << endl;
        cout << "username:" << loginfo->username << endl;
        cout << "password:" << loginfo->password << endl;
        cout << "ipaddress:" << loginfo->ipaddress << endl;
        cout << "portno:" << loginfo->portno << endl; 

        DealData((char*)&msg);

   } 
}


/********** pipe ***********/ 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "servereq.h"

#define FIFO_NAME ("/tmp/servehandlerfifo")                 // 设定FIFO的名字
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)   // 设定创建FIFO的权限
#define BUFF_SIZE (1024)

extern bool doreq_by_name(const char *active, void *data);
void do_reqLog(void *data);
void do_reqContrl(void *data);

/********** rs485 ************/
#include "arm_linux_uart.h"
extern bool Exec_Instruction(uart_dev_t *uart, int argc ,char *argv[]);
extern int Exec_Instruction(uart_dev_t *uart, char *instruct, char *value);
extern int Exec_Command(const char *str_cmd, void *data);

uart_dev_t g_uart;

void YunTai_Serial_Init(int serialNo, char *devName)
{
    uart_config_t config;

    config.baud_rate = 2400;
    config.data_width = DATA_WIDTH_8BIT;
    config.parity = NO_PARITY;
    config.stop_bits = STOP_BITS_1;
    config.mode = MODE_TX_RX;

    Uart_Config(&g_uart, serialNo, devName, config);

    if(0 != Uart_Init(&g_uart))
    {
        printf("uart open failed \r\n");
        return ;
    }
    
    printf("uart open successed \r\n");
}

/********  log device  *******/
int g_userID = -1;
extern sensor_value_t g_sensors; 

extern int Login_Equipment();
extern BOOL Logout_Equipment(int lUSerId);
extern bool Exec_Command(char *str_cmd, void *data);

void do_reqLog(void *data)
{
    loginfo_t *loginfo = (loginfo_t*)data;
/*
    if(true == Exec_Command((const char*)loginfo->active, loginfo))
        cout << "do command" << loginfo->active << " device failed" << endl;
    else
        cout << "do command" << loginfo->active << " device successed" << endl;
*/
}

void do_reqContrl(void *data)
{
/*
    char **ppstr = NULL;
    contrl_params_t *params = (contrl_params_t*)data;

    ppstr = (char**)malloc(sizeof(char*)*2);
    for(int i=0; i<2; i++)
        ppstr[i] = (char*)malloc(sizeof(char*)*20);
    
    strncpy(ppstr[0], (char*)params->active, strlen((char*)params->active));
    if(true == Exec_Instruction(&g_uart, 1, ppstr))
        cout << "do instruction" << params->active << "successed" << endl;     
    else
        cout << "do instruction" << params->active << "failed" << endl;     
        */
}


/*************************************************************************************/
void do_response_nopayload(int errorno, int msg_type)
{
    int ret_value;
    rsp_msgqueue_t rsp_msgs;
    response_nopayload_t response = DEFAULT_ERRORNO;

    get_error_event(errorno, &response);

    memset((char*)&rsp_msgs, 0, sizeof(rsp_msgqueue_t));
    rsp_msgs.msg_type = msg_type;
    rsp_msgs.msg_response = response;

    ret_value = msgsnd(get_sedmsgid(), &rsp_msgs, sizeof(rsp_msgs), IPC_NOWAIT);
    if(-1 == ret_value)
    {
        cout << "msgrcv failed" << endl;
    }
}


void do_reqLog(char *action, char *data)
{
    int errorno = 0;

    errorno = Exec_Command((const char*)action, data);
    do_response_nopayload(errorno, DEF_LOGIN_TYPE);
}

void do_reqContrl(char *action, char *value)
{
    int errorno = 0;

    if(action == NULL)
        return;

    errorno == Exec_Instruction(&g_uart, action, value);
    do_response_nopayload(errorno, DEF_LOGIN_TYPE);
}


void Demo_Server(int pipefd)
{
    char readbuff[BUFF_SIZE];
    char writebuff[BUFF_SIZE];
    char command[ACTIVE_MAX_LEN];
    int readlen = 0;
    int writelen = 0;

    //log_params_t params;
    while(1)
    {
        readlen = 0;
        writelen = 0;
        memset(readbuff, 0, BUFF_SIZE);
        memset(writebuff, 0, BUFF_SIZE);
        // 读取FIFO
        readlen = read(pipefd, readbuff, BUFF_SIZE);
        if(-1 != readlen)
        {
            DealData(readbuff);
        }
/*
        loginfo_t *loginfo = (loginfo_t*)readbuff;
        if(strcmp(loginfo->active, "login") == 0 || strcmp(loginfo->active, "logout") == 0)
        {
            strcpy(command, "reqLog");
        }
        if(true == doreq_by_name(command, loginfo))
        {
            cout << "command " << loginfo->active << " done" << endl;
            sprintf(writebuff, "command %s done", loginfo->active);
        }else{

            cout << "do command " << loginfo->active << " failed" << endl;
            sprintf(writebuff, "do command %s failed", loginfo->active);
            return ;
        }
        if(0 >= write(pipefd, writebuff, strlen(writebuff)))
            break;
*/
    }

    // 关闭FIFO
    if(-1 == close(pipefd))
    {
        perror("关闭FIFO失败");
        unlink(FIFO_NAME);
        exit(1);
    }

    // 删除FIFO
    unlink(FIFO_NAME);
}



int main()
{
    char cUserChoose;
    
#ifdef USE_PIPE
    int pipefd = -1;
    if(mkfifo(FIFO_NAME, FILE_MODE) < 0)
    {
        perror("create FIFO error");
        exit(1);
    }
    // 打开FIFO
    pipefd = open(FIFO_NAME, O_RDWR, 0);
    if(-1 == pipefd)
    {
        unlink(FIFO_NAME);
        exit(1);
    }
#endif

#ifdef USE_MSGQUEUE
    int rcv_msgid;
    rcv_msgid = msgget(RCV_MSGKEY,IPC_EXCL);//检查消息队列是否存在
    if(rcv_msgid < 0){
        rcv_msgid = msgget(RCV_MSGKEY,IPC_CREAT|0666);//创建消息队列
        if(rcv_msgid < 0){
            cout << "errno = " << errno << "==>" << strerror(errno) << endl;
            msgctl(rcv_msgid, IPC_RMID, NULL);
            exit(1);
        }
    }

    g_headle.rcv_msgid = rcv_msgid;
    cout << "rcv_msgid:" << rcv_msgid << endl;


    int sed_msgid;
    sed_msgid = msgget(SED_MSGKEY,IPC_EXCL);
    if(sed_msgid < 0){
        sed_msgid = msgget(SED_MSGKEY,IPC_CREAT|0666);
        if(sed_msgid < 0){
            cout << "errno = " << errno << "==>" << strerror(errno) << endl;
            exit(1);
        }
    }

    cout << "rcv_msgid:" << sed_msgid << endl;
    g_headle.sed_msgid = sed_msgid;
#endif

    request_initial();
    addto_reqitem("reqLog", do_reqLog);
    addto_reqitem("reqContrl", do_reqContrl);
/*
    lUserID = Login_Equipment();
    if(lUserID == HPR_ERROR)
    {
        cout << "longin device failed" << endl;
        return -1;
    }
    cout << "login device" << endl;

    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.lChannel     = 1;  //channel NO
    struPlayInfo.dwLinkMode   = 0;
    struPlayInfo.hPlayWnd = NULL;
    struPlayInfo.bBlocked = 1;
    struPlayInfo.dwDisplayBufNum = 1;

    realhandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, NULL, NULL);
    if (realhandle < 0)
    {
        printf("pyd1---realPlay error, %d\n", NET_DVR_GetLastError());
        return HPR_ERROR;
    }
*/    
    while ('q' != cUserChoose)
    {
        printf("\n");
        printf("Input 1, Test GetStream\n");
        printf("      2, Test Configure params\n");
        printf("      3, Test Alarm\n");
        printf("      4, Test Capture Picture\n");
        printf("      5, Test play back\n");
        printf("      6, Test Voice\n");
        printf("      7, Test SDK ability\n");
        printf("      8, Test tool interface\n");
        printf("      9, Test contral\n");
        printf("      0, Test PTZCruise\n");
        printf("      i, Test LoginDevice\n");
        printf("      m, Test main server\n");
		/*
        printf("      7, Test Matrix decode\n");
        printf("      8, Test PTZ\n");
        printf("      9, Test Format\n");
        printf("      0, Test Update\n");
        printf("      a, Test Serial trans\n");
        printf("      b, Test Configure Params\n");
        printf("      c, Test VCA && IVMS\n");
        */
        printf("      q, Quit.\n");
        printf("Input:");

        cin>>cUserChoose;
        switch (cUserChoose)
        {
        case '1':
            Demo_GetStream_V30(g_userID); //Get stream.
            break;
        case '2':
            Demo_ConfigParams(g_userID);  //Setting params.
            break;
        case '3':
            Demo_Alarm();         //Alarm & listen.
            break;
        case '4':
            Demo_Capture();
            break;
        case '5':
            Demo_PlayBack(g_userID);     //record & playback
            break;
        case '6':
            Demo_Voice();
            break;
        case '7':
            Demo_SDK_Ability();
            break;
		case '8':
			Demo_DVRIPByResolveSvr();
			break;
		case '9':
			Demo_Contral();
			break;
		case '0':
			Demo_PTZPCruise();
			break;
		case 'm':
            //Demo_Server(pipefd);
            msgProc();
			break;
        default:
            break;
        }
    }

    return 0;
}

