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
#include <stdio.h>
#include "CServerHandler.h"
#include <iostream>

using namespace std;

int main()
{
    char cUserChoose;
	CServerHandler *pCServerHandler = new CServerHandler(); 

    NET_DVR_Init();
/*    
    //Login device
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "192.168.31.73", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "sshw1234", NAME_LEN);

    int lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (lUserID < 0)
    {
        printf("pyd---Login error, %d\n", NET_DVR_GetLastError());
        printf("Press any key to quit...\n");
        cin>>cUserChoose;

        NET_DVR_Cleanup();
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

    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();
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
            //Demo_GetStream_V30(g_userID); //Get stream.
            break;
        case '2':
            //Demo_ConfigParams(g_userID);  //Setting params.
            break;
        case '3':
            Demo_Alarm();         //Alarm & listen.
            break;
        case '4':
            Demo_Capture();
            break;
        case '5':
            //Demo_PlayBack(g_userID);     //record & playback
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
            pCServerHandler->msgProcPoll();
			break;
        default:
            break;
        }
    }

    return 0;
}

