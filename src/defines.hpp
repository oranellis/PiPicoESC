//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== defines.hpp ====
//
// Header containing all user defined constants for use by the ESC
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "boards/pico.h"

#define PIN_A_HIGH 5
#define PIN_B_HIGH 4
#define PIN_C_HIGH 3
#define PIN_A_LOW 2
#define PIN_B_LOW 1
#define PIN_C_LOW 0
#define LED_PIN PICO_DEFAULT_LED_PIN

#define MOTOR_KV // For testing with BLDC's
#define MAX_V // For testing
#define MAX_RPS (MOTOR_KV*MAX_V/60)
#define HZ_V (MAX_RPS/MAX_V)
