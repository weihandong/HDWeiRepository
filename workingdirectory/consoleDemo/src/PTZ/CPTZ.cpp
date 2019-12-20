#include <string.h>
#include "public.h"
#include "CPTZ.h"
#include <stdio.h>
int g_Errorno = 0;

/*	设置错误码
 *
 */
void set_Errorno(void)
{
    int errorno = 0;

    errorno =  NET_DVR_GetLastError();
    printf("set errorno:%d \r\n", errorno);
    g_Errorno = errorno;
}

/*	获取错误码
 *
 */
int get_PTZErrorno(void)
{
    int errorno;

    errorno = g_Errorno;
    g_Errorno = 0;

    return errorno;
}

CPTZ::CPTZ()
{
	m_lUserId = -1;
	m_lRealPlayHandle = -1;
	m_pPTZRealPlay = NULL;
	m_pPTZControl = NULL;
	
	m_pPTZRealPlay = new CPTZRealPlay;
	m_pPTZControl = new CPTZControl;
}

CPTZ::~CPTZ()
{
	if(m_pPTZRealPlay != NULL)
		delete m_pPTZRealPlay;
	if(m_pPTZControl != NULL)
		delete m_pPTZControl;
}

/* device login
 *
 */
 BOOL CPTZ::login_Equipment(char *username,char *password,char *ipaddress, int port)
{
    NET_DVR_Init();

    //Login device
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    struLoginInfo.bUseAsynLogin = false;

    memcpy(struLoginInfo.sUserName, username, NAME_LEN);
    memcpy(struLoginInfo.sPassword, password, NAME_LEN);
    memcpy(struLoginInfo.sDeviceAddress, ipaddress, NET_DVR_DEV_ADDRESS_MAX_LEN);
    struLoginInfo.wPort = port;	
	
    m_lUserId = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (m_lUserId < 0)
    {
        set_Errorno();
        NET_DVR_Cleanup();
        return HPR_ERROR;
    }

/*
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "192.168.31.173", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "sshw1234", NAME_LEN);

    int lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID < 0)
    {
        printf("pyd---Login error, %d\n", NET_DVR_GetLastError());
        NET_DVR_Cleanup();
        return HPR_ERROR;
    }
*/
    long realhandle;
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.lChannel     = 1;  //channel NO
    struPlayInfo.dwLinkMode   = 0;
    struPlayInfo.hPlayWnd = NULL;
    struPlayInfo.bBlocked = 1;
    struPlayInfo.dwDisplayBufNum = 1;
    realhandle = NET_DVR_RealPlay_V40(m_lUserId, &struPlayInfo, NULL, NULL);
    if (realhandle < 0)
    {
		set_Errorno();
        NET_DVR_Cleanup();
        return HPR_ERROR;
    }

    NET_DVR_Cleanup();	

    return HPR_OK;
}

/* device logout
 *
 */
BOOL CPTZ::logout_Equipment(void)
{
    NET_DVR_Init();

    BOOL iRet = NET_DVR_Logout(m_lUserId);
	if (!iRet){
        set_Errorno();
        NET_DVR_Cleanup();
        return HPR_ERROR;
    }
    NET_DVR_Cleanup();
    stop_RealPlay();

    return HPR_OK;
}

/* 开启实时预览
 *
 */
void CPTZ::init_RealPlay(void)
{
	NET_DVR_PREVIEWINFO struPlayInfo = {0};

    struPlayInfo.lChannel   = 1;  //channel NO
    struPlayInfo.dwLinkMode = 0;
    struPlayInfo.hPlayWnd = NULL;
    struPlayInfo.bBlocked = 1;
    struPlayInfo.dwDisplayBufNum = 1;

    NET_DVR_Init();
    m_lRealPlayHandle = NET_DVR_RealPlay_V40(m_lUserId, &struPlayInfo, NULL, NULL);

    if (m_lRealPlayHandle < 0)
    {
		set_Errorno();
        NET_DVR_Cleanup();
        return ;
    }

    NET_DVR_Cleanup();
	init_operateHandle();
}

/* 停止预览
 *
 */
void CPTZ::stop_RealPlay(void)
{
    NET_DVR_Init();
	
    BOOL iRet = NET_DVR_StopRealPlay(m_lRealPlayHandle);
	if (!iRet){
        set_Errorno();
        NET_DVR_Cleanup();
        return ;
    }
    NET_DVR_Cleanup();
}

void CPTZ::init_operateHandle(void)
{
	if(m_pPTZRealPlay != NULL && m_pPTZControl != NULL)
	{
		m_pPTZRealPlay->init_RealPlayInfo(m_lUserId, m_lRealPlayHandle);
		m_pPTZControl->init_RealPlayInfo(m_lUserId, m_lRealPlayHandle);
	}	
}

/*********************************************************************************/
CPTZRealPlay::CPTZRealPlay()
{
	
}

CPTZRealPlay::~CPTZRealPlay()
{
	
}

/* 初始化预览信息
 *
 */
void CPTZRealPlay::init_RealPlayInfo(LONG lUserId, LONG lRealPlayHandle)
{
	if(lUserId < 0 || lRealPlayHandle < 0)
	{
		return ;
	}
	
	m_lUserId = lUserId;
	m_lRealPlayHandle = lRealPlayHandle;	
}

/* 预览抓图
 *
 */
BOOL CPTZRealPlay::do_CapturePicture(char *pFileName)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_SetCapturePictureMode(JPEG_MODE);
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	
	iRet = NET_DVR_CapturePicture(m_lRealPlayHandle, pFileName);
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;	
	
}

/* 预览录像，捕获数据并存放到指定的文件中
 *
 */
BOOL CPTZRealPlay::start_VideoRecording(char *pFileName)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();	
	BOOL iRet = NET_DVR_SaveRealData(m_lRealPlayHandle, pFileName);
		
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

/* 停止录像，停止数据捕获
 *
 */
BOOL CPTZRealPlay::stop_VideoRecording(void)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();	
	BOOL iRet = NET_DVR_StopSaveRealData(m_lRealPlayHandle);
		
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;	
}

/********---------------------------------------------------------------------*********/
CPTZControl::CPTZControl()
{

}

CPTZControl::~CPTZControl()
{

}

/* 初始化预览信息
 *
 */
void CPTZControl::init_RealPlayInfo(LONG lUserId, LONG lRealPlayHandle)
{
	if(lUserId < 0 || lRealPlayHandle < 0)
	{
		return ;
	}
	
	m_lUserId = lUserId;
	m_lRealPlayHandle = lRealPlayHandle;	
}

/* 焦距变大
 *
 */
BOOL CPTZControl::contrl_MvStop(DWORD dwCmd)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, dwCmd, 1);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}
/* 焦距变大
 *
 */
BOOL CPTZControl::contrl_ZoomIn(DWORD dwStop)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, ZOOM_IN, dwStop);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//焦距变小
BOOL CPTZControl::contrl_ZoomOut(DWORD dwStop)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, ZOOM_OUT, dwStop);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//焦点前调
BOOL CPTZControl::contrl_FocusNear(DWORD dwStop)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, FOCUS_NEAR, dwStop);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//焦点前调
BOOL CPTZControl::contrl_FocusFar(DWORD dwStop)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, FOCUS_FAR, dwStop);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//光圈扩大
BOOL CPTZControl::contrl_IrisOpen(DWORD dwStop)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, IRIS_OPEN, dwStop);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//光圈缩小
BOOL CPTZControl::contrl_IrisClose(DWORD dwStop)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControl(m_lRealPlayHandle, IRIS_CLOSE, dwStop);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

/* 云台上仰
 *
 */
BOOL CPTZControl::contrl_TiltUp(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, TILT_UP, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台下俯
BOOL CPTZControl::contrl_TiltDown(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, TILT_DOWN, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台左转
BOOL CPTZControl::contrl_PanLeft(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;
	
	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, PAN_LEFT, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台右转
BOOL CPTZControl::contrl_PanRight(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, PAN_RIGHT, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台上仰和左转
BOOL CPTZControl::contrl_UpLeft(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, UP_LEFT, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台上仰和右转
BOOL CPTZControl::contrl_UpRight(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, UP_RIGHT, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台下俯和左转
BOOL CPTZControl::contrl_DownLeft(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, DOWN_LEFT, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}

//云台下俯和右转
BOOL CPTZControl::contrl_DownRight(DWORD dwStop, DWORD dwSpeed)
{
	BOOL result = HPR_OK;

	NET_DVR_Init();
	BOOL iRet = NET_DVR_PTZControlWithSpeed(m_lRealPlayHandle, DOWN_RIGHT, dwStop, dwSpeed);
	
	if (!iRet){
		set_Errorno();
		result = HPR_ERROR;
	}
	NET_DVR_Cleanup();
	
	return result;
}



