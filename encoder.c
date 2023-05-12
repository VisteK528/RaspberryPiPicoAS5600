#include "encoder.h"

float getRawAngle(i2c_inst_t *i2c, uint8_t ADDRESS)
{
    float value;
    int raw_value;
    uint8_t data = 0;
    uint16_t highbyte, lowbyte;

    i2c_write_blocking(i2c, ADDRESS, &raw_angle_low, 1, false);
    i2c_read_blocking(i2c, ADDRESS, &data, 1, false);
    lowbyte = data;
    i2c_write_blocking(i2c, ADDRESS, &raw_angle_high, 1, false);
    i2c_read_blocking(i2c, ADDRESS, &data, 1, false);
    highbyte = data << 8;
    raw_value = highbyte | lowbyte;
    value = (float)raw_value*coefficient;
    return value;
}

void homeEncoder(AS5600_ENCODER* encoder, float home_position, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS){
    float angle = getRawAngle(i2c, ENCODER_ADDRESS);
    while(angle > home_position + 0.1 || angle < home_position - 0.1){
        printf("Angle: %f\tHoming...\n", angle);
        angle = getRawAngle(i2c, ENCODER_ADDRESS);
    }
    encoder->position=0;
    encoder->rawPosition=0;
    encoder->offset= getRawAngle(i2c, ENCODER_ADDRESS);
    printf("Successfully homed AS5600 magnetic encoder!\n");
    printf("Offset: %f\n", encoder->offset);
}

void updatePosition(AS5600_ENCODER* encoder, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS){
    encoder->rawPosition = getRawAngle(i2c, ENCODER_ADDRESS);
    encoder->position = encoder->rawPosition - encoder->offset;
    if(encoder->position < 0){
        encoder->position += 360;
    }
}