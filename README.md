# AS5600 magnetic encoder library

This library consists of 2 parts. 

## General info
AS5600 i2C address - ```0x36```

## Encoder Library
This part is dedicated to for pure usage of AS5600 magnetic encoder and comes with these functions:
### Available functions
```c
uint8_t as5600_init(i2c_inst_t* i2c, uint8_t ADDRESS);
uint8_t as5600_get_magnet_status(i2c_inst_t* i2c, uint8_t ADDRESS);
uint8_t as5600_read_from_single_register(i2c_inst_t* i2c, uint8_t ADDRESS, uint8_t REGISTER_ADDRESS);
uint16_t as5600_read_from_double_register(i2c_inst_t* i2c, uint8_t ADDRESS, uint8_t REGISTER_LSB_ADDRESS,
                                         uint8_t REGISTER_MSB_ADDRESS);
float as5600_read_raw_angle(i2c_inst_t* i2c, uint8_t ADDRESS);
float as5600_read_angle(i2c_inst_t* i2c, uint8_t ADDRESS);
```
## Robotic Arm Joint Sensor Library
### Available functions