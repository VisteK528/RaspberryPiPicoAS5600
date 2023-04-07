#include <string.h>
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "encoder.h"

#define AS5600_I2C_ADDRESS 0x36

float value = 0;



int main()
{
    stdio_init_all();
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    while(1)
    {
        sleep_ms(10);
        value = getAngle(i2c_default, AS5600_I2C_ADDRESS);
        printf("%f\n", value);
    }
    return 0;
}