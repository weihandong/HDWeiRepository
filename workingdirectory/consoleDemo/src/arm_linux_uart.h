#ifndef _ARM_LINUX_UART_H_
#define _ARM_LINUX_UART_H_


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
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

typedef struct {
	uint8_t       	port_no;   	 /* uart port */
	int				uart_fd;	 /* uart fd */
    char	       	dev_name[20];/* dev name */
    uart_config_t 	config; 	 /* uart config */
    char         	priv[1024];  /* priv data */
} uart_dev_t;


void Uart_Config(uart_dev_t *uart, uint8_t port_no, const char *dev_name, uart_config_t config);

/**
 * Initialises a UART interface
 *
 *
 * @param[in]  uart  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t Uart_Init(uart_dev_t *uart);

/**
 * Deinitialises a UART interface
 *
 * @param[in]  uart  the interface which should be deinitialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t Uart_Deinit(uart_dev_t *uart);

/**
 * Transmit data on a UART interface
 *
 * @param[in]  uart     the UART interface
 * @param[in]  data     pointer to the start of data
 * @param[in]  size     number of bytes to transmit
 * @param[in]  timeout  timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                      if you want to wait forever
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t Uart_Send(uart_dev_t *uart, const void *data, uint32_t size);

/**
 * Receive data on a UART interface
 *
 * @param[in]   uart         the UART interface
 * @param[out]  data         pointer to the buffer which will store incoming data
 * @param[in]   expect_size  number of bytes to receive
 * @param[out]  recv_size    number of bytes received
 * @param[in]   timeout      timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                           if you want to wait forever
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t Uart_Recv(uart_dev_t *uart, void *data, uint32_t expect_size);


#endif


