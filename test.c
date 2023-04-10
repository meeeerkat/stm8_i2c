#include <stdint.h>
#include <stdio.h>
#include "i2c.h"
#include "STM8S103F3.h"

void main (void) {

  i2c__init();

  i2c__start();

  i2c__write_addr(0x12);
  i2c__write(0xAB);
  i2c__write(0xCD);
  i2c__write(0xEF);

  i2c__stop();
}
