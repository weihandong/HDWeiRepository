#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <modbus.h>

modbus_t *initModbus_RTU(char *pdevpath, uint32_t sec, uint32_t usec)
{
    modbus_t *mb = NULL;

    //1-打开端口
    if(NULL == (mb=modbus_new_rtu(pdevpath, 9600,'N',8, 1)))
    {
         printf("modbus-RTU serial open failed\r\n");
         return NULL;
    }
    
    //2-设置从地址
    modbus_set_slave(mb, 1);

    //3-建立连接
    modbus_connect(mb);

    //4-设置应答延时
    modbus_set_response_timeout(mb, sec, usec);

    return mb;
}

void releaseModbus_RTU(modbus_t *mb)
{
    if(mb == NULL)
         return ;

    //7-关闭modbus端口
    modbus_close(mb);
    //8-释放modbus资源
    modbus_free(mb);
}

void modbus_Poll(void)
{

}


int main(int argc, char *argv[])
{
    modbus_t *mb = NULL;
    char *pdevpath = NULL;
    uint16_t tab_reg[2] = {0};

    if(argc < 2)
    {
	printf("please input the file of device \r\n");
	return 0;
    }
    //设备文件路径
    pdevpath = argv[1];
    //初始化modbus-RTU
    mb = initModbus_RTU(pdevpath, 0, 1000000); //1000ms

    //5-循环读
    int num = 0;
    while(1)
    {   
        memset(tab_reg, 0, 2);

        //6-读寄存器设置：寄存器地址、数量、数据缓冲
        int regs = modbus_read_registers(mb, 0, 2, tab_reg);
       
        printf("-------------------------------------------\n");
        printf("[%4d][read num = %d]", num, regs);
        num++;
        
        for(int i=0; i<2; i++)
        {
            //printf("<%d>",tab_reg[i]);
	    printf("<%#x>",tab_reg[i]);
        }
        printf("\n");
        printf("-------------------------------------------\n");
        sleep(1);
    }
    releaseModbus_RTU(mb);

    return 0;
}

