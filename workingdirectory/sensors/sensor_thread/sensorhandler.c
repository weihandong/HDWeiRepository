#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>


#include "sensorhandler.h"





#define SENSORNO_NUM        ( 32 )
#define ARRAY_SIZE(array)   ( sizeof(array) / sizeof((array)[0]) )

static struct sensor_t g_implement_sensors[SENSORNO_NUM] = {0};
static struct sensor_thread_t  g_sensor_thread[SENSORNO_NUM];
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

void *thread_routine(void *argv)
{

    struct sensor_t *sensor = (struct sensor_t*)argv;
    struct sensor_handler_t *handler = (struct sensor_handler_t*)sensor->handler;
    
    while(1)
    {
        printf("internal thread work\r\n");
        handler->func(handler->data);
        usleep(1000000);
    }
    return NULL;
}



pthread_t *Sensors_ThreadStart(void)
{
	uint32_t count;
    pthread_t *tid = (pthread_t*)malloc(SENSORNO_NUM);

	count = count_sensors(g_implement_sensors);

	for(int i=0; i<count; i++)
	{
        pthread_create(&tid[i], NULL, g_implement_sensors[i].thread->thread_func, &g_implement_sensors[i]);
    }

    return tid;
}
/**********************************************************************/
void *Sensor_MutexCreate(void)
{
    int err_num;
    pthread_mutex_t *mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (NULL == mutex) {
        return NULL;
    }

    if (0 != (err_num = pthread_mutex_init(mutex, NULL))) {
        printf("create mutex failed\n");
        free(mutex);
        return NULL;
    }

    return mutex;
}

void Sensor_MutexDestroy(void *mutex)
{
    int err_num;

    if (!mutex) {
        printf("mutex want to destroy is NULL!\n");
        return;
    }
    if (0 != (err_num = pthread_mutex_destroy((pthread_mutex_t *)mutex))) {
        printf("destroy mutex failed\n");
    }

    free(mutex);
}

void Sensor_MutexLock(void *mutex)
{
    int err_num;
    if (0 != (err_num = pthread_mutex_lock((pthread_mutex_t *)mutex))) {
        printf("lock mutex failed: - '%s' (%d)\n", strerror(err_num), err_num);
    }
}

void Sensor_MutexUnlock(void *mutex)
{
    int err_num;
    if (0 != (err_num = pthread_mutex_unlock((pthread_mutex_t *)mutex))) {
        printf("unlock mutex failed - '%s' (%d)\n", strerror(err_num), err_num);
    }
}

void *Sensor_CondCreate(void)
{
    int err_num;

    pthread_cond_t *cond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    if (NULL == cond) {
        return NULL;
    }

    if (0 != (err_num = pthread_cond_init(cond, NULL))) {
        printf("create cond failed\n");
        free(cond);
        return NULL;
    }

    return cond;
}

void Sensor_CondDestroy(void *cond)
{
    int err_num;

    if (!cond) {
        printf("cond want to destroy is NULL!\n");
        return;
    }
    if (0 != (err_num = pthread_cond_destroy((pthread_cond_t *)cond))) {
        printf("destroy cond failed\n");
    }

    free(cond);
}

void Sensor_CondSignal(void *cond)
{
    int err_num;

    if (0 != (err_num = pthread_cond_signal((pthread_cond_t *)cond))) {
        printf("lock cond failed: - '%s' (%d)\n", strerror(err_num), err_num);
    }
}


void Sensor_CondWait(void *cond, void *mutex)
{
    int err_num;

    if (0 != (err_num = pthread_cond_wait((pthread_cond_t *)cond, (pthread_mutex_t *)mutex))) {
        printf("lock cond failed: - '%s' (%d)\n", strerror(err_num), err_num);
    }
}


void *Sensor_SemaphoreCreate(void)
{
    sem_t *sem = (sem_t *)malloc(sizeof(sem_t));
    if (NULL == sem) {
        return NULL;
    }

    if (0 != sem_init(sem, 0, 0)) {
        free(sem);
        return NULL;
    }

    return sem;
}

void Sensor_SemaphoreDestroy(void *sem)
{
    sem_destroy((sem_t *)sem);
    free(sem);
}

void Sensor_SemaphorePost(void *sem)
{
    sem_post((sem_t *)sem);
}

#define PLATFORM_WAIT_INFINITE (~0)

int Sensor_SemaphoreWait(void *sem, uint32_t timeout_ms)
{
    if (PLATFORM_WAIT_INFINITE == timeout_ms) {
        sem_wait(sem);
        return 0;
    } else {
        struct timespec ts;
        int s;
        /* Restart if interrupted by handler */
        do {
            if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
                return -1;
            }

            s = 0;
            ts.tv_nsec += (timeout_ms % 1000) * 1000000;
            if (ts.tv_nsec >= 1000000000) {
                ts.tv_nsec -= 1000000000;
                s = 1;
            }

            ts.tv_sec += timeout_ms / 1000 + s;

        } while (((s = sem_timedwait(sem, &ts)) != 0) && errno == EINTR);

        return (s == 0) ? 0 : -1;
    }
}


void Sensor_ThreadDetach(void *thread_handle)
{
    pthread_detach((pthread_t)thread_handle);
}

void Sensor_ThreadDelete(void *thread_handle)
{
    if (NULL == thread_handle) {
        pthread_exit(0);
    } else {
        /*main thread delete child thread*/
        pthread_cancel((pthread_t)thread_handle);
        pthread_join((pthread_t)thread_handle, 0);
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
	for(int i = 0; i < ARRAY_SIZE(g_implement_sensors); i++)
	{
        g_implement_sensors[i].name = NULL;
        g_implement_sensors[i].sensor_no = -1;
		g_implement_sensors[i].thread = &g_sensor_thread[i];
		g_implement_sensors[i].handler = &g_sensor_handler[i];
        g_implement_sensors[i].enable = enable_sensors;
        g_implement_sensors[i].sensor_enable = false; 
	}
}

/***************************************************************************************************************/
void add_sensoritem(struct sensor_t *sensor, const char *name, sensorthread_func_t thread_func, void *argv, sensorhandler_func_t handler, void *data)
{
	if(!sensor)
		return ;
		
    int len = strlen(name) + 1;
    sensor->name = (char*)malloc(len);
    if(sensor->name == NULL)
        return ;
    memcpy(sensor->name, name, len);

	if(sensor->handler->func != NULL)
		return ;
    if(thread_func == NULL)
        sensor->thread->thread_func = thread_routine;
    else
    {
        sensor->thread->thread_func = thread_func;
        sensor->thread->argv = argv;
    }
//    sensor->thread->n_mutex = (pthread_mutex_t *)Sensor_MutexCreate();
//    sensor->thread->n_cond = (pthread_cond_t *)Sensor_CondCreate();

	//绑定传感器采集函数
	sensor->handler->func = handler;
	sensor->handler->data = data;

    if(sensor->enable)
        sensor->enable(sensor->sensor_no, true);
}


//添加传感器采集函数
bool addto_sensoritem(const char *name, sensorthread_func_t thread_func, void *argv,sensorhandler_func_t handler, void *data)
{
	struct sensor_t *sensor = NULL;
    int sensorno_id;
	int i;

	if(!name || !handler)
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

	add_sensoritem(sensor, name, thread_func, argv, handler, data);
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

    sensor->thread->thread_func = NULL;
    /*
    Sensor_MutexDestroy(sensor->thread->n_mutex);
    sensor->thread->n_mutex = NULL;
    Sensor_CondDestroy(sensor->thread->n_cond);
    sensor->thread->n_cond = NULL;
    */
    sensor->handler->func = NULL;
	sensor->handler->data = 0;

    if(sensor->enable)
        sensor->enable(sensor->sensor_no, false);
}

//删除传感器
bool remove_sensoritem(char *name)
{
	struct sensor_t *sensor = NULL;
	int i;

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

