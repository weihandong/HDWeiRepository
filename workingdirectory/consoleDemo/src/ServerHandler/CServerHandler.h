#ifndef _CSERVER_HANDLER_H
#define _CSERVER_HANDLER_H

typedef int PackdefType;

#define ENABLE     0
#define DISENABLE  1


class CPTZ;
class CExecAction;
class CSensorOpt;
class CServerHandler;


struct ProtocolMap
{
    int  m_ntype;
    void (CServerHandler::*func)(char *data);
};

#define BEGIN_PROTOCOL_MAP static const ProtocolMap ProtocolMapEntries[] = \
{
#define END_PROTOCOL_MAP    {0,0},\
};

class CServerHandler{
public:
	CServerHandler();
	~CServerHandler();

private:
    int m_rcvMsgid;
    int m_sedMsgid;
    int m_deviceId;
    DWORD m_dwlastCmd;
    DWORD m_dwSpeed;
    CPTZ *m_pPtz;
    CSensorOpt *m_pSensorOpt;
	CExecAction *m_pCExecAction;
protected:	
	char *get_Rawdata(char *pdata);
	void do_Response_Nopayload(int errorno, int msg_type);
	void do_Response_payload(int errorno, int msg_type, char *payload, int len);
	
public:
	void msgProcPoll();
	void dealwith_Handler(char *data);

	void do_ReqLogin(char *data);
	void do_ReqLogout(char *data);

    void do_ReqMvStop(char *data);
    void do_ReqUpLeft(char *data);
    void do_ReqUpRight(char *data);
    void do_ReqDownLeft(char *data);
    void do_ReqDownRight(char *data);
    void do_ReqTiltUp(char *data);
    void do_ReqTiltDown(char *data);
    void do_ReqPanLeft(char *data);
    void do_ReqPanRight(char *data);
    void do_ReqSpeedOpt(char *data);
    //焦距变大
    void do_ReqZoomIn(char *data);
    //焦距变小
    void do_ReqZoomOut(char *data);
    //焦点前调
    void do_ReqFocusNear(char *data);
    //焦点前调
    void do_ReqFocusFar(char *data);
    //光圈扩大
    void do_ReqIrisOpen(char *data);
    //光圈缩小
    void do_ReqIrisClose(char *data);

	//预览抓图
	void do_ReqCapturePicture(char *data);
	//预览录像，捕获数据并存放到指定的文件中
    void do_ReqStartVideoRecord(char *data);
	//停止录像，停止数据捕获。
	void do_ReqStopVideoRecord(char *data);

    /******************************************/
    void do_ReqTemperatureValue(char *data);
    void do_ReqHumidityValue(char *data);
    void do_ReqNoiseValue(char *data);
    void do_ReqCO2Value(char *data);
};

#endif
