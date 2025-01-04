#include <stdio.h>
#include <string.h>

#include "i2c.h"

#define LCD1602_ADDR 0x27

/************************
 * LCD1602 I2C 驱动
 ************************/
static void lcd1602_write_word(unsigned char address, unsigned char data) {
    // 0x08 是打开背光
    data |= 0x08;
    i2c_write_address_byte(address, data);
}

static void lcd1602_send_command(unsigned char comm) {
    unsigned char buf;
    // 先发送 bit7 - bit4
    buf = comm & 0xF0;
    buf |= 0x04;  // RS = 0, RW = 0, EN = 1
    lcd1602_write_word(LCD1602_ADDR, buf);
    buf &= 0xFB;  // EN = 0
    lcd1602_write_word(LCD1602_ADDR, buf);
    // 再发送 bit3 - bit0
    buf = (comm & 0x0F) << 4;
    buf |= 0x04;  // RS = 0, RW = 0, EN = 1
    lcd1602_write_word(LCD1602_ADDR, buf);
    buf &= 0xFB;  // EN = 0
    lcd1602_write_word(LCD1602_ADDR, buf);
}

static void lcd1602_send_data(unsigned char data) {
    unsigned char buf;
    // 先发送 bit7 - bit4
    buf = data & 0xF0;
    buf |= 0x05;  // RS = 1, RW = 0, EN = 1
    lcd1602_write_word(LCD1602_ADDR, buf);
    buf &= 0xFB;  // EN = 0
    lcd1602_write_word(LCD1602_ADDR, buf);
    // 再发送 bit3 - bit0
    buf = (data & 0x0F) << 4;
    buf |= 0x05;  // RS = 1, RW = 0, EN = 1
    lcd1602_write_word(LCD1602_ADDR, buf);
    buf &= 0xFB;  // EN = 0
    lcd1602_write_word(LCD1602_ADDR, buf);
}
void lcd1602_init(const char* path) {
    i2c_init(path);
    // 先设置8线模式
    lcd1602_send_command(0x33);
    // 再设置4线模式
    lcd1602_send_command(0x32);
    // 设置2行 5*7点阵
    lcd1602_send_command(0x28);
    // 关闭光标
    lcd1602_send_command(0x0C);
    // 清屏
    lcd1602_send_command(0x01);
}
void lcd1602_clear() {
    lcd1602_send_command(0x01);
}

void lcd1602_print(unsigned char x, unsigned char y, char* str) {
    // 限制坐标范围
    if (x < 0) x = 0;
    if (x > 15) x = 15;
    if (y < 0) y = 0;
    if (y > 1) y = 1;

    unsigned char addr = 0x80 + 0x40 * y + x;
    // 发送命令移动光标到指定位置
    lcd1602_send_command(addr);

    // 循环发送字符串中的每个字符数据
    for (size_t i = 0; i < strlen(str); i++) {
        lcd1602_send_data((unsigned char)str[i]);
    }
}
