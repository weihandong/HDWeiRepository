#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "servereq.h"


extern void req(void);

struct req_handler_t {
	void (*func)(void * data);
	void * data;
};

struct req_t {
	/* 请求操作名称 */
	const char * name;
	/* 请求号 */
	const int req_no;
	/* 请求处理函数 */
	struct req_handler_t * handler;
	/* 使能请求 */
	void (*enable)(struct req_t * req, bool enable);
};

#define ARRAY_SIZE(array)   ( sizeof(array) / sizeof((array)[0]) )

static struct req_handler_t req_handler[128];
//暂时不需要处理的
static void null_request_function(void *data){}

static uint32_t req_offset(uint32_t x)
{
	uint32_t index = x;

	return (index);
}

void do_reqs(const int reqno)
{
	uint32_t offset;

	if(reqno >= 0 && reqno < 32)
	{
		offset = req_offset(reqno - 0);
		(req_handler[offset].func)(req_handler[offset].data);
	}
	else if(reqno >= 32 && reqno < 64)
	{
		offset = req_offset(reqno - 32);
		(req_handler[offset + 32].func)(req_handler[offset + 32].data);
	}
	else if(reqno >= 64 && reqno < 96)
	{
		offset = req_offset(reqno - 64);
		(req_handler[offset + 64].func)(req_handler[offset + 64].data);
	}
	else if(reqno >= 96 && reqno < 128)
	{
		offset = req_offset(reqno - 96);
		(req_handler[offset + 96].func)(req_handler[offset + 96].data);
	}
	else
	{

	}
}


static void enable_reqs(struct req_t *req, bool enable)
{
    uint32_t req_no = req->req_no;
}

/*
 * the array of req.
 */
static struct req_t implement_reqs[] = {
	{
		.name		= "req1",
		.req_no		= 0,
		.handler	= &req_handler[0],
		.enable		= enable_reqs,
	}, {
		.name		= "req2",
		.req_no		= 1,
		.handler	= &req_handler[1],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT2",
		.req_no		= 2,
		.handler	= &req_handler[2],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT3",
		.req_no		= 3,
		.handler	= &req_handler[3],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT4",
		.req_no		= 4,
		.handler	= &req_handler[4],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT5",
		.req_no		= 5,
		.handler	= &req_handler[5],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT6",
		.req_no		= 6,
		.handler	= &req_handler[6],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT7",
		.req_no		= 7,
		.handler	= &req_handler[7],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT8",
		.req_no		= 8,
		.handler	= &req_handler[8],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT9",
		.req_no		= 9,
		.handler	= &req_handler[9],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT10",
		.req_no		= 10,
		.handler	= &req_handler[10],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT11",
		.req_no		= 11,
		.handler	= &req_handler[11],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT12",
		.req_no		= 12,
		.handler	= &req_handler[12],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT13",
		.req_no		= 13,
		.handler	= &req_handler[13],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT14",
		.req_no		= 14,
		.handler	= &req_handler[14],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT15",
		.req_no		= 15,
		.handler	= &req_handler[15],
		.enable		= enable_reqs,
	}, {
		.name		= "EINT16_31",
		.req_no		= 16,
		.handler	= &req_handler[16],
		.enable		= enable_reqs,
	}, {
		.name		= "MDMA",
		.req_no		= 18,
		.handler	= &req_handler[18],
		.enable		= enable_reqs,
	}, {
		.name		= "PDMA0",
		.req_no		= 19,
		.handler	= &req_handler[19],
		.enable		= enable_reqs,
	}, {
		.name		= "PDMA1",
		.req_no		= 20,
		.handler	= &req_handler[20],
		.enable		= enable_reqs,
	}, {
		.name		= "TIMER0",
		.req_no		= 21,
		.handler	= &req_handler[21],
		.enable		= enable_reqs,
	}, {
		.name		= "TIMER1",
		.req_no		= 22,
		.handler	= &req_handler[22],
		.enable		= enable_reqs,
	}, {
		.name		= "TIMER2",
		.req_no		= 23,
		.handler	= &req_handler[23],
		.enable		= enable_reqs,
	}, {
		.name		= "TIMER3",
		.req_no		= 24,
		.handler	= &req_handler[24],
		.enable		= enable_reqs,
	}, {
		.name		= "TIMER4",
		.req_no		= 25,
		.handler	= &req_handler[25],
		.enable		= enable_reqs,
	}, {
		.name		= "SYSTEM_TMIER",
		.req_no		= 26,
		.handler	= &req_handler[26],
		.enable		= enable_reqs,
	}, {
		.name		= "WDT",
		.req_no		= 27,
		.handler	= &req_handler[27],
		.enable		= enable_reqs,
	}, {
		.name		= "RTC_ALARM",
		.req_no		= 28,
		.handler	= &req_handler[28],
		.enable		= enable_reqs,
	}, {
		.name		= "RTC_TIC",
		.req_no		= 29,
		.handler	= &req_handler[29],
		.enable		= enable_reqs,
	}, {
		.name		= "GPIOINT",
		.req_no		= 30,
		.handler	= &req_handler[30],
		.enable		= enable_reqs,
	}, {
		.name		= "FIMC3",
		.req_no		= 31,
		.handler	= &req_handler[31],
		.enable		= enable_reqs,
	}, {
		.name		= "CORTEX0",
		.req_no		= 32,
		.handler	= &req_handler[32],
		.enable		= enable_reqs,
	}, {
		.name		= "CORTEX1",
		.req_no		= 33,
		.handler	= &req_handler[33],
		.enable		= enable_reqs,
	}, {
		.name		= "CORTEX2",
		.req_no		= 34,
		.handler	= &req_handler[34],
		.enable		= enable_reqs,
	}, {
		.name		= "CORTEX3",
		.req_no		= 35,
		.handler	= &req_handler[35],
		.enable		= enable_reqs,
	}, {
		.name		= "CORTEX4",
		.req_no		= 36,
		.handler	= &req_handler[36],
		.enable		= enable_reqs,
	}, {
		.name		= "IEM_APC",
		.req_no		= 37,
		.handler	= &req_handler[37],
		.enable		= enable_reqs,
	}, {
		.name		= "IEM_IEC",
		.req_no		= 38,
		.handler	= &req_handler[38],
		.enable		= enable_reqs,
	}, {
		.name		= "NFC",
		.req_no		= 40,
		.handler	= &req_handler[40],
		.enable		= enable_reqs,
	}, {
		.name		= "CFC",
		.req_no		= 41,
		.handler	= &req_handler[41],
		.enable		= enable_reqs,
	}, {
		.name		= "UART0",
		.req_no		= 42,
		.handler	= &req_handler[42],
		.enable		= enable_reqs,
	}, {
		.name		= "UART1",
		.req_no		= 43,
		.handler	= &req_handler[43],
		.enable		= enable_reqs,
	}, {
		.name		= "UART2",
		.req_no		= 44,
		.handler	= &req_handler[44],
		.enable		= enable_reqs,
	}, {
		.name		= "UART3",
		.req_no		= 45,
		.handler	= &req_handler[45],
		.enable		= enable_reqs,
	}, {
		.name		= "I2C0",
		.req_no		= 46,
		.handler	= &req_handler[46],
		.enable		= enable_reqs,
	}, {
		.name		= "SPI0",
		.req_no		= 47,
		.handler	= &req_handler[47],
		.enable		= enable_reqs,
	}, {
		.name		= "SPI1",
		.req_no		= 48,
		.handler	= &req_handler[48],
		.enable		= enable_reqs,
	}, {
		.name		= "AUDIO_SS",
		.req_no		= 50,
		.handler	= &req_handler[50],
		.enable		= enable_reqs,
	}, {
		.name		= "I2C2",
		.req_no		= 51,
		.handler	= &req_handler[51],
		.enable		= enable_reqs,
	}, {
		.name		= "I2C_HDMI_PHY",
		.req_no		= 52,
		.handler	= &req_handler[52],
		.enable		= enable_reqs,
	}, {
		.name		= "UHOST",
		.req_no		= 55,
		.handler	= &req_handler[55],
		.enable		= enable_reqs,
	}, {
		.name		= "OTG",
		.req_no		= 56,
		.handler	= &req_handler[56],
		.enable		= enable_reqs,
	}, {
		.name		= "MODEMIF",
		.req_no		= 57,
		.handler	= &req_handler[57],
		.enable		= enable_reqs,
	}, {
		.name		= "HSMMC0",
		.req_no		= 58,
		.handler	= &req_handler[58],
		.enable		= enable_reqs,
	}, {
		.name		= "HSMMC1",
		.req_no		= 59,
		.handler	= &req_handler[59],
		.enable		= enable_reqs,
	}, {
		.name		= "HSMMC2",
		.req_no		= 60,
		.handler	= &req_handler[60],
		.enable		= enable_reqs,
	}, {
		.name		= "MIPI_CSI",
		.req_no		= 61,
		.handler	= &req_handler[61],
		.enable		= enable_reqs,
	}, {
		.name		= "MIPI_DSI",
		.req_no		= 62,
		.handler	= &req_handler[62],
		.enable		= enable_reqs,
	}, {
		.name		= "ONENAND_AUDI",
		.req_no		= 63,
		.handler	= &req_handler[63],
		.enable		= enable_reqs,
	}, {
		.name		= "LCD0",
		.req_no		= 64,
		.handler	= &req_handler[64],
		.enable		= enable_reqs,
	}, {
		.name		= "LCD1",
		.req_no		= 65,
		.handler	= &req_handler[65],
		.enable		= enable_reqs,
	}, {
		.name		= "LCD2",
		.req_no		= 66,
		.handler	= &req_handler[66],
		.enable		= enable_reqs,
	}, {
		.name		= "ROTATOR",
		.req_no		= 68,
		.handler	= &req_handler[68],
		.enable		= enable_reqs,
	}, {
		.name		= "FIMC0",
		.req_no		= 69,
		.handler	= &req_handler[69],
		.enable		= enable_reqs,
	}, {
		.name		= "FIMC1",
		.req_no		= 70,
		.handler	= &req_handler[70],
		.enable		= enable_reqs,
	}, {
		.name		= "FIMC2",
		.req_no		= 71,
		.handler	= &req_handler[71],
		.enable		= enable_reqs,
	}, {
		.name		= "JPEG",
		.req_no		= 72,
		.handler	= &req_handler[72],
		.enable		= enable_reqs,
	}, {
		.name		= "2D",
		.req_no		= 73,
		.handler	= &req_handler[73],
		.enable		= enable_reqs,
	}, {
		.name		= "3D",
		.req_no		= 74,
		.handler	= &req_handler[74],
		.enable		= enable_reqs,
	}, {
		.name		= "MIXER",
		.req_no		= 75,
		.handler	= &req_handler[75],
		.enable		= enable_reqs,
	}, {
		.name		= "HDMI",
		.req_no		= 76,
		.handler	= &req_handler[76],
		.enable		= enable_reqs,
	}, {
		.name		= "I2C_HDMI_DDC",
		.req_no		= 77,
		.handler	= &req_handler[77],
		.enable		= enable_reqs,
	}, {
		.name		= "MFC",
		.req_no		= 78,
		.handler	= &req_handler[78],
		.enable		= enable_reqs,
	}, {
		.name		= "TVENC",
		.req_no		= 79,
		.handler	= &req_handler[79],
		.enable		= enable_reqs,
	}, {
		.name		= "I2S0",
		.req_no		= 80,
		.handler	= &req_handler[80],
		.enable		= enable_reqs,
	}, {
		.name		= "I2S1",
		.req_no		= 81,
		.handler	= &req_handler[81],
		.enable		= enable_reqs,
	}, {
		.name		= "AC97",
		.req_no		= 83,
		.handler	= &req_handler[83],
		.enable		= enable_reqs,
	}, {
		.name		= "PCM0",
		.req_no		= 84,
		.handler	= &req_handler[84],
		.enable		= enable_reqs,
	}, {
		.name		= "PCM1",
		.req_no		= 85,
		.handler	= &req_handler[85],
		.enable		= enable_reqs,
	}, {
		.name		= "SPDIF",
		.req_no		= 86,
		.handler	= &req_handler[86],
		.enable		= enable_reqs,
	}, {
		.name		= "ADC",
		.req_no		= 87,
		.handler	= &req_handler[87],
		.enable		= enable_reqs,
	}, {
		.name		= "PENDN",
		.req_no		= 88,
		.handler	= &req_handler[88],
		.enable		= enable_reqs,
	}, {
		.name		= "KEYPAD",
		.req_no		= 89,
		.handler	= &req_handler[89],
		.enable		= enable_reqs,
	}, {
		.name		= "INTHASH_SSS",
		.req_no		= 91,
		.handler	= &req_handler[91],
		.enable		= enable_reqs,
	}, {
		.name		= "INTFEEDCTRL_SSS",
		.req_no		= 92,
		.handler	= &req_handler[92],
		.enable		= enable_reqs,
	}, {
		.name		= "PCM2",
		.req_no		= 93,
		.handler	= &req_handler[93],
		.enable		= enable_reqs,
	}, {
		.name		= "SDM_req",
		.req_no		= 94,
		.handler	= &req_handler[94],
		.enable		= enable_reqs,
	}, {
		.name		= "SDM_FIQ",
		.req_no		= 95,
		.handler	= &req_handler[95],
		.enable		= enable_reqs,
	}, {
		.name		= "MMC3",
		.req_no		= 98,
		.handler	= &req_handler[98],
		.enable		= enable_reqs,
	}, {
		.name		= "CEC",
		.req_no		= 99,
		.handler	= &req_handler[99],
		.enable		= enable_reqs,
	}, {
		.name		= "TSI",
		.req_no		= 100,
		.handler	= &req_handler[100],
		.enable		= enable_reqs,
	}, {
		.name		= "ADC1",
		.req_no		= 105,
		.handler	= &req_handler[105],
		.enable		= enable_reqs,
	}, {
		.name		= "PENDN1",
		.req_no		= 106,
		.handler	= &req_handler[106],
		.enable		= enable_reqs,
	}
};

void request_initial(void)
{
	for(int i = 0; i < ARRAY_SIZE(implement_reqs); i++)
	{
		implement_reqs[i].handler->func = null_request_function;
		implement_reqs[i].handler->data = NULL;
	}
}

//添加请求项
bool addto_reqitem(const char * name, request_function_t func, void * data)
{
	struct req_t * req = NULL;
	int i;

	if(!name || !func)
		return false;

	for(i=0; i< ARRAY_SIZE(implement_reqs); i++)
	{
		if(strcmp(implement_reqs[i].name, name) == 0)
		{
            printf("add <%s> into implement_reqs table \r\n", name);
            req = &implement_reqs[i];
			break;
		}
	}
	if(!req)
		return false;

	if(req->handler->func != null_request_function)
		return false;

	req->handler->func = func;
	req->handler->data = data;

	if(req->enable)
		req->enable(req, true);

	return false;
}

//删除请求项
bool remove_reqitem(const char * name)
{
	struct req_t * req = NULL;
	int i;

	if(!name)
		return false;

	for(i=0; i< ARRAY_SIZE(implement_reqs); i++)
	{
		//查找要删除的请求事件
		if(strcmp(implement_reqs[i].name, name) == 0)
		{
            printf("remove <%s> from implement_reqs table \r\n", name);
			req = &implement_reqs[i];
			break;
		}
	}
	if(!req)
		return false;

	req->handler->func = null_request_function;
	req->handler->data = NULL;

	if(req->enable)
		req->enable(req, false);

	return true;
}
