#include "uart.h"

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

/************************
 * 文件描述符开关
 ************************/
static int fd;

static void signal_handler(int signum) {
    uart_close();
    exit(0);
}

void uart_init(const char* path) {
    fd = open(path, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("打开串口失败");
        exit(1);
    }
    signal(SIGINT, signal_handler);
}

void uart_close() {
    close(fd);
}

/************************
 * 控制 DTR RTS 低电平有效
 ************************/
void uart_dtr_l() {
    int status;
    ioctl(fd, TIOCMGET, &status);
    // 设置 DTR 位
    status |= TIOCM_DTR;
    ioctl(fd, TIOCMSET, &status);
}

void uart_dtr_h() {
    int status;
    ioctl(fd, TIOCMGET, &status);
    // 清除 DTR 位
    status &= ~TIOCM_DTR;
    ioctl(fd, TIOCMSET, &status);
}

void uart_rts_l() {
    int status;
    ioctl(fd, TIOCMGET, &status);
    // 设置 RTS 位
    status |= TIOCM_RTS;
    ioctl(fd, TIOCMSET, &status);
}

void uart_rts_h() {
    int status;
    ioctl(fd, TIOCMGET, &status);
    // 清除 RTS 位
    status &= ~TIOCM_RTS;
    ioctl(fd, TIOCMSET, &status);
}
