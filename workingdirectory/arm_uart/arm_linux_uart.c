#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#include "arm_linux_uart.h"

static uart_dev_t	g_uartdev[6] = {0};


static int read_and_discard_all_data(const int fd)
{
    int was_msg_already_printed = 0;
    int errno_code;

    while (1) {
        char buffer[1024];
        const ssize_t read_count = read(fd, buffer, sizeof(buffer));

        if (read_count == 0) {
            /* "EOF" or "connection closed at the other end"*/
            return 0;
        }

        if (read_count > 0) {
            if (!was_msg_already_printed) {
                printf("Some stale data was discarded.\r\n");
                was_msg_already_printed = 1;
            }

            continue;
        }

        assert(read_count == -1);  /* According to the specification. */

        errno_code = errno;
        if (errno_code == EINTR) {
            continue;
        }

        if (errno_code == EAGAIN || errno_code == EWOULDBLOCK) {
            /**
             * We know that the file descriptor has been opened with
             * O_NONBLOCK or O_NDELAY, and these codes mean that there
             * is no data to read at present.
             */
            return 0;
        }

        /* Some other error has occurred. */
        return -1;
    }
}


void Uart_Config(uart_dev_t *uart, uint8_t port_no, const char *dev_name, uart_config_t config)
{	
	int privlen = 0;
	
	if(uart == NULL || dev_name == NULL)
		return ;
	
	uart->port_no = port_no;
	strcpy(uart->dev_name, dev_name);
	uart->config = config;
}


int32_t Uart_Init(uart_dev_t *uart)
{
    int fd;
    struct termios t_opt;
    speed_t baud;

    if (uart->dev_name == NULL) {
        return 0;
    }

    if ((uart->uart_fd = open(uart->dev_name, O_RDWR | O_NOCTTY | O_NDELAY)) == -1) 
	{
        printf("open at uart failed\r\n");
        return -1;
    }

    switch (uart->config.baud_rate) {
        case 115200:
            baud = B115200;
            break;
        case 38400:
            baud = B38400;
            break;			
        case 9600:
            baud = B9600;
            break;			
        case 4800:
            baud = B4800;
            break;			
        case 2400:
            baud = B2400;
            break;
        default:
            baud = B115200;
            break;
    }

    fd = uart->uart_fd;
    /* set the serial port parameters */
    fcntl(fd, F_SETFL, 0);
    if (0 != tcgetattr(fd, &t_opt)) {
        return -1;
    }

    if (0 != cfsetispeed(&t_opt, baud)) {
        return -1;
    }

    if (0 != cfsetospeed(&t_opt, baud)) {
        return -1;
    }

    /* 8N1, flow control, etc. */
    t_opt.c_cflag |= (CLOCAL | CREAD);
    if (uart->config.parity == NO_PARITY) {
        t_opt.c_cflag &= ~PARENB;
    }
    if (uart->config.stop_bits == STOP_BITS_1) {
        t_opt.c_cflag &= ~CSTOPB;
    } else {
        t_opt.c_cflag |= CSTOPB;
    }
    t_opt.c_cflag &= ~CSIZE;
    switch (uart->config.data_width) {
        case DATA_WIDTH_5BIT:
            t_opt.c_cflag |= CS5;
            break;
        case DATA_WIDTH_6BIT:
            t_opt.c_cflag |= CS6;
            break;
        case DATA_WIDTH_7BIT:
            t_opt.c_cflag |= CS7;
            break;
        case DATA_WIDTH_8BIT:
            t_opt.c_cflag |= CS8;
            break;
        default:
            t_opt.c_cflag |= CS8;
            break;
    }
    t_opt.c_lflag &= ~(ECHO | ECHOE | ISIG | ICANON);

    /**
     * AT is going to use a binary protocol, so make sure to
     * turn off any CR/LF translation and the like.
     */
    t_opt.c_iflag &= ~(IXON | IXOFF | IXANY | INLCR | ICRNL);

    t_opt.c_oflag &= ~OPOST;
    t_opt.c_cc[VMIN] = 0;
    t_opt.c_cc[VTIME] = 5;

    if (0 != tcsetattr(fd, TCSANOW, &t_opt)) {
        return -1;
    }

    /* clear uart buffer */
    read_and_discard_all_data(fd);

    return 0;
}

int32_t Uart_Deinit(uart_dev_t *uart)
{
	int status = 0;
	
    status = close(uart->uart_fd);

	return status;
}

int32_t Uart_Send(uart_dev_t *uart, const void *data, uint32_t size)
{
    uint32_t ret, rmd = size;

    if (uart->uart_fd == -1)
		return -1;

	while (rmd > 0) {
		ret = write(uart->uart_fd, data + size - rmd, rmd);
		if (ret == -1) {
			printf("write uart fd failed on error: %d.\r\n", errno);
			return -1;
		}
		rmd -= ret;
	}

    return 0;
}

int32_t Uart_Recv(uart_dev_t *uart, void *data, uint32_t expect_size)
{
    int recv_size;

    if (uart->uart_fd == -1)
        return -1;

    if ((recv_size = read(uart->uart_fd, data, expect_size)) == -1) {
        return -1;
    }

    return recv_size;
}
