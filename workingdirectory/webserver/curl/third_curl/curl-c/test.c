
#include <stdio.h>  

#include <stdlib.h>  

#include "curl.h"

 

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *param)  
{  
    return size * nmemb;  
}  

static size_t head_data(char *ptr, size_t size, size_t nmemb, void *param)  
{  
	//printf("%s\r\n",ptr);
	char buff[512] = {0};
	char * pketword = "Content-Length: ";
	int i = 0;

	if(NULL == ptr)
	{
		printf("packet read error! \r\n");
		return size * nmemb; 
	}

	while((ptr[i] == pketword[i])&&(ptr[i] != ' '))       
    	{       
        	i++;   
    	}  

    	if(ptr[i] == pketword[i])  
	{
		//sscanf( (char*)ptr, "%*s%[^\r]", buff );//%s遇空格停止，加*则是忽略第一个读到的字符串
		sscanf((char*)ptr, "%*[^ ] %[^\r\n]", buff);//第一段到空格结束前的内容都忽略掉，第二段从空格开始换行结束
		printf("Size=%s\r\n",buff);
		return 0;
	}
	else{
		return size * nmemb;  
	}
}
 

void * http_get(const char *pcurl) 
{
    CURL *curl;//定义CURL类型的指针  
    CURLcode res; //定义CURLcode类型的变量  
  
    curl = curl_easy_init();//初始化一个CURL类型的指针   
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);//这里打开libcurl打印所有调试信息  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);  
    //CURLOPT_NOBODY只下报文头，不包括数据.但是这里默认是head命令，注释掉，则是GET命令  
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);  
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);   
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, head_data);  
    //让用户指定url. Defaultport中存放的命令行传进来的网址  
    curl_easy_setopt(curl, CURLOPT_URL, pcurl);  
    //传输时间 （ms）   
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 100);
    //设置端口
    curl_easy_setopt(curl, CURLOPT_PORT, 80);  
    res = curl_easy_perform(curl);
    //清除curl操作.  
    curl_easy_cleanup(curl);  

    return NULL;  
}

 
int main(int argc, char **argv)
{
	CURLcode res;
 
	res = curl_global_init(CURL_GLOBAL_ALL);  
	if (res != CURLE_OK)  
    	{  
        	printf( "Failed to global init default [%d]\n", res);  
        	return 1;  
    	}

	http_get("https://blog.csdn.net/dqvega/article/details/6960772");
}

