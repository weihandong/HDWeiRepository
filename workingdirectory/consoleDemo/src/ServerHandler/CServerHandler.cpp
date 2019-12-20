#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>   
#include <sys/msg.h>

#include "public.h"
#include "CPTZ.h"
#include "CSensorOpt.h"
#include "CServerHandler.h"

using namespace std;	
	
CServerHandler::CServerHandler()
{
    m_dwlastCmd = 0;
    m_deviceId = 1;
    m_dwSpeed = 5;

    m_pPtz = new CPTZ;
	if(m_pPtz == NULL)
		return ;

    m_pSensorOpt = new CSensorOpt;
    if(m_pSensorOpt == NULL)
    {
        return ;
    }
	
    m_rcvMsgid = msgget(RCV_MSGKEY,IPC_EXCL);//检查消息队列是否存在
    if(m_rcvMsgid < 0){
        m_rcvMsgid = msgget(RCV_MSGKEY,IPC_CREAT|0666);//创建消息队列
        if(m_rcvMsgid < 0){
            //cout << "errno = " << errno << "==>" << strerror(errno) << endl;
            msgctl(m_rcvMsgid, IPC_RMID, NULL);
        }
    }

    m_sedMsgid = msgget(SED_MSGKEY,IPC_EXCL);
    if(m_sedMsgid < 0){
        m_sedMsgid = msgget(SED_MSGKEY,IPC_CREAT|0666);
        if(m_sedMsgid < 0){
            //cout << "errno = " << errno << "==>" << strerror(errno) << endl;
            msgctl(m_sedMsgid, IPC_RMID, NULL);
        }
    }	
}


CServerHandler::~CServerHandler()
{
	msgctl(m_rcvMsgid, IPC_RMID, NULL);
    msgctl(m_sedMsgid, IPC_RMID, NULL);
}

/*
 * 获取发送消息队列content原始内容(不包含消息类型msg_type)
 *
 */
char* CServerHandler::get_Rawdata(char *pdata)
{
    char *ptmp_data = NULL;
    msg_queue_t *pmsg = (msg_queue_t*)pdata;

    if(pdata == pmsg->msg_content)
        return NULL;
    ptmp_data = pmsg->msg_content;

    return ptmp_data;
}

/*
 * 服务处理返回，不带负载响应
 *
 */
void CServerHandler::do_Response_Nopayload(int errorno, int msg_type)
{
    int ret_value;
    rsp_msgqueue_t rsp_msgs;

    memset((char*)&rsp_msgs, 0, sizeof(rsp_msgqueue_t));
    rsp_msgs.msg_type = msg_type;
    rsp_msgs.msg_result = errorno;

    ret_value = msgsnd(m_sedMsgid, &rsp_msgs, sizeof(rsp_msgs), IPC_NOWAIT);
    if(-1 == ret_value)
    {
        cout << "msgrcv failed" << endl;
    }
}

/*
 * 服务处理返回，带负载响应
 *
 */
 void CServerHandler::do_Response_payload(int errorno, int msg_type, char *payload, int payload_len)
{
    int ret_value;
    rsp_msgqueue_t rsp_msgs;

    memset((char*)&rsp_msgs, 0, sizeof(rsp_msgqueue_t));
    rsp_msgs.msg_type = msg_type;
    rsp_msgs.msg_result = errorno;
    memcpy(rsp_msgs.msg_payload, (char*)payload, payload_len);

/*********************************************************************************
    rsp_loginfo_t *rsploginfo = (rsp_loginfo_t*)rsp_msgs.msg_payload;
    cout << rsploginfo->loginfo_PTZ.username << endl;
    cout << rsploginfo->loginfo_PTZ.password <<endl;
    cout << rsploginfo->loginfo_PTZ.ipaddress << endl;
    cout << rsploginfo->loginfo_PTZ.portno << endl;
    //用户名
    cout << rsploginfo->loginfo_TI.username << endl;
    cout << rsploginfo->loginfo_TI.password <<endl;
    cout << rsploginfo->loginfo_TI.ipaddress<<endl;
    cout << rsploginfo->loginfo_TI.portno<<endl;
    //端口号 
    cout << rsploginfo->loginfo_NM.username<<endl;
    cout << rsploginfo->loginfo_NM.password<<endl;
    cout << rsploginfo->loginfo_NM.ipaddress<<endl;
    cout << rsploginfo->loginfo_NM.portno<<endl;
*********************************************************************************/
    ret_value = msgsnd(m_sedMsgid, &rsp_msgs, sizeof(rsp_msgs), IPC_NOWAIT);
    if(-1 == ret_value)
    {
        cout << "msgrcv failed" << endl;
    }
}


BEGIN_PROTOCOL_MAP
{ DEF_LOGIN_TYPE, &CServerHandler::do_ReqLogin },
{ DEF_LOGOUT_TYPE, &CServerHandler::do_ReqLogout },

{ DEF_MVSTOP_TYPE, &CServerHandler::do_ReqMvStop },
{ DEF_UP_LEFT_TYPE, &CServerHandler::do_ReqUpLeft },
{ DEF_UP_RIGHT_TYPE, &CServerHandler::do_ReqUpRight },
{ DEF_DOWN_LEFT_TYPE, &CServerHandler::do_ReqDownLeft },
{ DEF_DOWN_RIGHT_TYPE, &CServerHandler::do_ReqDownRight },
{ DEF_TILT_UP_TYPE, &CServerHandler::do_ReqTiltUp },
{ DEF_TILT_DOWN_TYPE, &CServerHandler::do_ReqTiltDown },
{ DEF_PAN_LEFT_TYPE, &CServerHandler::do_ReqPanLeft },
{ DEF_PAN_RIGHT_TYPE, &CServerHandler::do_ReqPanRight },

{ DEF_SET_SPEED_TYPE, &CServerHandler::do_ReqSpeedOpt },

{ DEF_ZOOM_IN_TYPE, &CServerHandler::do_ReqZoomIn },
{ DEF_ZOOM_OUT_TYPE, &CServerHandler::do_ReqZoomOut },
{ DEF_FOCUS_NEAR_TYPE, &CServerHandler::do_ReqFocusNear },
{ DEF_FOCUS_FAR_TYPE, &CServerHandler::do_ReqFocusFar },
{ DEF_IRIS_OPEN_TYPE, &CServerHandler::do_ReqIrisOpen },
{ DEF_IRIS_CLOSE_TYPE, &CServerHandler::do_ReqIrisClose },

{ DEF_CAPTURE_PICTURE_TYPE, &CServerHandler::do_ReqCapturePicture },
{ DEF_START_RECORD_TYPE, &CServerHandler::do_ReqStartVideoRecord },
{ DEF_STOP_RECORD_TYPE, &CServerHandler::do_ReqStopVideoRecord },

{ DEF_GET_TEMPERATURE_TYPE, &CServerHandler::do_ReqTemperatureValue },
{ DEF_GET_HUMIDITY_TYPE, &CServerHandler::do_ReqHumidityValue },
{ DEF_GET_NOISE_TYPE, &CServerHandler::do_ReqNoiseValue },
{ DEF_GET_CO2_TYPE, &CServerHandler::do_ReqCO2Value },
END_PROTOCOL_MAP


/*  处理请求
 *  
 */
void CServerHandler::dealwith_Handler(char *szbuf)
{
    int i = 0;
    //判断报类型
    PackdefType *ptype = (PackdefType *)szbuf;

    if(*ptype <= DEF_EVENT_START_TYPE || *ptype > DEF_EVENT_END_TYPE)
    {
        do_Response_Nopayload(CODE_UNKNOWN_ERROR, *ptype);
        return ;
    }

    while(1)
    {
        if(ProtocolMapEntries[i].m_ntype == *ptype){
            (this->*ProtocolMapEntries[i].func)(szbuf);
            return ;
        }

        i++;
    }
    do_Response_Nopayload(CODE_UNKNOWN_ERROR, *ptype);
}


void CServerHandler::msgProcPoll()
{
    bool running = true;
    msg_queue_t msg = {0};
    int ret_value;

    while(running)
    {
        ret_value = msgrcv(m_rcvMsgid, &msg, sizeof(msg_queue_t), 0, 0);
        if(-1 == ret_value)
        {
            cout << "msgrcv failed" << endl;
            msgctl(m_sedMsgid, IPC_RMID, NULL);
            msgctl(m_rcvMsgid, IPC_RMID, NULL);
            running = false;
        }
        dealwith_Handler((char*)&msg);
   } 
}


/*  处理设备的登录请求
 *  
 */
void CServerHandler::do_ReqLogin(char *data)
{
    int errorno = 0;
    char *raw_data;
    int *pmsg_type = (int*)data;
    raw_data = get_Rawdata(data);
	loginfo_t *ploginfo = (loginfo_t*)raw_data;

    if(HPR_OK == m_pPtz->login_Equipment(ploginfo->username, ploginfo->password, ploginfo->ipaddress, ploginfo->portno)){
        rsp_loginfo_t rsp_loginfo={0};

        strcpy(rsp_loginfo.loginfo_PTZ.username,"admin");
        strcpy(rsp_loginfo.loginfo_PTZ.password, "sshw1234");
        strcpy(rsp_loginfo.loginfo_PTZ.ipaddress, "192.168.31.173");
        rsp_loginfo.loginfo_PTZ.portno = 8000;

        strcpy(rsp_loginfo.loginfo_TI.username, "admin");
        strcpy(rsp_loginfo.loginfo_TI.password, "sshw1234");
        strcpy(rsp_loginfo.loginfo_TI.ipaddress, "192.168.31.172");
        rsp_loginfo.loginfo_TI.portno = 8000;

        strcpy(rsp_loginfo.loginfo_NM.username, "admin");
        strcpy(rsp_loginfo.loginfo_NM.password, "123456");
        strcpy(rsp_loginfo.loginfo_NM.ipaddress, "192.168.31.177");
        rsp_loginfo.loginfo_NM.portno = 80;

        errorno = get_PTZErrorno();
        do_Response_payload(errorno, *pmsg_type, (char*)&rsp_loginfo, sizeof(rsp_loginfo));

        cout << "login successed" << endl;
        return ;
    }

    cout << "login failed" << endl;
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/*  处理设备的登出请求
 *  
 */
void CServerHandler::do_ReqLogout(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->logout_Equipment()){
        cout << "logout successed" << endl;
    }
    else{
        cout << "logout failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 设备控制停止动作
 *  
 */
void CServerHandler::do_ReqMvStop(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_MvStop(m_dwlastCmd)){
        m_dwlastCmd = 0;
        cout << "device move stop successed" << endl;
    }
    else{
        cout << "device move stop failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);

}

/* 云台上仰和左转
 *  
 */
void CServerHandler::do_ReqUpLeft(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_UpLeft(ENABLE, m_dwSpeed)){
        m_dwlastCmd = UP_LEFT;
        cout << "device up left successed" << endl;
    }
    else{
        cout << "device up left failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 云台上仰和右转
 *  
 */
void CServerHandler::do_ReqUpRight(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_UpRight(ENABLE, m_dwSpeed)){
        m_dwlastCmd = UP_RIGHT;
        cout << "device up right successed" << endl;
    }
    else{
        cout << "device up right failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 云台下俯和左转
 *  
 */
void CServerHandler::do_ReqDownLeft(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_DownLeft(ENABLE, m_dwSpeed)){
        m_dwlastCmd = DOWN_LEFT;
        cout << "device down left successed" << endl;
    }
    else{
        cout << "device down left failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 云台下俯和右转
 *  
 */
void CServerHandler::do_ReqDownRight(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_DownRight(ENABLE, m_dwSpeed)){
        m_dwlastCmd = DOWN_RIGHT;
        cout << "device down right successed" << endl;
    }
    else{
        cout << "device down right failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);

}

/* 云台上仰
 *  
 */
void CServerHandler::do_ReqTiltUp(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_TiltUp(ENABLE, m_dwSpeed)){
        m_dwlastCmd = TILT_UP;
        cout << "device tilt up successed" << endl;
    }
    else{
        cout << "device tilt up failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}


/* 云台下俯
 *  
 */
void CServerHandler::do_ReqTiltDown(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_TiltDown(ENABLE, m_dwSpeed)){
        m_dwlastCmd = TILT_DOWN;
        cout << "device tilt down successed" << endl;
    }
    else{
        cout << "device tilt down failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 云台左转
 *  
 */
void CServerHandler::do_ReqPanLeft(char *data)
{

    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_PanLeft(ENABLE, m_dwSpeed)){
        m_dwlastCmd = PAN_LEFT;
        cout << "device pan left successed" << endl;
    }
    else{
        cout << "device pan left failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 云台下俯
 *  
 */
void CServerHandler::do_ReqPanRight(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_PanRight(ENABLE, m_dwSpeed)){
    m_dwlastCmd = PAN_RIGHT;
        cout << "device pan right successed" << endl;
    }
    else{
        cout << "device pan right failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 设置转速
 *
 */
void CServerHandler::do_ReqSpeedOpt(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;
    char *raw_data = get_Rawdata(data);

	speed_config_t *pspeedcfg = (speed_config_t *)raw_data;
   
    if(pspeedcfg->deviceId == m_deviceId && strcmp(pspeedcfg->action, "set") == 0 ){
        if(pspeedcfg->speedvalue > 0 && pspeedcfg->speedvalue <= 7){
            m_dwSpeed = pspeedcfg->speedvalue;
            cout << pspeedcfg->action << " device: " << pspeedcfg->deviceId << " speed value" << pspeedcfg->speedvalue << endl;
        }else{
            errorno = CODE_PARAMETER_ERROR;
        }
    }

    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 焦距变大
 *
 */
void CServerHandler::do_ReqZoomIn(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_ZoomIn(ENABLE)){
    m_dwlastCmd = ZOOM_IN;
        cout << "device zoom in successed" << endl;
    }
    else{
        cout << "device zoom in failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 焦距变小
 *
 */
void CServerHandler::do_ReqZoomOut(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_ZoomOut(ENABLE)){
    m_dwlastCmd = ZOOM_OUT;
        cout << "device zoom out successed" << endl;
    }
    else{
        cout << "device zoom out failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);

}

/* 焦点前调
 *
 */
void CServerHandler::do_ReqFocusNear(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_FocusNear(ENABLE)){
    m_dwlastCmd = FOCUS_NEAR;
        cout << "device focus near successed" << endl;
    }
    else{
        cout << "device fous near failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 焦点前调
 *
 */
void CServerHandler::do_ReqFocusFar(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_FocusFar(ENABLE)){
    m_dwlastCmd = FOCUS_FAR;
        cout << "device focus far successed" << endl;
    }
    else{
        cout << "device focus far failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 光圈扩大
 *
 */
void CServerHandler::do_ReqIrisOpen(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_IrisOpen(ENABLE)){
    m_dwlastCmd = IRIS_OPEN;
        cout << "device iris open successed" << endl;
    }
    else{
        cout << "device iris open failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 光圈缩小
 *
 */
void CServerHandler::do_ReqIrisClose(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_IrisClose(ENABLE)){
    m_dwlastCmd = IRIS_CLOSE;
        cout << "device iris close successed" << endl;
    }
    else{
        cout << "device iris open failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}


/* 预览抓图
 *
 */
void CServerHandler::do_ReqCapturePicture(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_IrisClose(ENABLE)){
    m_dwlastCmd = IRIS_CLOSE;
        cout << "device capture picture successed" << endl;
    }
    else{
        cout << "device capture picture failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 预览录像，捕获数据并存放到指定的文件中
 *
 */
void CServerHandler::do_ReqStartVideoRecord(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_IrisClose(ENABLE)){
    m_dwlastCmd = IRIS_CLOSE;
        cout << "device start video recording  successed" << endl;
    }
    else{
        cout << "device start video recording failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 停止录像，停止数据捕获。
 *
 */
void CServerHandler::do_ReqStopVideoRecord(char *data)
{
    int errorno = 0;
    int *pmsg_type = (int*)data;

    if(HPR_OK == m_pPtz->m_pPTZControl->contrl_IrisClose(ENABLE)){
    m_dwlastCmd = IRIS_CLOSE;
        cout << "device stop video recording successed" << endl;
    }
    else{
        cout << "device stop video recording failed" << endl;
    }
    errorno = get_PTZErrorno();
    do_Response_Nopayload(errorno, *pmsg_type);
}

/* 请求温度传感器数值
 *
 */
void CServerHandler::do_ReqTemperatureValue(char *data)
{
    int errorno = 0;
    int sensor_value = 0;
    int *pmsg_type = (int*)data;

    sensor_value = m_pSensorOpt->get_TemperatureValue();
    do_Response_payload(errorno, *pmsg_type, (char*)&sensor_value, sizeof(int));
    cout << "request temperature value:" << sensor_value << endl;
}

/* 请求湿度传感器数值
 *
 */
void CServerHandler::do_ReqHumidityValue(char *data)
{
    int errorno = 0;
    int sensor_value = 0;
    int *pmsg_type = (int*)data;

    sensor_value = m_pSensorOpt->get_HumidityValue();
    
    do_Response_payload(errorno, *pmsg_type, (char*)&sensor_value, sizeof(int));
    cout << "request humidity value:" << sensor_value << endl;
}

/* 请求噪声传感器数值
 *
 */
void CServerHandler::do_ReqNoiseValue(char *data)
{
    int errorno = 0;
    int sensor_value = 0;
    int *pmsg_type = (int*)data;

    sensor_value = m_pSensorOpt->get_NoiseValue();
    do_Response_payload(errorno, *pmsg_type, (char*)&sensor_value, sizeof(int));
    cout << "request noise value:" << sensor_value << endl;
}

/* 请求CO2传感器数值
 *
 */
void CServerHandler::do_ReqCO2Value(char *data)
{
    int errorno = 0;
    int sensor_value = 0;
    int *pmsg_type = (int*)data;

    sensor_value = m_pSensorOpt->get_CO2Value();
    do_Response_payload(errorno, *pmsg_type, (char*)&sensor_value, sizeof(int));
    cout << "request CO2 value:" << sensor_value << endl;
}
