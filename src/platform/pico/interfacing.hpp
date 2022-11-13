//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== interfacing.hpp ====
//
// Header for interfacing.cpp
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "boards/pico.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "defines.hpp"

class Interface {

    int channel_a_high = pwm_gpio_to_channel(PIN_A_HIGH);
    int channel_b_high = pwm_gpio_to_channel(PIN_B_HIGH);
    int channel_c_high = pwm_gpio_to_channel(PIN_C_HIGH);
    int channel_a_low = pwm_gpio_to_channel(PIN_A_LOW);
    int channel_b_low = pwm_gpio_to_channel(PIN_B_LOW);
    int channel_c_low = pwm_gpio_to_channel(PIN_C_LOW);

    int slice_a_high = pwm_gpio_to_slice_num(PIN_A_HIGH);
    int slice_b_high = pwm_gpio_to_slice_num(PIN_B_HIGH);
    int slice_c_high = pwm_gpio_to_slice_num(PIN_C_HIGH);
    int slice_a_low = pwm_gpio_to_slice_num(PIN_A_LOW);
    int slice_b_low = pwm_gpio_to_slice_num(PIN_B_LOW);
    int slice_c_low = pwm_gpio_to_slice_num(PIN_C_LOW);

    public:
    Interface() {
        // IO Initialisation
        // stdio_init_all();

        // LED setup
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
        gpio_put(LED_PIN, 1);

        // PWM setup

        gpio_set_function(PIN_A_HIGH, GPIO_FUNC_PWM);
        gpio_set_function(PIN_B_HIGH, GPIO_FUNC_PWM);
        gpio_set_function(PIN_C_HIGH, GPIO_FUNC_PWM);
        gpio_set_function(PIN_A_LOW, GPIO_FUNC_PWM);
        gpio_set_function(PIN_B_LOW, GPIO_FUNC_PWM);
        gpio_set_function(PIN_C_LOW, GPIO_FUNC_PWM);

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

        pwm_set_enabled(pwm_gpio_to_slice_num(PIN_A_HIGH), true);
        pwm_set_enabled(pwm_gpio_to_slice_num(PIN_B_HIGH), true);
        pwm_set_enabled(pwm_gpio_to_slice_num(PIN_C_HIGH), true);
        pwm_set_enabled(pwm_gpio_to_slice_num(PIN_A_LOW), true);
        pwm_set_enabled(pwm_gpio_to_slice_num(PIN_B_LOW), true);
        pwm_set_enabled(pwm_gpio_to_slice_num(PIN_C_LOW), true);
    }

    void led(bool on_state) {
        if (on_state == true) {
            gpio_put(LED_PIN, true);
        }
        else {
            gpio_put(LED_PIN, false);
        }
    }

    void PwmALevel(int level) {
        if (level > 0) {
            pwm_set_chan_level(slice_a_low, channel_a_low, 0);
            pwm_set_chan_level(slice_a_high, channel_a_high, MIN(level, 4095));
        }
        else {
            pwm_set_chan_level(slice_a_high, channel_a_high, 0);
            pwm_set_chan_level(slice_a_low, channel_a_low, MIN(-level, 4095));
        }
    }

    void PwmBLevel(int level) {
        if (level > 0) {
            pwm_set_chan_level(slice_b_high, channel_b_high, 0);
            pwm_set_chan_level(slice_b_low, channel_b_low, MIN(level, 4095));
        }
        else {
            pwm_set_chan_level(slice_b_high, channel_b_high, 0);
            pwm_set_chan_level(slice_b_low, channel_b_low, MIN(-level, 4095));
        }
    }

    void PwmCLevel(int level) {
        if (level > 0) {
            pwm_set_chan_level(slice_c_low, channel_c_low, 0);
            pwm_set_chan_level(slice_c_high, channel_c_high, MIN(level, 4095));
        }
        else {
            pwm_set_chan_level(slice_c_high, channel_c_high, 0);
            pwm_set_chan_level(slice_c_low, channel_c_low, MIN(-level, 4095));
        }
    }
};


// Global interface declaration
extern Interface interface;
