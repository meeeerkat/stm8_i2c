#include <stdint.h>
#include "i2c.h"
#include "STM8S103F3.h"



void i2c__init() {
  sfr_I2C.FREQR.FREQ = 1;
  //sfr_I2C.TRISER.TRISE = 9; // Rise time 1000ns
  sfr_I2C.CCRL.byte = 10; // 100kHz
  //sfr_I2C.CCRH.byte = 0;
  //sfr_I2C.ITR.byte = 0; // disable interrupts
  sfr_I2C.CR2.ACK = 1;
  sfr_I2C.OARH.ADDMODE = 0; // 7-bit addressing
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

void i2c__write_addr(uint8_t addr, uint8_t is_read) {
  sfr_I2C.DR.byte = addr << 1 | is_read;
  while (!sfr_I2C.SR1.ADDR);
  sfr_I2C.SR3.byte; // clear EV6
  sfr_I2C.CR2.ACK = 1;
}

void i2c__write_byte(uint8_t data) {
  sfr_I2C.DR.byte = data;
  while (!sfr_I2C.SR1.TXE);
}

void i2c__write_buff(uint8_t* buff, uint16_t buff_size) {
  for (uint16_t i=0; i < buff_size; ++i)
    i2c__write_byte(buff[i]);
}
void i2c__fullwrite(uint8_t addr, uint8_t* buff, uint16_t buff_size) {
  i2c__start();
  i2c__write_addr(addr, 0);
  i2c__write_buff(buff, buff_size);
  i2c__stop();
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

