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

#include "CUartDev.h"


CUartDev::CUartDev()
{
	m_puart = new uart_dev_t;
}

CUartDev::~CUartDev()
{
	close(m_puart->uart_fd);
	if(m_puart != NULL)
		delete m_puart;
	
}


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

/*
 * Config a UART interface
 *
 * @param[in]  uart  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
void CUartDev::uart_Config(uint8_t port_no, const char *dev_name, uart_config_t config)
{	
	if(m_puart == NULL || dev_name == NULL)
		return ;
	
	m_puart->port_no = port_no;
	strcpy(m_puart->dev_name, dev_name);
	m_puart->config = config;
}

/*
 * Initialises a UART interface
 *
 * @param[in]  uart  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t CUartDev::uart_Init(void)
{
    int fd;
    struct termios t_opt;
    speed_t baud;

    if (m_puart->dev_name == NULL) {
        return 0;
    }

    if ((m_puart->uart_fd = open(m_puart->dev_name, O_RDWR | O_NOCTTY | O_NDELAY)) == -1) {
        return -1;
    }

    switch (m_puart->config.baud_rate) {
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

    fd = m_puart->uart_fd;
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
    if (m_puart->config.parity == NO_PARITY) {
        t_opt.c_cflag &= ~PARENB;
    }
    if (m_puart->config.stop_bits == STOP_BITS_1) {
        t_opt.c_cflag &= ~CSTOPB;
    } else {
        t_opt.c_cflag |= CSTOPB;
    }
    t_opt.c_cflag &= ~CSIZE;
    switch (m_puart->config.data_width) {
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
int32_t CUartDev::uart_Send(const void *data, uint32_t size)
{
    uint32_t ret, rmd = size;
    char *str = (char*)data;

    if (m_puart->uart_fd == -1)
		printf("uart fd error\r\n");
		return 1;

	while (rmd > 0) {
		//ret = write(uart->uart_fd, data + size - rmd, rmd);
		ret = write(m_puart->uart_fd, str, rmd);
		if (ret == -1) {
			printf("write uart fd failed on error: %d.\r\n", errno);
			return 1;
		}
		//rmd -= ret;
	}

    return 0;
}

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
int32_t CUartDev::uart_Recv(void *data, uint32_t expect_size)
{
    int recv_size;

    if (m_puart->uart_fd == -1)
        return -1;

    if ((recv_size = read(m_puart->uart_fd, data, expect_size)) == -1) {
        return -1;
    }

    return recv_size;
}
