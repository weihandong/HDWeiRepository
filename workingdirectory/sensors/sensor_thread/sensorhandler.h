#ifndef _SENSORS_H_
#define _SENSORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

typedef void   *(*sensorthread_func_t)(void *data);
typedef void    (*sensorhandler_func_t)(void *data);

//传感器初始化结构体
struct sensor_thread_t
{
	void *(*thread_func)(void *data);
    void *argv;
//    pthread_mutex_t n_mutex;
//    pthread_cond_t  n_cond;
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
	struct sensor_thread_t *thread;
	/* 传感器采集函数 */
	struct sensor_handler_t *handler;
    /* 是否启用传感器 */
    void (*enable)(const int sensorno, bool enable);
    bool sensor_enable;
};

struct thread_param_t
{
    int Sample_rate;
    char *string;
};


void initial_sensoritem(void);
//添加传感器项
bool addto_sensoritem(const char *name, sensorthread_func_t thread_func, void *argv, sensorhandler_func_t handler, void *data);
//删除传感器项
bool remove_sensoritem(char *name);

#ifdef __cplusplus
}
#endif

#endif /* _SENSORS_H_ */
