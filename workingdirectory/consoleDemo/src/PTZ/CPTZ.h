#ifndef _CPTZ_H
#define _CPTZ_H

#include "public.h"

//实时预览属性(类)
class CPTZRealPlay{
private:
	LONG 	m_lUserId;
	LONG	m_lRealPlayHandle;
public:
	CPTZRealPlay();
	~CPTZRealPlay();
	//初始化预览信息
	void init_RealPlayInfo(LONG m_lUserId, LONG lRealPlayHandle);
	//预览抓图
	BOOL do_CapturePicture(char *pFileName);
	//预览录像，捕获数据并存放到指定的文件中
	BOOL start_VideoRecording(char *pFileName);
	//停止录像，停止数据捕获。
	BOOL stop_VideoRecording(void);
};

//云台控制属性(类)
class CPTZControl{
private:
	LONG 	m_lUserId;
	LONG	m_lRealPlayHandle;
public:
    CPTZControl();
    ~CPTZControl();

    //初始化预览信息
	void init_RealPlayInfo(LONG m_lUserId, LONG lRealPlayHandle);
    //停止
	BOOL contrl_MvStop(DWORD dwCmd);

    //焦距变大
	BOOL contrl_ZoomIn(DWORD dwStop);
	//焦距变小
	BOOL contrl_ZoomOut(DWORD dwStop);
	//焦点前调
	BOOL contrl_FocusNear(DWORD dwStop);
	//焦点前调
	BOOL contrl_FocusFar(DWORD dwStop);
	//光圈扩大
	BOOL contrl_IrisOpen(DWORD dwStop);
	//光圈缩小
	BOOL contrl_IrisClose(DWORD dwStop);

    //云台上仰
	BOOL contrl_TiltUp(DWORD dwStop, DWORD dwSpeed);
	//云台下俯
	BOOL contrl_TiltDown(DWORD dwStop, DWORD dwSpeed);
	//云台左转
	BOOL contrl_PanLeft(DWORD dwStop, DWORD dwSpeed);
	//云台右转
	BOOL contrl_PanRight(DWORD dwStop, DWORD dwSpeed);
	//云台上仰和左转
	BOOL contrl_UpLeft(DWORD dwStop, DWORD dwSpeed);
	//云台上仰和右转
	BOOL contrl_UpRight(DWORD dwStop, DWORD dwSpeed);
	//云台下俯和左转
	BOOL contrl_DownLeft(DWORD dwStop, DWORD dwSpeed);
	//云台下俯和右转
	BOOL contrl_DownRight(DWORD dwStop, DWORD dwSpeed);
	
	//云台设置预置点方法
	
	//云台巡航方法
};


//云台类
class CPTZ{
public:
    CPTZ();
    ~CPTZ();
	//device login
	BOOL login_Equipment(char *username,char *password,char *ipaddress, int port);
	//device logout
	BOOL logout_Equipment(void);
	//开启实时预览
	void init_RealPlay(void);
	//停止预览。
	void stop_RealPlay(void);

	CPTZRealPlay *m_pPTZRealPlay;
	CPTZControl *m_pPTZControl;
private:
	LONG 	m_lUserId;
	LONG	m_lRealPlayHandle;
	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;

	//初始化操作句柄
	void init_operateHandle(void);
};

int get_PTZErrorno(void);

#endif
