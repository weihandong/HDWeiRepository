#include "execution_instruction.h"
#include "arm_linux_uart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	const char *name;
	const int instruction_no;
 	const char pelco_d[7];
}instruction_t;

typedef struct _PELCOD_packet
{
    unsigned char bytes[32];
    uint32_t length;
} PELCOD_Packet_t;


#define ARRAY_SIZE(array)   ( sizeof(array)/sizeof((array)[0]))

static instruction_t instruction_lit[] = {
    {"turn_stop", 0,{0xff,0x01,0x00,0x00,0x00,0x00,0x01}},
	{"tilt_up", TILT_UP,{0xff,0x01,0x00,0x08,0x00,0xff,0x08}},
	{"tilt_down", TILT_DOWN,{0xff,0x01,0x00,0x10,0x00,0xff,0x10}},
	{"pan_left", PAN_LEFT,{0xff,0x01,0x00,0x04,0xff,0x00,0x04}},
	{"pan_right", PAN_RIGHT,{0xff,0x01,0x00,0x02,0xff,0x00,0x02}},

    {"up_left", UP_LEFT,{0xff,0x01,0x00,0x0c,0x1f,0x1f,0x4b}},
	{"up_right", UP_RIGHT,{0xff,0x01,0x00,0x0a,0x1f,0x1f,0x49}},
	{"down_left", DOWN_LEFT,{0xff,0x01,0x00,0x14,0x1f,0x1f,0x53}},
	{"down_right", DOWN_RIGHT,{0xff,0x01,0x00,0x12,0xff,0x00,0x51}},
};


void PELCOD_init_packet(PELCOD_Packet_t *packet)
{
    packet->length = 1;
}

void PELCOD_append_byte(PELCOD_Packet_t *packet, unsigned char byte)
{
    packet->bytes[packet->length] = byte;
    (packet->length)++;
}

uint32_t PELCOD_set_pantilt_up(uint32_t pan_speed, uint32_t tilt_speed)
{
    return 0;
}



void exec_instruction(uart_dev_t *uart, int argc , char *argv[])
{
	int i;
	instruction_t * cmd = 0;

    printf("%s\n",argv[0]);

	if(argc > 0)
	{
        if(argc == 1){
            if(atoi(argv[0]) == -1)
                return ;

            for(i = 0; i < ARRAY_SIZE(instruction_lit); i++)
            {
                cmd = &instruction_lit[i];
                if(cmd->instruction_no == atoi(argv[0]))
                    break;
                else
                    cmd = 0;
            }

        }else{
            if(strcmp("", argv[0]) == 0 && atoi(argv[1]) == -1)
                return ;

            for(i = 0; i < ARRAY_SIZE(instruction_lit); i++)
            {
                cmd = &instruction_lit[i];
                if(strncmp(cmd->name,argv[0],strlen(argv[0])) == 0 || cmd->instruction_no == atoi(argv[1]))
                    break;
                else
                    cmd = 0;
            }
            
	    }
    }

    if(cmd == 0)
    {
        printf("invalid instruction \r\n");
    }else{
        //执行发送指令
        printf("name: %s\n",cmd->name);
        printf("instruction_no: %d\n",cmd->instruction_no);
        printf("pelco-d:");
        for(int i=0; i<7; i++)
            printf("%02X ",cmd->pelco_d[i]);
        printf("\n");

       // Uart_Send(uart, cmd->pelco_d, sizeof(cmd->pelco_d));
    }    
}
