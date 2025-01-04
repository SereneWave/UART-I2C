#ifndef __UART_H
#define __UART_H

void uart_init(const char* path);
void uart_close();

void uart_dtr_l();
void uart_dtr_h();
void uart_rts_l();
void uart_rts_h();

#endif