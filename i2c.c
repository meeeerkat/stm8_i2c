#include <stdint.h>
#include "i2c.h"
#include "STM8S103F3.h"



void i2c__init() {
  sfr_I2C.FREQR.FREQ = 1;
  sfr_I2C.CCRL.byte = 10; // 100kHz
  sfr_I2C.OARH.ADDMODE = 1; // 7-bit addressing
  sfr_I2C.CR1.PE = 1; // Peripheral enable
}

void i2c__start() {
  sfr_I2C.CR2.START = 1;
  while (!sfr_I2C.SR1.SB);
}

void i2c__stop() {
  sfr_I2C.CR2.STOP = 1;
  while (sfr_I2C.SR3.MSL);
}

void i2c__write_addr(uint8_t addr) {
  sfr_I2C.DR.byte = addr;
  while (!sfr_I2C.SR1.ADDR);
  (void) sfr_I2C.SR3.byte; // clear EV6
  sfr_I2C.CR2.ACK = 1;
}

void i2c__write(uint8_t data) {
  sfr_I2C.DR.byte = data;
  while (!sfr_I2C.SR1.TXE);
}

uint8_t i2c__read() {
  sfr_I2C.CR2.ACK = 0;
  i2c__stop();
  while (!sfr_I2C.SR1.RXNE);
  return sfr_I2C.DR.byte;
}

void i2c__read_buff(uint8_t *buff, int len) {
  while (len-- > 1) {
    sfr_I2C.CR2.ACK = 1;
    while (!sfr_I2C.SR1.RXNE);
    *(buff++) = sfr_I2C.DR.byte;
  }
  *buff = i2c__read();
}

