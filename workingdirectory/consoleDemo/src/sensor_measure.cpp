#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "sensorhandler.h"
#include "sensor_measure.h"


extern "C"
{
#include "modbus.h"
}


extern void sensors_poll(void);
modbus_t *mb1 = NULL;
modbus_t *mb2 = NULL;

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif



modbus_t *initModbus_RTU(char *pdevpath, uint32_t sec, uint32_t usec)
{
    modbus_t *mb = NULL;

    //1-打开端口
    if(NULL == (mb=modbus_new_rtu(pdevpath, 9600,'N',8, 1)))
    {
#ifdef DEBUG
         cout << "modbus-RTU serial open failed" << endl;
#endif
         return NULL;
    }
    
    //2-设置从地址
    modbus_set_slave(mb, 1);

    //3-建立连接
    modbus_connect(mb);

    //4-设置应答延时
    modbus_set_response_timeout(mb, sec, usec);

    return mb;
}

void releaseModbus_RTU(modbus_t *mb)
{
    if(mb == NULL)
         return ;

    //7-关闭modbus端口
    modbus_close(mb);
    //8-释放modbus资源
    modbus_free(mb);
}

//温湿度传感器初始化
static void temperature_humidity_initial(void)
{
    mb1 = initModbus_RTU("/dev/ttyUSB0", 0, 1000000);
    if(mb1)
    {
#ifdef DEBUG
        cout << "mb1 open successed" << endl;
#endif
    }
}
//噪声传感器初始化
static void noise_initial(void)
{
    mb2 = initModbus_RTU("/dev/ttyUSB1", 0, 1000000);
    if(mb2)
    {
#ifdef DEBUG
        cout << "mb2 open successed" << endl;
#endif
    }
}
//温湿度传感器处理函数
static void temperature_humidity_handler(void *data)
{
    uint16_t *tab_reg = (uint16_t*)data;

    //6-读寄存器设置：寄存器地址、数量、数据缓冲
    modbus_read_registers(mb1, 0, 2, tab_reg);
}

static void noise_handler(void *data)
{
    uint16_t *tab_reg = (uint16_t*)data;

    //6-读寄存器设置：寄存器地址、数量、数据缓冲
    modbus_read_registers(mb2, 0, 1, tab_reg);
}


sensor_value_t g_sensors;

void Demo_SensorsMeasure(void)
{
    uint16_t tab_reg[2] = {0};
    uint16_t noise = 0;

    initial_sensoritem();
    addto_sensoritem("temperature-humidity", temperature_humidity_initial, temperature_humidity_handler, tab_reg);
    addto_sensoritem("noise-humidity", noise_initial, noise_handler, &noise);
    sensors_initial();
    printf(" start........ \r\n ");
    //5-循环读
    while(1)
    {   
        sensors_poll();
       
        g_sensors.temperature_value = tab_reg[0];
        g_sensors.humidity_value = tab_reg[1];
        g_sensors.noise_value = noise;

        printf("%d,%d,%d \r\n",tab_reg[0],tab_reg[1],noise);
        sleep(2);
    }

    releaseModbus_RTU(mb1);
    releaseModbus_RTU(mb2);
}

