#include "i2c.h"

#include <unistd.h>

#include "uart.h"

/************************
 * DTR RTS 模拟 SCL SDA
 ************************/
#define i2c_scl_h() uart_dtr_h()
#define i2c_scl_l() uart_dtr_l()

#define i2c_sda_h() uart_rts_h()
#define i2c_sda_l() uart_rts_l()

/************************
 * I2C 信号
 ************************/
static void i2c_delay() {
    usleep(10);
}
void i2c_init(const char* path) {
    uart_init(path);
    i2c_scl_h();
    i2c_sda_h();
    i2c_delay();
}

static void i2c_start() {
    i2c_scl_h();
    i2c_sda_h();
    i2c_sda_l();
    i2c_scl_l();
}

static void i2c_stop() {
    i2c_scl_l();
    i2c_sda_l();
    i2c_scl_h();
    i2c_sda_h();
}

void i2c_write_byte(unsigned char byte) {
    // 发送8个位
    for (int i = 0; i < 8; i++) {
        if (byte & 0x80) {
            i2c_sda_h();
            // printf("1");
        } else {
            i2c_sda_l();
            // printf("0");
        }
        i2c_scl_h();
        i2c_delay();
        i2c_scl_l();
        byte <<= 1;
    }
    // printf("\n");
    // 等待设备应答
    i2c_sda_h();
    i2c_scl_h();
    i2c_delay();
    i2c_scl_l();
}

void i2c_write_address_byte(unsigned char address, unsigned char byte) {
    i2c_start();
    i2c_write_byte((address << 1) & 0xFE);  // 最后一位置 0 表示写
    i2c_write_byte(byte);
    i2c_stop();
}
