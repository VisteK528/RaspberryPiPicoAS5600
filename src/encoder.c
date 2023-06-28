#include "../include/encoder.h"

int8_t as5600_init(i2c_inst_t* i2c, uint8_t ADDRESS){
    // 1. Check if the sensor is available at given address by reading one empty byte from the sensor

    uint8_t rxdata;
    int ret = i2c_read_blocking(i2c, ADDRESS, &rxdata, 1, false);

    if(ret >= 0){
        printf("AS5600 sensor successfully detected at 0x%x address!\n", ADDRESS);
    }
    else{
        printf("Failed to connect to the sensort at 0x%x address!\n", ADDRESS);
        return -1;
    }

    // Check if the magnet is present by reading the 0x0B STATUS register
    uint8_t status;
    typedef enum{MAGNET_HIGH=0x08, MAGNET_LOW=0x10, MAGNET_DETECTED=0x20} STATUS;
    i2c_read_blocking(i2c, ADDRESS, &status, 1, false);

    if(status == MAGNET_DETECTED){
        printf("Magnet detected!\n");
    }
    else if(status == MAGNET_LOW){
        printf("Magnet too weak! Aborting...\n");
        return -1;
    }
    else if(status == MAGNET_HIGH){
        printf("Magnet too strong! Aborting...\n");
        return -1;
    }

    printf("AS5600 sensor initialized successfully!\n");
    return 0;
}

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