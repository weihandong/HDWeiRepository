#include <stdio.h>

#include "tcpnet.h"

#define  SERVERIP ""
#define  PORT   1234


int main(int argc, char**argv)
{
    uintptr_t fd = -1;
    char pStr[] = "hello world";

    if(0 > (fd=TCP_Establish(SERVERIP, PORT))
    {
         printf("server connect failed \r\n");
    }

    TCP_Write(fd, pStr, sizeof(pStr), 100);

    while()p
    TCP_Read()
 


}
