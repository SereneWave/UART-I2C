#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "lcd1602.h"

int main(void) {
    lcd1602_init("/dev/ttyUSB0");

    while (1) {
        time_t current_time = time(NULL);
        char time_str[17];

        // strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&current_time));
        strftime(time_str, sizeof(time_str), "%m-%d %H:%M:%S", localtime(&current_time));
        // time_t start_time, end_time;
        // start_time = time(NULL);
        lcd1602_print(0, 0, time_str);
        // end_time = time(NULL);
        // printf("刷新屏幕花费 %ds 时间\n", (int)difftime(end_time, start_time));
        sleep(5);
    }
}