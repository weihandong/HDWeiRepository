#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "servereq.h"

extern do_reqs(const int reqno);
void do_req1(char *data);
void do_req2(char *data);

int main(int argc, char *argv[])
{
    int reqno = -1;

    request_initial();
    addto_reqitem("req1",do_req1, "hello world. I am req1");
    addto_reqitem("req2",do_req2, "hello world. I am req2");

    while(1)
    {
        scanf("%d", &reqno);
        do_reqs(reqno);
    }


    return 0;
}

void do_req1(char *data)
{
    printf("req1 data: %s\r\n",data);
}

void do_req2(char *data)
{
    printf("req2 data: %s\r\n",data);
}
