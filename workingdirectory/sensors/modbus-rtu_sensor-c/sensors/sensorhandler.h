#ifndef _SENSORS_H_
#define _SENSORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

typedef void    (*sensorinitial_func_t)(void);
typedef void    (*sensorhandler_func_t)(void *data);

void sensors_initial(void);
void initial_sensoritem(void);
//添加传感器项
bool addto_sensoritem(const char *name, sensorinitial_func_t initial,sensorhandler_func_t handler, void *data);
//删除传感器项
bool remove_sensoritem(char *name);

#ifdef __cplusplus
}
#endif

#endif /* _SENSORS_H_ */
