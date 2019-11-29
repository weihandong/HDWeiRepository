#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "sensorhandler.h"


extern pthread_t *Sensors_ThreadStart(void);


void *sensor_thread1(void *argv)
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


void sensor_initial1(void *data)
{
    printf("sensor1 initial \r\n");
}


void sensor_initial2(void *data)
{
    printf("sensor1 initial \r\n");
}

void sensor_initial3(void *data)
{
    printf("sensor3 initial \r\n");
}

void sensor_handler1(void *data)
{
    static int i = 0;
    int *pdata = (int*)data;
    *pdata = i++;
}

void sensor_handler2(void *data)
{
    static int i = 10;
    int *pdata = (int*)data;
    *pdata = i++;
}

void sensor_handler3(void *data)
{
    static int i = 20;
    int *pdata = (int*)data;
    *pdata = i++;
}


int main(int argc, char *argv[])
{
    int sensor1 = 0;
    int sensor2 = 0;
    int sensor3 = 0;
    pthread_t *ptid;
    struct thread_param_t arg;
    arg.Sample_rate = 30000;
    arg.string = "Hello, this is sampling rate";


    initial_sensoritem();
    addto_sensoritem("sensor1", sensor_thread1, (void*)&arg, sensor_handler1, &sensor1);
    addto_sensoritem("sensor2", sensor_thread1, NULL, sensor_handler2, &sensor2);
    addto_sensoritem("sensor3", NULL, NULL, sensor_handler3, &sensor3);
    
    
    ptid = Sensors_ThreadStart();

    while(1)
    {
        printf("-------------------------\r\n");
        printf("sensor1 data:%d \r\n", sensor1);
        printf("sensor2 data:%d \r\n", sensor2);
        printf("sensor3 data:%d \r\n", sensor3);
        sleep(2);
    }

    return 0;
}
