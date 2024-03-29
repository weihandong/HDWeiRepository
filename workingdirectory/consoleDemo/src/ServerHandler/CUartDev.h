#ifndef _ARM_LINUX_UART_H
#define _ARM_LINUX_UART_H

#include <stdint.h>
#include <stdarg.h>

/*
 * UART data width
 */
typedef enum {
    DATA_WIDTH_5BIT,
    DATA_WIDTH_6BIT,
    DATA_WIDTH_7BIT,
    DATA_WIDTH_8BIT,
    DATA_WIDTH_9BIT
} hal_uart_data_width_t;

/*
 * UART stop bits
 */
typedef enum {
    STOP_BITS_1,
    STOP_BITS_2
} hal_uart_stop_bits_t;


/*
 * UART parity
 */
typedef enum {
    NO_PARITY,
    ODD_PARITY,
    EVEN_PARITY
} hal_uart_parity_t;

/*
 * UART mode
 */
typedef enum {
    MODE_TX,
    MODE_RX,
    MODE_TX_RX
} hal_uart_mode_t;

/*
 * UART configuration
 */
typedef struct {
    uint32_t                baud_rate;
    hal_uart_data_width_t   data_width;
    hal_uart_parity_t       parity;
    hal_uart_stop_bits_t    stop_bits;
    hal_uart_mode_t         mode;
} uart_config_t;
/*
 * UART handle
 */
typedef struct {
	uint8_t       	port_no;   	 /* uart port */
	int				uart_fd;	 /* uart fd */
    char	       	dev_name[20];/* dev name */
    uart_config_t 	config; 	 /* uart config */
    char         	priv[1024];  /* priv data */
} uart_dev_t;

class CUartDev
{
public:
	CUartDev();
	~CUartDev();
	
	void uart_Config(uint8_t port_no, const char *dev_name, uart_config_t config);
	int32_t uart_Init(void);
	int32_t uart_Send(const void *data, uint32_t size);
	int32_t uart_Recv(void *data, uint32_t expect_size);
protected:

private:
	uart_dev_t *m_puart;
};

#endif


