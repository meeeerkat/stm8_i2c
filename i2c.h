#pragma once

#include <stdint.h>


void i2c__init();

void i2c__start();
void i2c__stop();

void i2c__write_addr(uint8_t addr, uint8_t is_read);

void i2c__write_byte(uint8_t data);
void i2c__write_buff(uint8_t* buff, uint16_t buff_size);
void i2c__fullwrite(uint8_t addr, uint8_t* buff, uint16_t buff_size);

uint8_t i2c__read();
void i2c__read_buff(uint8_t* buff, int len);

