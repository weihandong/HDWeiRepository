#ifndef _SERVE_REQ_H_
#define _SERVE_REQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <linux/types.h>

typedef void (*request_function_t)(void *data);

void request_initial(void);
//添加请求项
bool addto_reqitem(const char *name, request_function_t func, void *data);
//删除请求项
bool remove_reqitem(const char *name);

#ifdef __cplusplus
}
#endif

#endif /* _SERVE_REQ_H_ */
