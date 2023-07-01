#include <string.h>
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/encoder.h"
#include "include/sensor.h"

#define AS5600_I2C_ADDRESS 0x36

AS5600_ENCODER encoder;
bool ISR_timer_callback(struct repeating_timer *t) {
    updatePosition(&encoder, i2c_default, AS5600_I2C_ADDRESS);
    return true;
}

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

    //homeEncoder(&encoder, 120.f, i2c_default, AS5600_I2C_ADDRESS);
    struct repeating_timer timer;
    add_repeating_timer_ms(2, ISR_timer_callback, NULL, &timer);

    while(1)
    {
        sleep_ms(10);
        printf("Position: %f\tRaw position: %f\n", encoder.position, encoder.rawPosition);
    }
    return 0;
}