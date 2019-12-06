/*
 * Copyright(C) 2010,Hikvision Digital Technology Co., Ltd 
 * 
 * �ļ����ƣ�public.h
 * ��    ����
 * ��ǰ�汾��1.0
 * ��    �ߣ����Ƕ�
 * �������ڣ�2010��3��25��
 * �޸ļ�¼��
 */


#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#define  HPR_OK 0
#define  HPR_ERROR -1


#include "../include/HCNetSDK.h"

#define COMMAND_MAX_LEN     20

#define USERNAME_MAX_LEN    20
#define PASSWORD_MAX_LEN    45
#define IPADDRESS_MAX_LEN   16
#define PORTNO_MAX_LEN      6

typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char ipaddress[IPADDRESS_MAX_LEN];
    char portno[PORTNO_MAX_LEN];
}loginfo_t;

typedef struct {
    char active[COMMAND_MAX_LEN];
    char *loginfo;
}log_params_t;

typedef struct {
    char active[COMMAND_MAX_LEN];
}contrl_params_t;

#endif
