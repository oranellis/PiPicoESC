#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"
#include <stdio.h>

// Define output pins
#define outputAHigh 0
#define outputBHigh 1
#define outputCHigh 2
#define outputALow 3
#define outputBLow 4
#define outputCLow 5
#define LED_PIN PICO_DEFAULT_LED_PIN

uint slice_num_0;
uint slice_num_1;
uint slice_num_2;
uint channel_0;
uint channel_1;
uint channel_2;

int iosetup() {
    
     // IO Initialisation 
    stdio_init_all();

    // LED setup
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    // PWM setup
    gpio_set_function(outputAHigh, GPIO_FUNC_PWM);
    gpio_set_function(outputBHigh, GPIO_FUNC_PWM);
    gpio_set_function(outputCHigh, GPIO_FUNC_PWM);


    slice_num_0 = pwm_gpio_to_slice_num(outputAHigh);
    slice_num_1 = pwm_gpio_to_slice_num(outputBHigh);
    slice_num_2 = pwm_gpio_to_slice_num(outputCHigh);
    channel_0 = pwm_gpio_to_channel(outputAHigh);
    channel_1 = pwm_gpio_to_channel(outputBHigh);
    channel_2 = pwm_gpio_to_channel(outputCHigh);


    pwm_set_wrap(slice_num_0, 4095);
    pwm_set_wrap(slice_num_1, 4095);
    pwm_set_wrap(slice_num_2, 4095);

    // initialise all to 0 volts
    pwm_set_chan_level(slice_num_0, channel_0, 0);
    pwm_set_chan_level(slice_num_1, channel_1, 0);
    pwm_set_chan_level(slice_num_2, channel_2, 0);

    pwm_set_enabled(slice_num_0, true);
    pwm_set_enabled(slice_num_1, true);
    pwm_set_enabled(slice_num_2, true);
    return 0;
}
