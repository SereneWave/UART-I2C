#ifndef __LCD1602_H
#define __LCD1602_H

void lcd1602_init(const char* path);
void lcd1602_clear();
void lcd1602_print(unsigned char x, unsigned char y, char* str);

#endif