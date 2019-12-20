#include "CExecAction.h"
#include "CUartDev.h"
#include "CPTZ.h"
#include <string.h>
#include <stdlib.h>
#include "public.h"


#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif







static command_t command_lit[] = {
    {"login", MINOR_REMOTE_LOGIN, &CExecAction::Login_Equipment},
    {"logout", MINOR_REMOTE_LOGOUT, &CExecAction::Logout_Equipment},
};


static instruction_t instruction_lit[] = {
    {"mv_stop", 0, {0xff,0x01,0x00,0x00,0x00,0x00,0x01}},
	{"tilt_up", TILT_UP, {0xff,0x01,0x00,0x08,0x00,0xff,0x08}},
	{"tilt_down", TILT_DOWN, {0xff,0x01,0x00,0x10,0x00,0xff,0x10}},
	{"pan_left", PAN_LEFT, {0xff,0x01,0x00,0x04,0xff,0x00,0x04}},
	{"pan_right", PAN_RIGHT, {0xff,0x01,0x00,0x02,0xff,0x00,0x02}},

    {"up_left", UP_LEFT, {0xff,0x01,0x00,0x0c,0x1f,0x1f,0x4b}},
	{"up_right", UP_RIGHT, {0xff,0x01,0x00,0x0a,0x1f,0x1f,0x49}},
	{"down_left", DOWN_LEFT, {0xff,0x01,0x00,0x14,0x1f,0x1f,0x53}},
	{"down_right", DOWN_RIGHT, {0xff,0x01,0x00,0x12,0xff,0x00,0x51}},
};




CExecAction::CExecAction()
{
	m_Errorno = -1;
	m_UserID = -1;
	pUartDev = new CUartDev;
	

	
}

CExecAction::~CExecAction()
{
	
	
}

/*	初始化串口
 *
 */
void CExecAction::uartCom_Init()
{
    uart_config_t config;
    config.baud_rate = 115200;
    config.data_width = DATA_WIDTH_8BIT;
    config.parity = NO_PARITY;
    config.stop_bits = STOP_BITS_1;
    config.mode = MODE_TX_RX;

    pUartDev->uart_Config(1, "/dev/ttyUSB2", config);

    if(0 != pUartDev->uart_Init())
    {
        cout << "uart Init failed" << endl;
        return ;
    }		
}

/*	设置错误码
 *
 */
void CExecAction::set_Errorno(void)
{
    int errorno = 0;

    errorno =  NET_DVR_GetLastError();
    m_Errorno = errorno;
}

/*	获取错误码
 *
 */
int CExecAction::get_Errorno(void)
{
    int errorno;

    errorno = m_Errorno;
    m_Errorno = 0;

    return errorno;
}

/*	执行命令(SDK)
 *
 */
int CExecAction::Exec_Command(const char *str_cmd, char *data)
{
    unsigned int i; 
    command_t *psrt_cmd = 0;

    if(str_cmd == NULL)
        return -1;

    for(i = 0; i < ARRAY_SIZE(command_lit); i++)
    {
        psrt_cmd = &command_lit[i];
        if(strncmp(psrt_cmd->name, str_cmd, strlen(str_cmd)) == 0 || psrt_cmd->cmd_no == atoi(str_cmd))
            break;
        else
            psrt_cmd = 0;
    }
    
    if(psrt_cmd != 0)
    {
        (this->*psrt_cmd->func)(data);
        return get_Errorno();
    }

    return -1;
}

/*	执行指令(RS485)
 *
 */
int CExecAction::Exec_Instruction(char *instruct, char *value)
{
	unsigned int i;
	instruction_t * cmd = 0;

    if(instruct == NULL || pUartDev == NULL)
        return -1;

    for(i = 0; i < ARRAY_SIZE(instruction_lit); i++){
        cmd = &instruction_lit[i];
        if(strncmp(cmd->name, instruct, strlen(instruct)) == 0)
            break;
        else
            cmd = 0;
    }

    if(cmd == 0){
        return CODE_DEV_OPRATEFAILED;
    }else{
        //执行发送指令
        if(0 == pUartDev->uart_Send(cmd->pelco_d, sizeof(cmd->pelco_d))){
            cout << "instruct " << instruct << " successed" << endl;
            return CODE_SUCCESS;
        }
        cout << "instruct " << instruct << " failed" << endl;
    }    

    return CODE_DEV_OPRATEFAILED;
}

/*	执行指令(RS485)
 *
 */
int CExecAction::Exec_Instruction(int instruct, char *value)
{
	unsigned int i;
	instruction_t * cmd = 0;

	if(pUartDev == NULL)
		return CODE_DEV_OPRATEFAILED;
	
    for(i = 0; i < ARRAY_SIZE(instruction_lit); i++){
        cmd = &instruction_lit[i];
        if(cmd->instruction_no == instruct)
            break;
        else
            cmd = 0;
    }

    if(cmd == 0){
        return CODE_DEV_OPRATEFAILED;
    }
	else{
        //执行发送指令
        if(0 == pUartDev->uart_Send(cmd->pelco_d, sizeof(cmd->pelco_d))){
            cout << "instruct " << instruct << " successed" << endl;
            return CODE_SUCCESS;
        }
        cout << "instruct " << instruct << " failed" << endl;
    }    

    return CODE_DEV_OPRATEFAILED;
}
/************************************************************************************/
/*	登录设备
 *
 */
void CExecAction::Login_Equipment(char *arg)
{
	loginfo_t *ploginfo = (loginfo_t*)arg;
	
    NET_DVR_Init();
    //Login device
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = ploginfo->portno;
    memcpy(struLoginInfo.sDeviceAddress, ploginfo->ipaddress, NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, ploginfo->username, NAME_LEN);
    memcpy(struLoginInfo.sPassword, ploginfo->password, NAME_LEN);

    m_UserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (m_UserID < 0)
    {
        set_Errorno();
#ifdef DEBUG
        cout << "login device error: " << NET_DVR_GetLastError() << endl;
#endif
        cout << "login device error: " << NET_DVR_GetLastError() << endl;
        NET_DVR_Cleanup();
        return ;
    }
    NET_DVR_Cleanup();

    return ;
}

/*	登出设备
 *
 */
void CExecAction::Logout_Equipment(char *arg)
{
    NET_DVR_Init();

    if(FALSE == NET_DVR_Logout_V30(m_UserID))
    {
        set_Errorno();
#ifdef DEBUG
        cout << "logout device error: " << NET_DVR_GetLastError() << endl;
#endif
        return ;
    }
	m_UserID = -1;
    NET_DVR_Cleanup();

    return ;
}
