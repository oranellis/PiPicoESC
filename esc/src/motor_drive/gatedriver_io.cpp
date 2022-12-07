#include "motor_drive/gatedriver_io.hpp"

GatedriverIo::GatedriverIo() {
    // IO Initialisation
    // stdio_init_all();

    // LED setup
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    // PWM pin setup
    gpio_set_function(PIN_A_HIGH, GPIO_FUNC_PWM);
    gpio_set_function(PIN_B_HIGH, GPIO_FUNC_PWM);
    gpio_set_function(PIN_C_HIGH, GPIO_FUNC_PWM);
    gpio_set_function(PIN_A_LOW, GPIO_FUNC_PWM);
    gpio_set_function(PIN_B_LOW, GPIO_FUNC_PWM);
    gpio_set_function(PIN_C_LOW, GPIO_FUNC_PWM);

    // Defines wraparound value such that PWM frequency is ~30kHz
    pwm_set_wrap(pwm_gpio_to_slice_num(PIN_A_HIGH), 4095);
    pwm_set_wrap(pwm_gpio_to_slice_num(PIN_B_HIGH), 4095);
    pwm_set_wrap(pwm_gpio_to_slice_num(PIN_C_HIGH), 4095);
    pwm_set_wrap(pwm_gpio_to_slice_num(PIN_A_LOW), 4095);
    pwm_set_wrap(pwm_gpio_to_slice_num(PIN_B_LOW), 4095);
    pwm_set_wrap(pwm_gpio_to_slice_num(PIN_C_LOW), 4095);

    // initialise all to 0 volts
    pwm_set_chan_level(pwm_gpio_to_slice_num(PIN_A_HIGH), pwm_gpio_to_channel(PIN_A_HIGH), 0);
    pwm_set_chan_level(pwm_gpio_to_slice_num(PIN_B_HIGH), pwm_gpio_to_channel(PIN_B_HIGH), 0);
    pwm_set_chan_level(pwm_gpio_to_slice_num(PIN_C_HIGH), pwm_gpio_to_channel(PIN_C_HIGH), 0);
    pwm_set_chan_level(pwm_gpio_to_slice_num(PIN_A_LOW), pwm_gpio_to_channel(PIN_A_LOW), 0);
    pwm_set_chan_level(pwm_gpio_to_slice_num(PIN_B_LOW), pwm_gpio_to_channel(PIN_B_LOW), 0);
    pwm_set_chan_level(pwm_gpio_to_slice_num(PIN_C_LOW), pwm_gpio_to_channel(PIN_C_LOW), 0);

    // enable all pins
    pwm_set_enabled(pwm_gpio_to_slice_num(PIN_A_HIGH), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(PIN_B_HIGH), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(PIN_C_HIGH), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(PIN_A_LOW), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(PIN_B_LOW), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(PIN_C_LOW), true);
}


void GatedriverIo::led(bool on_state) {
    if (on_state == true) {
        gpio_put(LED_PIN, true);
    }
    else {
        gpio_put(LED_PIN, false);
    }
}

void GatedriverIo::PwmALevel(int level) {
    if (level > 0) {
        pwm_set_chan_level(slice_a_low, channel_a_low, 0);
        pwm_set_chan_level(slice_a_high, channel_a_high, MIN(level, 4095));
    }
    else {
        pwm_set_chan_level(slice_a_high, channel_a_high, 0);
        pwm_set_chan_level(slice_a_low, channel_a_low, MIN(-level, 4095));
    }
}

void GatedriverIo::PwmBLevel(int level) {
    if (level > 0) {
        pwm_set_chan_level(slice_b_high, channel_b_high, 0);
        pwm_set_chan_level(slice_b_low, channel_b_low, MIN(level, 4095));
    }
    else {
        pwm_set_chan_level(slice_b_high, channel_b_high, 0);
        pwm_set_chan_level(slice_b_low, channel_b_low, MIN(-level, 4095));
    }
}

void GatedriverIo::PwmCLevel(int level) {
    if (level > 0) {
        pwm_set_chan_level(slice_c_low, channel_c_low, 0);
        pwm_set_chan_level(slice_c_high, channel_c_high, MIN(level, 4095));
    }
    else {
        pwm_set_chan_level(slice_c_high, channel_c_high, 0);
        pwm_set_chan_level(slice_c_low, channel_c_low, MIN(-level, 4095));
    }
}
