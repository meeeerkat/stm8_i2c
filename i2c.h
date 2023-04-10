#pragma once

#include <stdint.h>


void i2c__init();

void i2c__start();
void i2c__stop();

void i2c__write_addr(uint8_t addr);

void i2c__write(uint8_t data);

uint8_t i2c__read();
void i2c__read_buff(uint8_t *buff, int len);
