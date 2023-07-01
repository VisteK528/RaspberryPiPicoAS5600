#include "../include/encoder.h"

uint8_t as5600_init(i2c_inst_t* i2c, uint8_t ADDRESS){
    // 1. Check if the sensor is available at given address by reading one empty byte from the sensor

    uint8_t rxdata;
    int ret = i2c_read_blocking(i2c, ADDRESS, &rxdata, 1, false);

    if(ret >= 0){
        printf("AS5600 sensor successfully detected at 0x%x address!\n", ADDRESS);
    }
    else{
        printf("Failed to connect to the sensort at 0x%x address!\n", ADDRESS);
        return 1;
    }

    // Check if the magnet is present by reading the 0x0B STATUS register
    uint8_t status = as5600_get_magnet_status(i2c, ADDRESS);
    if(status == 0){
        printf("Magnet detected!\n");
        return 0;
    }
    else if(status == 1){
        printf("Magnet too weak! Aborting...\n");
        return 1;
    }
    else if(status == 2){
        printf("Magnet too strong! Aborting...\n");
        return 2;
    }


    printf("AS5600 sensor initialized successfully!\n");
    return 0;
}

uint8_t as5600_get_magnet_status(i2c_inst_t* i2c, uint8_t ADDRESS){
    // Check if the magnet is present by reading the 0x0B STATUS register
    uint8_t status;
    typedef enum{MAGNET_HIGH=0x08, MAGNET_LOW=0x10, MAGNET_DETECTED=0x20} STATUS;
    i2c_read_blocking(i2c, ADDRESS, &status, 1, false);

    if(status == MAGNET_LOW){
        return 1;
    }
    else if(status == MAGNET_HIGH){
        return 2;
    }
    return 0;
}

uint8_t as5600_read_from_single_register(i2c_inst_t* i2c, uint8_t ADDRESS, uint8_t REGISTER_ADDRESS){
    uint8_t data = 0;
    i2c_write_blocking(i2c, ADDRESS, &REGISTER_ADDRESS, 1, false);
    i2c_read_blocking(i2c, ADDRESS, &data, 1, false);
    return data;
}

uint16_t as5600_read_from_double_register(i2c_inst_t* i2c, uint8_t ADDRESS, uint8_t REGISTER_LSB_ADDRESS,
                                         uint8_t REGISTER_MSB_ADDRESS){
    uint16_t data, high_byte, low_byte;
    low_byte = as5600_read_from_single_register(i2c, ADDRESS, REGISTER_LSB_ADDRESS);
    high_byte = (uint16_t)as5600_read_from_single_register(i2c, ADDRESS, REGISTER_MSB_ADDRESS) << 8;
    data = high_byte | low_byte;
    return data;
}

float as5600_read_raw_angle(i2c_inst_t *i2c, uint8_t ADDRESS)
{
    float value;
    int raw_value = as5600_read_from_double_register(i2c, ADDRESS, raw_angle_low, raw_angle_high);
    value = (float)raw_value*coefficient;
    return value;
}

float as5600_read_angle(i2c_inst_t *i2c, uint8_t ADDRESS)
{
    int raw_value = as5600_read_from_double_register(i2c, ADDRESS, angle_low, angle_high);
    return (float)raw_value;
}