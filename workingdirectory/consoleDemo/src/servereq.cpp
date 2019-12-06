#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servereq.h"


extern void req(void);

struct req_handler_t
{
	void (*func)(void *data);
};



struct req_t 
{
	/* 请求操作名称 */
	char * name;
	/* 请求号 */
	int req_no;
	/* 请求处理函数 */
	struct req_handler_t *handler;
    /* Enable irq or not */
    void (*enable)(const int reqno, bool enable);
    /* 请求号是否被启用 */
    bool reqno_enable;
};

#define REQNO_NUM           ( 128 )
#define ARRAY_SIZE(array)   ( sizeof(array) / sizeof((array)[0]) )

struct req_t implement_reqs[REQNO_NUM] = {0};

static struct req_handler_t req_handler[REQNO_NUM];
//暂时不需要处理的

int fd_to_reqno(int reqno);
void enable_reqs(const int reqno, bool enable);


/*
 * the array of req.
 */
static const char* req_name(const int reqno)
{
	unsigned int i = 0;
    const char *cmd_name = NULL;

	for(i=0; i<ARRAY_SIZE(implement_reqs); i++)
    {
        if(implement_reqs[i].req_no == reqno) 
        {
            cmd_name = implement_reqs[i].name;
            break;
        }
    }

	return cmd_name;
}

static const int req_offset(const char* cmd_name)
{
	unsigned int i = 0;
    int index = -1;

	for(i=0; i<ARRAY_SIZE(implement_reqs); i++)
    {
		if(strcmp(implement_reqs[i].name, cmd_name) == 0)
        {
            index = i;
            break;
        }
    }

	return index;
}

bool isenable(int index)
{
    return implement_reqs[index].reqno_enable == true ? true : false ;
}

bool doreq_by_name(const char *req_name, void *data)
{
	int index;

	index = req_offset(req_name);
    if(index != -1 && isenable(index))
    {
		(req_handler[index].func)(data);
        return true;
    }

    return false;
}

bool doreq_by_reqno(const int reqno, void *data)
{
    const char *pcmd = NULL;

    pcmd = req_name(reqno);
    if(pcmd != NULL && isenable(reqno))
    {
		(req_handler[reqno].func)(data);
        return true;
    }

    return false;
}

void enable_reqs(const int reqno, bool enable)
{
    int req_no = -1;
    
    req_no = fd_to_reqno(reqno);
    if(req_no < 0 || req_no > REQNO_NUM)
        return ;

    if(implement_reqs[req_no].reqno_enable != enable)
        implement_reqs[req_no].reqno_enable = enable;
}

int fd_to_reqno(int reqno)
{
    int reqno_id;

    for (reqno_id = 0; reqno_id < REQNO_NUM; reqno_id++) 
    {
        if (implement_reqs[reqno_id].req_no == reqno) 
        {
            break;
        }
    }

    return reqno_id;
}


void request_initial(void)
{
    unsigned int i = 0;

	for(i=0; i < ARRAY_SIZE(implement_reqs); i++)
	{
        implement_reqs[i].name = NULL;
        implement_reqs[i].req_no = -1;
		implement_reqs[i].handler = &req_handler[i];
        implement_reqs[i].enable = enable_reqs;
        implement_reqs[i].reqno_enable = false; 
	}
}

//添加请求项
bool addto_reqitem(const char * name, request_function_t func)
{
	struct req_t * req = NULL;
    int reqno_id;
	unsigned int i;

	if(!name || !func)
		return false;

	for(i=0; i< ARRAY_SIZE(implement_reqs); i++)
    {
        if(implement_reqs[i].name == NULL) 
            break;
		if(strcmp(implement_reqs[i].name, name) == 0)
            return false;
    }

    for (reqno_id = 0; reqno_id < REQNO_NUM; reqno_id++) 
    {
        if(implement_reqs[reqno_id].req_no >= 0) 
        {
            continue;
        }
        implement_reqs[reqno_id].req_no = reqno_id;
        req = &implement_reqs[reqno_id];
        break;
    }

	if(!req)
		return false;

    int len = strlen(name) + 1;
    req->name = (char*)malloc(len);
    if(req->name == NULL)
        return false;
    memcpy(req->name, name, len);

	if(req->handler->func != NULL)
		return false;

	req->handler->func = func;

    if(req->enable)
        req->enable(req->req_no, true);
   
    printf("addto <%s> into implement_reqs table \r\n", req->name);
	return true;
}

//删除请求项
bool remove_reqitem(char * name)
{
	struct req_t * req = NULL;
	unsigned int i;

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
    
    free(req->name);
    req->name = NULL;
    req->req_no = -1;
	req->handler->func = NULL;

    if(req->enable)
            req->enable(req->req_no, false);

	return true;
}
