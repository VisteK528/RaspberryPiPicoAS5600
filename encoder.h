#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Coefficient for converting 12-bit information(0-4095) about angle to degrees (0-360)
static float coefficient = 360/4096.f;

// Raw angle register map
static const uint8_t raw_angle_low = 0x0D; // Raw angle (7:0)
static const uint8_t raw_angle_high = 0x0C; // Raw angle (11:8)

typedef struct{
    float rawPosition;
    float position;

    float offset;

} AS5600_ENCODER;

float getRawAngle(i2c_inst_t *i2c, uint8_t ADDRESS);
void homeEncoder(AS5600_ENCODER* encoder, float home_position, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS);
void updatePosition(AS5600_ENCODER* encoder, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS);

#endif