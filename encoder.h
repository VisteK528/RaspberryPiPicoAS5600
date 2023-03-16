#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define AS5600 0x36

void getAngle(i2c_inst_t *t, uint16_t *angle);


#endif