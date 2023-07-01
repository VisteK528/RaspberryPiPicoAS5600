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

static const uint8_t angle_low = 0x0F; // Angle (7:0)
static const uint8_t angle_high = 0x0E; // Angle (11:8)

/// @brief \n Initializes AS5600 sensor by checking if it is available at given address and if the magnet is present
/// @param i2c type: i2c_inst_t* -  raspberry pi pico i2c instance
/// @param ADDRESS type: uint8_t - hexadecimal i2c address of AS5600 sensor
/// @returns type: uint8_t If the sensor was initialized successfully function returns 0,
/// otherwise the function returns 1.
uint8_t as5600_init(i2c_inst_t* i2c, uint8_t ADDRESS);

/// @brief \n Checks if the magnet is present and if its magnetic field optimal for sensor's normal activity.
/// @param i2c type: i2c_inst_t* -  raspberry pi pico i2c instance
/// @param ADDRESS type: uint8_t - hexadecimal i2c address of AS5600 sensor
/// @returns type: uint8_t If the magnet is present and its magnetic field influence is sufficient the function
/// returns 0, otherwise the function returns 1.
uint8_t as5600_get_magnet_status(i2c_inst_t* i2c, uint8_t ADDRESS);

/// @brief \n Reads data from single 1 byte (8 bits) AS5600 data register
/// @param i2c type: i2c_inst_t* -  raspberry pi pico i2c instance
/// @param ADDRESS type: uint8_t - hexadecimal i2c address of AS5600 sensor
/// @param REGISTER_ADDRESS type: uint8_t - hexadecimal address of AS5600 sensor register to be read
/// @returns data type: uint8_t - raw data read from the selected AS5500 register
uint8_t as5600_read_from_single_register(i2c_inst_t* i2c, uint8_t ADDRESS, uint8_t REGISTER_ADDRESS);

/// @brief \n Reads data from single 2 byte (16 bits) AS5600 data register
/// @param i2c type: i2c_inst_t* -  raspberry pi pico i2c instance
/// @param ADDRESS type: uint8_t - hexadecimal i2c address of AS5600 sensor
/// @param REGISTER_LSB_ADDRESS type: uint8_t - hexadecimal address of low byte of AS5600 sensor register to be read
/// @param REGISTER_MSB_ADDRESS type: uint8_t - hexadecimal address of high byte of AS5600 sensor register to be read
/// @returns data type: uint16_t - raw data read from the selected AS5500 register
uint16_t as5600_read_from_double_register(i2c_inst_t* i2c, uint8_t ADDRESS, uint8_t REGISTER_LSB_ADDRESS,
                                         uint8_t REGISTER_MSB_ADDRESS);

/// @brief \n Reads raw angle from AS5600 RAW_ANGLE register
/// @param i2c type: i2c_inst_t* -  raspberry pi pico i2c instance
/// @param ADDRESS type: uint8_t - hexadecimal i2c address of AS5600 sensor
/// @returns data type: float - raw angle
float as5600_read_raw_angle(i2c_inst_t* i2c, uint8_t ADDRESS);

/// @brief \n Reads angle from AS5600 ANGLE register
/// @param i2c type: i2c_inst_t* -  raspberry pi pico i2c instance
/// @param ADDRESS type: uint8_t - hexadecimal i2c address of AS5600 sensor
/// @returns data type: float - angle
float as5600_read_angle(i2c_inst_t* i2c, uint8_t ADDRESS);


#endif