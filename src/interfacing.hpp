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
<<<<<<< HEAD

#include <stdio.h>
=======
>>>>>>> gatedriver_testing

#include "boards/pico.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "defines.hpp"

#define PIN_A_HIGH 5
#define PIN_B_HIGH 4
#define PIN_C_HIGH 3
#define PIN_A_LOW 2
#define PIN_B_LOW 1
#define PIN_C_LOW 0
#define LED_PIN PICO_DEFAULT_LED_PIN

#define HARDWARE_PWM

class Interface {

    private:
    // Define output pins
    uint slice_a_high;
    uint slice_b_high;
    uint slice_c_high;
    uint slice_a_low;
    uint slice_b_low;
    uint slice_c_low;
    uint channel_a_high;
    uint channel_b_high;
    uint channel_c_high;
    uint channel_a_low;
    uint channel_b_low;
    uint channel_c_low;

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

        slice_a_high = pwm_gpio_to_slice_num(PIN_A_HIGH);
        slice_b_high = pwm_gpio_to_slice_num(PIN_B_HIGH);
        slice_c_high = pwm_gpio_to_slice_num(PIN_C_HIGH);
        slice_a_low = pwm_gpio_to_slice_num(PIN_A_LOW);
        slice_b_low = pwm_gpio_to_slice_num(PIN_B_LOW);
        slice_c_low = pwm_gpio_to_slice_num(PIN_C_LOW);

        channel_a_high = pwm_gpio_to_channel(PIN_A_HIGH);
        channel_b_high = pwm_gpio_to_channel(PIN_B_HIGH);
        channel_c_high = pwm_gpio_to_channel(PIN_C_HIGH);
        channel_a_low = pwm_gpio_to_channel(PIN_A_LOW);
        channel_b_low = pwm_gpio_to_channel(PIN_B_LOW);
        channel_c_low = pwm_gpio_to_channel(PIN_C_LOW);

        pwm_set_wrap(slice_a_high, 4095);
        pwm_set_wrap(slice_b_high, 4095);
        pwm_set_wrap(slice_c_high, 4095);
        pwm_set_wrap(slice_a_low, 4095);
        pwm_set_wrap(slice_b_low, 4095);
        pwm_set_wrap(slice_c_low, 4095);

        // initialise all to 0 volts
        pwm_set_chan_level(slice_a_high, channel_a_high, 0);
        pwm_set_chan_level(slice_b_high, channel_b_high, 0);
        pwm_set_chan_level(slice_c_high, channel_c_high, 0);
        pwm_set_chan_level(slice_a_low, channel_a_low, 0);
        pwm_set_chan_level(slice_b_low, channel_b_low, 0);
        pwm_set_chan_level(slice_c_low, channel_c_low, 0);

        pwm_set_enabled(slice_a_high, true);
        pwm_set_enabled(slice_b_high, true);
        pwm_set_enabled(slice_c_high, true);
        pwm_set_enabled(slice_a_low, true);
        pwm_set_enabled(slice_b_low, true);
        pwm_set_enabled(slice_c_low, true);
        /* for (int i=0; i<6; i++) { */
        /*     gpio_init(i); */
        /*     gpio_set_dir(i, GPIO_OUT); */
        /* } */
    }

    void PwmALevel(int level) {
        if (level > 0) {
            pwm_set_chan_level(slice_a_low, channel_a_low, 0);
            pwm_set_chan_level(slice_a_high, channel_a_high, MIN(level, 4095));
        }
        else if (level < 0) {
            pwm_set_chan_level(slice_a_high, channel_a_high, 0);
            pwm_set_chan_level(slice_a_low, channel_a_low, MIN(-level, 4095));
        }
        else {
            pwm_set_chan_level(slice_a_high, channel_a_high, 0);
            pwm_set_chan_level(slice_a_low, channel_a_low, 0);
        }
    }

    void PwmBLevel(int level) {
        if (level > 0) {
            pwm_set_chan_level(slice_b_high, channel_b_high, MIN(level, 4095));
            pwm_set_chan_level(slice_b_low, channel_b_low, 0);
        }
        else if (level < 0) {
            pwm_set_chan_level(slice_b_high, channel_b_high, 0);
            pwm_set_chan_level(slice_b_low, channel_b_low, MIN(-level, 4095));
        }
        else {
            pwm_set_chan_level(slice_b_high, channel_b_high, 0);
            pwm_set_chan_level(slice_b_low, channel_b_low, 0);
        }
    }

    void PwmCLevel(int level) {
        if (level > 0) {
            pwm_set_chan_level(slice_c_high, channel_c_high, MIN(level, 4095));
            pwm_set_chan_level(slice_c_low, channel_c_low, 0);
        }
        else if (level < 0) {
            pwm_set_chan_level(slice_c_high, channel_c_high, 0);
            pwm_set_chan_level(slice_c_low, channel_c_low, MIN(-level, 4095));
        }
        else {
            pwm_set_chan_level(slice_c_high, channel_c_high, 0);
            pwm_set_chan_level(slice_c_low, channel_c_low, 0);
        }
    }


    // Set the state of the phase to (h)igh, (l)ow or (f)loating
    void SetAState(char high_low) {
        if (high_low == 'h') {
            gpio_put(PIN_A_LOW, false);
            gpio_put(PIN_A_HIGH, true);
            return;
        }
        if (high_low == 'l') {
            gpio_put(PIN_A_HIGH, false);
            gpio_put(PIN_A_LOW, true);
            return;
        }
        if (high_low == 'f') {
            gpio_put(PIN_A_HIGH, false);
            gpio_put(PIN_A_LOW, false);
            return;
        }
    }

    // Set the state of the phase to (h)igh, (l)ow or (f)loating
    void SetBState(char high_low) {
        if (high_low == 'h') {
            gpio_put(PIN_B_LOW, false);
            gpio_put(PIN_B_HIGH, true);
            return;
        }
        if (high_low == 'l') {
            gpio_put(PIN_B_HIGH, false);
            gpio_put(PIN_B_LOW, true);
            return;
        }
        if (high_low == 'f') {
            gpio_put(PIN_B_HIGH, false);
            gpio_put(PIN_B_LOW, false);
            return;
        }
    }

    // Set the state of the phase to (h)igh, (l)ow or (f)loating
    void SetCState(char high_low) {
        if (high_low == 'h') {
            gpio_put(PIN_B_LOW, false);
            gpio_put(PIN_B_HIGH, true);
            return;
        }
        if (high_low == 'l') {
            gpio_put(PIN_B_HIGH, false);
            gpio_put(PIN_B_LOW, true);
            return;
        }
        if (high_low == 'f') {
            gpio_put(PIN_B_HIGH, false);
            gpio_put(PIN_B_LOW, false);
            return;
        }
    }
    // Set the state of the phase to (h)igh, (l)ow or (f)loating
    void SetAStatePWM(char high_low, double v_command) {
        if (high_low == 'h') {
            pwm_set_chan_level(slice_a_high, channel_a_high, v_command*4095);
            pwm_set_chan_level(slice_a_low, channel_a_low, 0);
            return;
        }
        if (high_low == 'l') {
            pwm_set_chan_level(slice_a_high, channel_a_high, 0);
            pwm_set_chan_level(slice_a_low, channel_a_low, v_command*4095);
            return;
        }
        if (high_low == 'f') {
            pwm_set_chan_level(slice_a_high, channel_a_high, 0);
            pwm_set_chan_level(slice_a_low, channel_a_low, 0);
            return;
        }
    }

    // Set the state of the phase to (h)igh, (l)ow or (f)loating
    void SetBStatePWM(char high_low, double v_command) {
        if (high_low == 'h') {
            pwm_set_chan_level(slice_b_high, channel_b_high, v_command*4095);
            pwm_set_chan_level(slice_b_low, channel_b_low, 0);
            return;
        }
        if (high_low == 'l') {
            pwm_set_chan_level(slice_b_high, channel_b_high, 0);
            pwm_set_chan_level(slice_b_low, channel_b_low, v_command*4095);
            return;
        }
        if (high_low == 'f') {
            pwm_set_chan_level(slice_b_high, channel_b_high, 0);
            pwm_set_chan_level(slice_b_low, channel_b_low, 0);
            return;
        }
    }

    // Set the state of the phase to (h)igh, (l)ow or (f)loating
    void SetCStatePWM(char high_low, double v_command) {
        if (high_low == 'h') {
            pwm_set_chan_level(slice_c_high, channel_c_high, v_command*4095);
            pwm_set_chan_level(slice_c_low, channel_c_low, 0);
            return;
        }
        if (high_low == 'l') {
            pwm_set_chan_level(slice_c_high, channel_c_high, 0);
            pwm_set_chan_level(slice_c_low, channel_c_low, v_command*4095);
            return;
        }
        if (high_low == 'f') {
            pwm_set_chan_level(slice_c_high, channel_c_high, 0);
            pwm_set_chan_level(slice_c_low, channel_c_low, 0);
            return;
        }
    }
};
