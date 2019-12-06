#include "public.h"
#include "Contral.h"
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
int Demo_Contral()
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
    LONG lChannel = 0;
    DWORD uiReturnLen = 0;
    NET_DVR_PRESET_NAME struParams = {0};

    while(1)
    {
        DWORD cur_cmd = -1;
        DWORD last_cmd = -1;
        printf("Contral Input:");

        cin>>cUserChoose;
        switch (cUserChoose)
        {
        case '1':
            last_cmd = cur_cmd = DOWN_LEFT;
            break;
        case '2':
            last_cmd = cur_cmd = TILT_DOWN;
            break;
        case '3':
            last_cmd = cur_cmd = DOWN_RIGHT;
            break;
        case '4':
            last_cmd = cur_cmd = PAN_LEFT;
            break;
        case '5':
            last_cmd = cur_cmd = DOWN_LEFT;
            iRet = NET_DVR_PTZControl(realhandle, last_cmd, 1);
            if (!iRet)
            {
                printf("error, %d\n", NET_DVR_GetLastError());
                return HPR_ERROR;
            }
            continue;
        case '6':
            last_cmd = cur_cmd = PAN_RIGHT;
            break;
        case '7':
            last_cmd = cur_cmd = UP_LEFT;
            break;
		case '8':
            last_cmd = cur_cmd = TILT_UP;
			break;
		case '9':
            last_cmd = cur_cmd = UP_RIGHT;
			break;
		case 'p':
            iRet = NET_DVR_PTZPreset(realhandle, SET_PRESET,i++);
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            continue;
		case 't':
            iRet = NET_DVR_PTZPreset(realhandle,GOTO_PRESET, 2);
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            continue;
		case 'c':
            iRet = NET_DVR_PTZPreset(realhandle, CLE_PRESET,i--);
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            continue;
		case 's':
            struParams.dwSize = sizeof(struParams);
            struParams.wPresetNum = 1;
            strcpy(struParams.byName,"point1");

            NET_DVR_SetDVRConfig(lUserID, NET_DVR_SET_PRESET_NAME, struDeviceInfoV40.struDeviceV30.byStartChan, \
                                 &struParams, sizeof(NET_DVR_PRESET_NAME));
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            continue;
		case 'g':
            iRet = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_PRESET_NAME, struDeviceInfoV40.struDeviceV30.byStartChan, \
                                        &struParams, sizeof(NET_DVR_PRESET_NAME), &uiReturnLen);
            if (!iRet)
            {
                printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_DVR_SYNCHRONOUS_IPC error.%d\n",  NET_DVR_GetLastError());
                NET_DVR_Logout_V30(lUserID);
                NET_DVR_Cleanup();
                return HPR_ERROR;
            }
            cout << "wPresetNum:" << struParams.wPresetNum << endl;
            cout << "byName:" << struParams.byName << endl;
            cout << "wPanPos:" << struParams.wPanPos << endl;
            cout << "wTiltPos:" << struParams.wTiltPos << endl;
            cout << "wZoomPos:" << struParams.wZoomPos << endl;

            continue;
        default:
            break;
        }
        
        //iRet = NET_DVR_PTZControl(realhandle, cur_cmd, 0);
        iRet = NET_DVR_PTZControlWithSpeed(realhandle, cur_cmd, 0, 2);
        if (!iRet)
        {
            printf("error, %d\n", NET_DVR_GetLastError());
            return HPR_ERROR;
        }
    }

    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return HPR_OK;

}
