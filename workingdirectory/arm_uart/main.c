#include <stdio.h>
#include "arm_linux_uart.h"
#include "execution_instruction.h"


extern void exec_instruction(uart_dev_t *uart, int argc ,char *argv[]);



int main(int argc, char *argv[])
{
    uart_dev_t uart;
    uart_config_t config;


    config.baud_rate = 115200;
    config.data_width = DATA_WIDTH_8BIT;
    config.parity = STOP_BITS_1;
    config.stop_bits = NO_PARITY;
    config.mode = MODE_TX_RX;

    Uart_Config(&uart, 1, "/dev/ttyUSB2", config);

    if(0 != Uart_Init(&uart))
    {
        printf("uart open failed \r\n");
        return -1;
    }
    
    printf("uart open successed \r\n");

    char **ppstr = NULL;

    ppstr = (char**)malloc(sizeof(char*)*2);
    for(int i=0; i<2; i++)
        ppstr[i] = (char*)malloc(sizeof(char*)*20);
    
    while(1)
    {
        printf("input instruction:");
        scanf("%s",ppstr[0]);
        exec_instruction(&uart, 1,ppstr);

        printf("\n");
    }


    if(0 == Uart_Deinit(&uart))
    {
        printf("uart close successed \r\n");
    }

    return 0;
}
