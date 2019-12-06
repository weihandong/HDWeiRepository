#include "public.h"
#include "PTZPCruise.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

/*******************************************************************
      Function:   Demo_Capture
   Description:   Capture picture.
     Parameter:   (IN)   none 
        Return:   0--success��-1--fail.   
**********************************************************************/
int Demo_PTZPCruise(void)
{
    NET_DVR_Init();
    long lUserID;
    //login
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "192.168.31.173", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "sshw1234", NAME_LEN);

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID < 0)
    {
        printf("pyd1---Login error, %d\n", NET_DVR_GetLastError());
        return HPR_ERROR;
    }


    long realhandle;
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

    cout <<"pyd1---Login successed-======================================" << endl;
    //
    char cUserChoose = 'r';
    static int i = 1;
    int iRet = -1;

    while(1)
    {
        printf("Contral Input:");

        cin>>cUserChoose;
        switch (cUserChoose)
        {
		case 'c'://将预置点加入巡航序列
            iRet = NET_DVR_PTZCruise(realhandle, RUN_SEQ, i, i, i);   
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            iRet = NET_DVR_PTZCruise(realhandle, SET_SEQ_DWELL, i, i, 10);   
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
		    //设置巡航速度
            iRet = NET_DVR_PTZCruise(realhandle, SET_SEQ_SPEED,i,i,30);   
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            break;
		case 'd'://将预置点从巡航序列中删除
            iRet = NET_DVR_PTZCruise(realhandle, CLE_PRE_SEQ, i, i, i);   
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            break;
        case 'p':
            i -= 1;
            if(i == 0)
                i = 1;
            cout << "point:" << i << endl;
            break;
        case 'n':
            i += 1;
            if(i >= 32)
                i = 32;
            cout << "point:" << i << endl;
            break;
		case 'r':
            iRet = NET_DVR_PTZCruise(realhandle, RUN_SEQ,i,i,i);   
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            break;
		case 's':
            iRet = NET_DVR_PTZCruise(realhandle, STOP_SEQ,i,i,i);   
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            break;
        default:
            NET_DVR_Logout_V30(lUserID);
            NET_DVR_Cleanup();
            return HPR_OK;
        }
    }

    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return HPR_OK;

}
