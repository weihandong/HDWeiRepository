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

/********** fifo ***********/ 
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
extern bool Exec_Command(const char *str_cmd, void *data);

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





void Demo_RemteLogin(void *loginfo)
{
    long realhandle;

    if(false == Exec_Command("login", loginfo))
    {
        cout << "longin device failed" << endl;
        return ;
    }
    cout << "longin device successed" << endl;

    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.lChannel     = 1;  //channel NO
    struPlayInfo.dwLinkMode   = 0;
    struPlayInfo.hPlayWnd = NULL;
    struPlayInfo.bBlocked = 1;
    struPlayInfo.dwDisplayBufNum = 1;

    realhandle = NET_DVR_RealPlay_V40(g_userID, &struPlayInfo, NULL, NULL);
    if (realhandle < 0)
    {
        printf("pyd1---realPlay error, %d\n", NET_DVR_GetLastError());
        return ;
    }
}


void Demo_RemteLogout()
{

    if(false == Exec_Command("logout", (void*)NULL))
        cout << "logout device failed" << endl;
    else
        cout << "logout device successed" << endl;
}



void do_reqLog(void *data)
{
    log_params_t *params = (log_params_t*)data;

    if(false == Exec_Command((const char*)params->active, params->loginfo))
        cout << "do command" << params->active << " device failed" << endl;
    else
        cout << "do command" << params->active << " device successed" << endl;
}


void do_reqContrl(void *data)
{
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
}


void Demo_Server(int pipefd)
{
    char readbuff[BUFF_SIZE];
    char writebuff[BUFF_SIZE];
    int readlen = 0;
    int writelen = 0;

    loginfo_t loginfo = {"admin", "sshw1234", "192.168.31.173", "8000"};
    log_params_t params;

    strcpy(params.active,"login");
    params.loginfo = (char*)&loginfo;


    while(1)
    {
        readlen = 0;
        writelen = 0;
        memset(readbuff, 0, BUFF_SIZE);
        memset(writebuff, 0, BUFF_SIZE);


        // 读取FIFO
        readlen = read(pipefd, readbuff, BUFF_SIZE);
        if(-1 == readlen)
        {
            cout << "管道读取失败，退出" << endl;
            exit(1);
        }
        char *command = readbuff;
        
/*
        if(true == doreq_by_name("reqLog", &params))
        {
            cout << "command" << command << "done" << endl;
            sprintf(writebuff, "command %s done", command);
        }else{
*/
//            cout << "do command" << command << "failed" << endl;
//            sprintf(writebuff, "do command %s failed", command);
//            return ;
//        }
        //write(pipefd, writebuff, strlen(writebuff));
        write(pipefd, "1234", 5);
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
    
    int pipefd = -1;
    loginfo_t loginfo = {"admin", "sshw1234", "192.168.31.173", "8000"};
/*
    strncpy((char*)loginfo.username, "admin", strlen("admin"));
    strncpy((char*)loginfo.password, "sshw1234", strlen("sshw1234"));
    strncpy((char*)loginfo.ipaddress, "192.168.31.173", strlen("192.168.31.173"));
    strncpy((char*)loginfo.portno, "8000", strlen("8000"));
*/
    // 创建FIFO
    if(mkfifo(FIFO_NAME, FILE_MODE) < 0)
    {
        if(EEXIST == errno)
        {
            printf("FIFO：%s已经存在，不能重新创建\r\n", FIFO_NAME);
        }else{
            perror("create FIFO error");
            exit(1);
        }
    }

    request_initial();
    addto_reqitem("reqLog", do_reqLog);
    addto_reqitem("reqContrl", do_reqContrl);


    // 打开FIFO
    pipefd = open(FIFO_NAME, O_RDWR, 0);
    if(-1 == pipefd)
    {
        perror("打开FIFO失败");
        unlink(FIFO_NAME);
        exit(1);
    }
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
        printf("      o, Test LogoutDevice\n");
        printf("      c, Test Sensor measure\n");
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
		case 'i':
            Demo_RemteLogin((void*)&loginfo);
            break;
		case 'o':
            Demo_RemteLogout();
			break;
		case 'c':
            Demo_SensorsMeasure();
			break;
		case 'm':
            Demo_Server(pipefd);
			break;
        default:
            break;
        }
    }

    return 0;
}

