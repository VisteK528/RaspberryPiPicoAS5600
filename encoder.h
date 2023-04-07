#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Const
static float coefficient = 0.087890625f;

// Raw angle register map
static const uint8_t raw_angle_low = 0x0D; // Raw angle (7:0)
static const uint8_t raw_angle_high = 0x0C; // Raw angle (11:8)

float getAngle(i2c_inst_t *i2c, const uint8_t ADDRESS);

#endif