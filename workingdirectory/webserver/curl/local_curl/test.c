#include <stdio.h>
#include <stdlib.h>
#include "localhttp.h"


#define curl  "http://14.215.177.39:80"


int main(int argc, char*argv[])
{
    char *presult = NULL;
     char buff[1024];

     presult = http_get(curl);
     if(presult != NULL)
     {
          printf("respons:%s\r\n",presult);
          free(presult);
          presult = NULL;
     }

     return 0;
}
