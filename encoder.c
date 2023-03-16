#include "encoder.h"


void getAngle(i2c_inst_t *t, uint16_t *angle)
{
    uint8_t command = 0x0F;
    uint8_t data[2];
    i2c_write_blocking(t, 0x36, &command, 1, true);
    sleep_ms(2);
    i2c_read_blocking(t, 0x36, data, 2, true);
    *angle = (data[0]<<8) | (data[1]<<4);
}

