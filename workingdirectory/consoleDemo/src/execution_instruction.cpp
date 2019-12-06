#include "execution_instruction.h"
#include "arm_linux_uart.h"
#include <string.h>
#include <stdlib.h>

#include "public.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif


typedef struct {
    const char *name;
	const int cmd_no;
    void (*func)(void *arg);
}command_t;

typedef struct {
	const char *name;
	const int instruction_no;
 	const unsigned char pelco_d[7];
}instruction_t;

typedef struct _PELCOD_packet
{
    unsigned char bytes[32];
    uint32_t length;
} PELCOD_Packet_t;

void do_login(void *arg);
void do_logout(void *arg);


#define ARRAY_SIZE(array)   ( sizeof(array)/sizeof((array)[0]))

static command_t command_lit[] = {
    {
        .name = "login", 
        .cmd_no = MINOR_REMOTE_LOGIN, 
        .func = do_login
    },{
        .name = "logout", 
        .cmd_no = MINOR_REMOTE_LOGOUT, 
        .func = do_logout
    },
};


static instruction_t instruction_lit[] = {
    {"turn_stop", 0, {0xff,0x01,0x00,0x00,0x00,0x00,0x01}},
	{"tilt_up", TILT_UP, {0xff,0x01,0x00,0x08,0x00,0xff,0x08}},
	{"tilt_down", TILT_DOWN, {0xff,0x01,0x00,0x10,0x00,0xff,0x10}},
	{"pan_left", PAN_LEFT, {0xff,0x01,0x00,0x04,0xff,0x00,0x04}},
	{"pan_right", PAN_RIGHT, {0xff,0x01,0x00,0x02,0xff,0x00,0x02}},

    {"up_left", UP_LEFT, {0xff,0x01,0x00,0x0c,0x1f,0x1f,0x4b}},
	{"up_right", UP_RIGHT, {0xff,0x01,0x00,0x0a,0x1f,0x1f,0x49}},
	{"down_left", DOWN_LEFT, {0xff,0x01,0x00,0x14,0x1f,0x1f,0x53}},
	{"down_right", DOWN_RIGHT, {0xff,0x01,0x00,0x12,0xff,0x00,0x51}},
};



int Login_Equipment(loginfo_t *loginfo)
{
    NET_DVR_Init();
    //Demo_SDK_Version();
    //NET_DVR_SetLogToFile(3, "./sdkLog");
    
    //Login device
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = atoi(loginfo->portno);
    memcpy(struLoginInfo.sDeviceAddress, loginfo->ipaddress, NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, loginfo->username, NAME_LEN);
    memcpy(struLoginInfo.sPassword, loginfo->password, NAME_LEN);

    int lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (lUserID < 0)
    {
#ifdef DEBUG
        cout << "login device error: " << NET_DVR_GetLastError() << endl;
#endif
        NET_DVR_Cleanup();

        return HPR_ERROR;
    }

    return lUserID;
}

BOOL Logout_Equipment(int lUserID)
{
    if(FALSE == NET_DVR_Logout_V30(lUserID))
    {
#ifdef DEBUG
        cout << "logout device error: " << NET_DVR_GetLastError() << endl;
#endif
        return HPR_ERROR;
    }

    if(FALSE == NET_DVR_Cleanup())
    {
#ifdef DEBUG
        cout << "cleanup error: " << NET_DVR_GetLastError() << endl;
#endif
        return HPR_ERROR; 
    }

    return HPR_OK;
}




bool Exec_Command(const char *str_cmd, void *data)
{
    unsigned int i; 
    command_t *srt_cmd = 0;

    if(str_cmd == NULL)
        return false;

    for(i = 0; i < ARRAY_SIZE(command_lit); i++)
    {
        srt_cmd = &command_lit[i];
        if(strncmp(srt_cmd->name, str_cmd, strlen(str_cmd)) == 0 || srt_cmd->cmd_no == atoi(str_cmd))
            break;
        else
            srt_cmd = 0;
    }
    
    if(srt_cmd != 0)
    {
        srt_cmd->func(data);
        return true;
    }

    return false;
}



void PELCOD_Init_Packet(PELCOD_Packet_t *packet)
{
    packet->length = 1;
}

void PELCOD_Append_Byte(PELCOD_Packet_t *packet, unsigned char byte)
{
    packet->bytes[packet->length] = byte;
    (packet->length)++;
}

uint32_t PELCOD_Set_Pantilt_up(uint32_t pan_speed, uint32_t tilt_speed)
{
    return 0;
}



bool Exec_Instruction(uart_dev_t *uart, int argc , char *argv[])
{
	unsigned int i;
	instruction_t * cmd = 0;

	if(argc > 0)
	{
        if(argc == 1){
            if(argv[0] == "")
                return false;

            for(i = 0; i < ARRAY_SIZE(instruction_lit); i++)
            {
                cmd = &instruction_lit[i];
                if(strncmp(cmd->name,argv[0],strlen(argv[0])) == 0 || cmd->instruction_no == atoi(argv[1]))
                    break;
                else
                    cmd = 0;
            }
        }else{
            if(strcmp("", argv[0]) == 0 && atoi(argv[1]) == -1)
                return false;

            for(i = 0; i < ARRAY_SIZE(instruction_lit); i++)
            {
                cmd = &instruction_lit[i];
                if(strncmp(cmd->name,argv[0],strlen(argv[0])) == 0 || cmd->instruction_no == atoi(argv[1]))
                    break;
                else
                    cmd = 0;
            }
	    }
    }

    if(cmd == 0)
    {
#ifdef DEBUG
        cout << "invalid instruction" << endl;
#endif
    }else{
        //执行发送指令
        if(0 == Uart_Send(uart, cmd->pelco_d, sizeof(cmd->pelco_d)))
            return true;
    }    

    return false;
}


/************************************************************************************/
extern int g_userID;

void do_login(void *arg)
{
    loginfo_t *ploginfo = (loginfo_t*)arg;

    g_userID = Login_Equipment(ploginfo);
#ifdef DEBUG
    if(g_userID == HPR_OK)
        cout << "login device succeesed" << endl;
    else
        cout << "login device failed" << endl;
#endif
}



void do_logout(void *arg)
{
    BOOL status;
    
    status = Logout_Equipment(g_userID);
#ifdef DEBUG    
    if(status == HPR_OK)
        cout << "logout device succeesed" << endl;
    else
        cout << "logout device failed" << endl;
#endif

}
