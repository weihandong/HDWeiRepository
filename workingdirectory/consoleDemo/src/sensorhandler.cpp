#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sensorhandler.h"


//传感器初始化结构体
struct sensor_initial_t
{
	void (*func)(void);
};
//传感器采集结构体
struct sensor_handler_t
{
	void (*func)(void *data);
	void *data;
};



struct sensor_t 
{
	/* 传感器名称 */
	char * name;
	/* 传感器编号，可能同时存在多个相同传感器 */
	int sensor_no;
	/* 传感器初始化函数 */
	struct sensor_initial_t *initial;
	/* 传感器采集函数 */
	struct sensor_handler_t *handler;
    /* 是否启用传感器 */
    void (*enable)(const int sensorno, bool enable);
    bool sensor_enable;
};

#define SENSORNO_NUM           ( 32 )
#define ARRAY_SIZE(array)   ( sizeof(array) / sizeof((array)[0]) )

static struct sensor_t g_implement_sensors[SENSORNO_NUM] = {0};
static struct sensor_initial_t g_sensor_initial[SENSORNO_NUM];
static struct sensor_handler_t g_sensor_handler[SENSORNO_NUM];


int fd_to_sensorno(int sensorno);
void enable_sensors(const int sensorno, bool enable);



static bool isenable(int index)
{
    return g_implement_sensors[index].sensor_enable == true ? true : false ;
}

static int count_sensors(struct sensor_t *sensor)
{
	int i = 0;
	
	if(!sensor)
		return 0;
	
	for(i=0; i < SENSORNO_NUM; i ++)
	{
		if(-1 == sensor[i].sensor_no)
			break;
	}
	
	return i;
}

void sensors_initial(void)
{
	uint32_t count;

	count = count_sensors(g_implement_sensors);

	for(unsigned int i=0; i<count; i++)
	{
        if(isenable(i))
		    (g_sensor_initial[i].func)();
	}
}

void sensors_poll(void)
{
	uint32_t count;

	count = count_sensors(g_implement_sensors);
	
	for(unsigned int i=0; i<count; i++)
	{
        if(isenable(i))
    		(g_sensor_handler[i].func)(g_sensor_handler[i].data);
    }
}




/***********************************************************************************/

void enable_sensors(const int sensorno, bool enable)
{
    int sensor_no = -1;
    
    sensor_no = fd_to_sensorno(sensorno);
    if(sensor_no < 0 || sensor_no > SENSORNO_NUM)
        return ;

    if(g_implement_sensors[sensor_no].sensor_enable != enable)
        g_implement_sensors[sensor_no].sensor_enable = enable;
}

int fd_to_sensorno(int sensorno)
{
    int sensorno_id;

    for (sensorno_id = 0; sensorno_id < SENSORNO_NUM; sensorno_id++) 
    {
        if (g_implement_sensors[sensorno_id].sensor_no == sensorno) 
        {
            break;
        }
    }

    return sensorno_id;
}


void initial_sensoritem(void)
{
    unsigned int i;

	for(i=0; i < ARRAY_SIZE(g_implement_sensors); i++)
	{
        g_implement_sensors[i].name = NULL;
        g_implement_sensors[i].sensor_no = -1;
		g_implement_sensors[i].initial = &g_sensor_initial[i];
		g_implement_sensors[i].handler = &g_sensor_handler[i];
        g_implement_sensors[i].enable = enable_sensors;
        g_implement_sensors[i].sensor_enable = false; 
	}
}

/***************************************************************************************************************/
void add_sensoritem(struct sensor_t *sensor, const char *name, sensorinitial_func_t initial, sensorhandler_func_t handler, void *data)
{
	if(!sensor)
		return ;
		
    int len = strlen(name) + 1;
    sensor->name = (char*)malloc(len);
    if(sensor->name == NULL)
        return ;
    memcpy(sensor->name, name, len);

	if(sensor->initial->func != NULL)
        return ;

	if(sensor->handler->func != NULL)
		return ;
	
	//绑定传感器初始化函数
	sensor->initial->func = initial;
	//绑定传感器采集函数
	sensor->handler->func = handler;
	sensor->handler->data = data;

    if(sensor->enable)
        sensor->enable(sensor->sensor_no, true);
}


//添加传感器采集函数
bool addto_sensoritem(const char *name, sensorinitial_func_t initial,sensorhandler_func_t handler, void *data)
{
	struct sensor_t *sensor = NULL;
    int sensorno_id;
	unsigned int i;

	if(!name || !initial || !handler)
		return false;

	for(i=0; i< ARRAY_SIZE(g_implement_sensors); i++)
    {
        if(g_implement_sensors[i].name == NULL) 
            break;
		if(strcmp(g_implement_sensors[i].name, name) == 0)
            return false;
    }

    for (sensorno_id = 0; sensorno_id < SENSORNO_NUM; sensorno_id++) 
    {
        if(g_implement_sensors[sensorno_id].sensor_no >= 0) 
        {
            continue;
        }
        g_implement_sensors[sensorno_id].sensor_no = sensorno_id;
        sensor = &g_implement_sensors[sensorno_id];
        break;
    }

	if(!sensor)
		return false;

	add_sensoritem(sensor, name, initial, handler, data);
    printf("addto <%s> into g_implement_sensors table \r\n", sensor->name);
	
	return true;
}

/******************************************************************************************/
void clean_sensoritem(struct sensor_t *sensor)
{
	if(!sensor)
		return ;
	
	free(sensor->name);
    sensor->name = NULL;
    sensor->sensor_no = -1;
	sensor->initial->func = NULL;
	sensor->handler->func = NULL;
	sensor->handler->data = 0;

    if(sensor->enable)
        sensor->enable(sensor->sensor_no, false);
}

//删除传感器
bool remove_sensoritem(char *name)
{
	struct sensor_t *sensor = NULL;
	unsigned int i;

	if(!name)
		return false;

	for(i=0; i< ARRAY_SIZE(g_implement_sensors); i++)
	{
		//查找要删除的请求事件
		if(strcmp(g_implement_sensors[i].name, name) == 0)
		{
            printf("remove <%s> from g_implement_sensors table \r\n", name);
			sensor = &g_implement_sensors[i];
			break;
		}
	}
	if(!sensor)
		return false;
	
	clean_sensoritem(sensor);

	return true;
}




