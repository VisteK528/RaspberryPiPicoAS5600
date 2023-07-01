#include "../include/sensor.h"

void homeEncoder(AS5600_ENCODER* encoder, float home_position, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS){
    float angle = as5600_read_raw_angle(i2c, ENCODER_ADDRESS);
    while(angle > home_position + 0.1 || angle < home_position - 0.1){
        printf("Angle: %f\tHoming...\n", angle);
        angle = as5600_read_raw_angle(i2c, ENCODER_ADDRESS);
    }
    encoder->position=0;
    encoder->rawPosition=0;
    encoder->offset= as5600_read_raw_angle(i2c, ENCODER_ADDRESS);
    printf("Successfully homed AS5600 magnetic encoder!\n");
    printf("Offset: %f\n", encoder->offset);
}

void updatePosition(AS5600_ENCODER* encoder, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS){
    encoder->rawPosition = as5600_read_raw_angle(i2c, ENCODER_ADDRESS);
    encoder->oldPosition = encoder->position;
    encoder->position = encoder->rawPosition - encoder->offset;
    if(encoder->position < 0){
        encoder->position += 360;
    }
}
