//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== motor.hpp ====
//
// Contains motor specific functions
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "defines.hpp"
#include "types.hpp"


inline MotorData motor_data_from_throttle(double throttle) {
    return MotorData(throttle, MAX_RPS*throttle);
}
