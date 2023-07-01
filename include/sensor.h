#ifndef RASPBERRYPIPICOAS5600_SENSOR_H
#define RASPBERRYPIPICOAS5600_SENSOR_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "encoder.h"

typedef struct{
    float rawPosition;
    float oldPosition;
    float position;

    float velocity;
    float oldVelocity;

    float offset;

} AS5600_ENCODER;

void homeEncoder(AS5600_ENCODER* encoder, float home_position, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS);
void updatePosition(AS5600_ENCODER* encoder, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS);

#endif //RASPBERRYPIPICOAS5600_SENSOR_H
