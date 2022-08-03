#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"
#include <stdio.h>

// Define output pins
#define output0 0
#define output1 1
#define output2 2
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
    gpio_set_function(output0, GPIO_FUNC_PWM);
    gpio_set_function(output1, GPIO_FUNC_PWM);
    gpio_set_function(output2, GPIO_FUNC_PWM);


    slice_num_0 = pwm_gpio_to_slice_num(output0);
    slice_num_1 = pwm_gpio_to_slice_num(output1);
    slice_num_2 = pwm_gpio_to_slice_num(output2);
    channel_0 = pwm_gpio_to_channel(output0);
    channel_1 = pwm_gpio_to_channel(output1);
    channel_2 = pwm_gpio_to_channel(output2);


    pwm_set_wrap(slice_num_0, 65535);
    pwm_set_wrap(slice_num_1, 65535);
    pwm_set_wrap(slice_num_2, 65535);

    // initialise all to 0 volts
    pwm_set_chan_level(slice_num_0, channel_0, 0);
    pwm_set_chan_level(slice_num_1, channel_1, 0);
    pwm_set_chan_level(slice_num_2, channel_2, 0);

    pwm_set_enabled(slice_num_0, true);
    pwm_set_enabled(slice_num_1, true);
    pwm_set_enabled(slice_num_2, true);
    return 0;
}
