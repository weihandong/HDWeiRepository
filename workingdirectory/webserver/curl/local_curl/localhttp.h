#ifndef _LOCAL_HTTP_H
#define _LOCAL_HTTP_H

 

#define DEFAULT_PORT 80

 
char *http_get(const char *url);

char *http_post(const char *url, const char *post_body);


#endif

