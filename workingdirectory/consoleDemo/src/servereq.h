#ifndef _SERVE_REQ_H_
#define _SERVE_REQ_H_


#include <stdbool.h>
#include <sys/types.h>

typedef void    (*request_function_t)(void *data);

void request_initial(void);
//添加请求项
bool addto_reqitem(const char *name, request_function_t func);
//删除请求项
bool remove_reqitem(char *name);

#endif /* _SERVE_REQ_H_ */
