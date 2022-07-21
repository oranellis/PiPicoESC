#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"

int main() {
    // LED setup
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // PWM setup
    gpio_init(22);
    gpio_set_function(22, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(22);
    pwm_set_gpio_level(22, 32768);
    pwm_set_enabled(22, true);

    // LED loop
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }
}
