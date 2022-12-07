#pragma once

#include "boards/pico.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "common/defines.hpp"

class GatedriverIo {

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

    // Default constructor for GatedriverIo, performs gpio setup and PWM
    // initialisation
    GatedriverIo();

    // Sets the state of the led to on_state
    void led(bool on_state);

    // Sets pwm output level for the gate driver on either the high side
    // (positive level) or the low side (negative level)
    void PwmALevel(int level);

    // Sets pwm output level for the gate driver on either the high side
    // (positive level) or the low side (negative level)
    void PwmBLevel(int level);

    // Sets pwm output level for the gate driver on either the high side
    // (positive level) or the low side (negative level)
    void PwmCLevel(int level);
};
