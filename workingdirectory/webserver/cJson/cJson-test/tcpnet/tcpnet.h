#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netdb.h>



static uint64_t _linux_get_time_ms(void);

static uint64_t _linux_time_left(uint64_t t_end, uint64_t t_now);

uintptr_t TCP_Establish(const char *host, uint16_t port);

int TCP_Destroy(uintptr_t fd);

int32_t TCP_Write(uintptr_t fd, const char *buf, uint32_t len, uint32_t timeout_ms);

int32_t TCP_Read(uintptr_t fd, char *buf, uint32_t len, uint32_t timeout_ms);

















