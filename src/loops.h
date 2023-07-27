//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "peripherals/throttle.h"
#include "peripherals/reverse.h"
#include "peripherals/phase_current.h"
#include "peripherals/phase_voltage.h"
#include "peripherals/hv_input.h"
#include "peripherals/motor_rotation.h"

#define inv_sqrt_2 0.707107
#define inv_sqrt_3 0.577350
#define inv_sqrt_6 0.408248

void DriveLoop(int* error_code_ptr);

void ChargeLoop(int* error_code_ptr);
