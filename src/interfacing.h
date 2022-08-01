#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"
#define PICO_COMPILED

int iosetup() {
    
    #ifdef PICO_COMPILED
     // IO Initialisation 
    stdio_init_all();

    // LED setup
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // PWM setup
    pwm_config cfg = pwm_get_default_config();
    gpio_set_function(22, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(22);
    pwm_set_gpio_level(22, 32768);
    pwm_set_enabled(22, true);

    return 0;
    #endif
}