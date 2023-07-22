#include "../include/sensor.h"

static void checkQuadrant(AS5600_ENCODER* encoder){
    float angle = encoder->rawPosition;

    if(angle >= 0 && angle < 90){
        encoder->quadrant = 1;
    }
    else if(angle >= 90 && angle < 180){
        encoder->quadrant = 2;
    }
    else if(angle >= 180 && angle < 270){
        encoder->quadrant = 3;
    }
    else if(angle >= 270 && angle < 360){
        encoder->quadrant = 4;
    }

    if(encoder->quadrant != encoder->previous_quadrant){
        if(encoder->quadrant == 1 && encoder->previous_quadrant == 4){
            encoder->turns++;
        }
        else if(encoder->quadrant == 4 && encoder->previous_quadrant == 1){
            encoder->turns--;
        }
        encoder->previous_quadrant = encoder->quadrant;
    }
    encoder->totalAngle = (float)encoder->turns*360.f + encoder->rawPosition;

}

void homeEncoder(AS5600_ENCODER* encoder, float home_position, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS){
    float angle = as5600_read_raw_angle(i2c, ENCODER_ADDRESS);// * (float)encoder->degPerRotation;;

    while(angle > home_position + 0.1 || angle < home_position - 0.1){
        printf("Angle: %f\tHoming...\n", angle);
        angle = as5600_read_raw_angle(i2c, ENCODER_ADDRESS);// * (float)encoder->degPerRotation;
    }
    encoder->position=0;
    encoder->rawPosition=0;
    encoder->offset= angle;
    printf("Successfully homed AS5600 magnetic encoder!\n");
    printf("Offset: %f\n", encoder->offset);
}

void updatePosition(AS5600_ENCODER* encoder, i2c_inst_t* i2c, uint8_t ENCODER_ADDRESS){
    encoder->rawPosition = as5600_read_raw_angle(i2c, ENCODER_ADDRESS);// * (float)encoder->degPerRotation;

    encoder->oldPosition = encoder->position;
    encoder->position = encoder->rawPosition - encoder->offset;
    if(encoder->position < 0){
        encoder->position += 360;
    }
    checkQuadrant(encoder);
}
