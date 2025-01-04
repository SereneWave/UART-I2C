#ifndef __I2C_H
#define __I2C_H

void i2c_init(const char* path);
void i2c_write_byte(unsigned char byte);
void i2c_write_address_byte(unsigned char address, unsigned char byte);

#endif