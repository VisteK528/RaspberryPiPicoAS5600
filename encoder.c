#include "encoder.h"

float getAngle(i2c_inst_t *i2c, const uint8_t ADDRESS)
{
    float value = 0;
    int raw_value = 0;
    uint8_t data = 0;
    uint16_t highbyte = 0;
    uint16_t lowbyte = 0;

    i2c_write_blocking(i2c, ADDRESS, &raw_angle_low, 1, false);
    i2c_read_blocking(i2c, ADDRESS, &data, 1, false);
    lowbyte = data;
    i2c_write_blocking(i2c, ADDRESS, &raw_angle_high, 1, false);
    i2c_read_blocking(i2c, ADDRESS, &data, 1, false);
    highbyte = data << 8;
    raw_value = highbyte | lowbyte;
    value = raw_value*coefficient;
    return value;
}