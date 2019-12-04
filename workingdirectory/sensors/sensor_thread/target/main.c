#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <modbus.h>
#include "sensorhandler.h"


extern pthread_t *Sensors_ThreadStart(void);


modbus_t *mb = NULL;

modbus_t *initModbus_RTU(char *pdevpath, uint32_t sec, uint32_t usec)
{
    modbus_t *mb = NULL;

    if(NULL == (mb=modbus_new_rtu(pdevpath, 9600,'N',8, 1)))
    {
         printf("modbus-RTU serial open failed\r\n");
         return NULL;
    }
    
    modbus_set_slave(mb, 1);
    modbus_connect(mb);
    modbus_set_response_timeout(mb, sec, usec);

    return mb;
}

void releaseModbus_RTU(modbus_t *mb)
{
    if(mb == NULL)
         return ;

    modbus_close(mb);
    modbus_free(mb);
}
static void temperature_humidity_initial(void)
{
    mb = initModbus_RTU("/dev/ttyUSB1", 0, 1000000);
}
static void noise_initial(void)
{
    mb = initModbus_RTU("/dev/ttyUSB1", 0, 1000000);
}
static void temperature_humidity_handler(void *data)
{
    uint16_t *tab_reg = (uint16_t*)data;

    modbus_read_registers(mb, 0, 2, tab_reg);
}

static void noise_handler(void *data)
{
    uint16_t *tab_reg = (uint16_t*)data;

    modbus_read_registers(mb, 0, 1, tab_reg);
    printf("read register done\r\n");
}
void *temperature_humidity_thread(void *argv)
{
    struct sensor_t *sensor = (struct sensor_t*)argv;
    struct thread_param_t *parg = (struct thread_param_t*)sensor->thread->argv;
   
    if(parg == NULL)
    {
        return NULL;
    }

    while(1)
    {
        printf("my thread work: %s\r\n",parg->string);
        sensor->handler->func(sensor->handler->data);
        usleep(parg->Sample_rate);
    }
    
    return NULL;
}

void *noise_thread(void *argv)
{
    struct sensor_t *sensor = (struct sensor_t*)argv;
    struct thread_param_t *parg = (struct thread_param_t*)sensor->thread->argv;
   
    if(parg == NULL)
    {
        return NULL;
    }

    while(1)
    {
        printf("my thread work: %s\r\n",parg->string);
        sensor->handler->func(sensor->handler->data);
        usleep(parg->Sample_rate);
    }
    
    return NULL;
}


void sensor_handler3(void *data)
{
    static int i = 20;
    int *pdata = (int*)data;
    *pdata = i++;
}


int main(int argc, char *argv[])
{
    uint16_t th_regs[2] = {0};
    uint16_t noise = 0;
    int sensor3 = 0;
    pthread_t *ptid;
    struct thread_param_t arg;
    arg.Sample_rate = 3000000;
    arg.string = "Hello world";


    initial_sensoritem();
    addto_sensoritem("sensor1", temperature_humidity_thread, (void*)&arg, temperature_humidity_handler, th_regs);
    addto_sensoritem("sensor2", noise_thread, (void*)&arg, noise_handler, &noise);
    addto_sensoritem("sensor3", NULL, NULL, sensor_handler3, &sensor3);
    
    
    temperature_humidity_initial();

    ptid = Sensors_ThreadStart();

    while(1)
    {
        printf("-------------------------\r\n");
        printf("sensor1 data:%d %d\r\n", th_regs[0],th_regs[1]);
        printf("sensor2 data:%d \r\n", noise);
        printf("sensor3 data:%d \r\n", sensor3);
        sleep(2);
    }

    return 0;
}
