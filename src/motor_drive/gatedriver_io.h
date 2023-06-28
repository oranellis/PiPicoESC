//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== gatedriver_io.h ====
//
// Contains wrapper functions for controlling the gate driver IC
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "boards/pico.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "defines.h"

// Contains wrapper functions for controlling the gate driver IC
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

    GatedriverIo();

    void SetLedState(bool on_state);

    // Sets pwm output level for the gate driver on either the high side
    // (positive level) or the low side (negative level)
    void SetPwmALevel(int level);

    // Sets pwm output level for the gate driver on either the high side
    // (positive level) or the low side (negative level)
    void SetPwmBLevel(int level);

    // Sets pwm output level for the gate driver on either the high side
    // (positive level) or the low side (negative level)
    void SetPwmCLevel(int level);
};
