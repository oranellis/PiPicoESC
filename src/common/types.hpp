//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== types.hpp ====
//
// Header file containing all commonly used types
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "pico/platform.h"


enum class States {
    kFault,
    kInit,
    kDisabled,
    kRegen,
    kCharging,
    kIdle,
    kPower
};


enum class DriveModes {
    kPark,
    kReverse,
    kNeutral,
    kEco,
    kDrive,
    kSpeeeeeed,
};


struct Message {
    char type;
    int32_t data;

    // Empty constructor
    Message() {
        type = ' ';
        data = 0;
    }

    // Populating constructor
    Message(char init_type, int32_t init_data) {
        type = init_type;
        data = init_data;
    }
};


struct MotorData {
    double v_command;
    double field_rps;

    MotorData() {
        v_command = 0;
        field_rps = 0;
    }

    MotorData(double init_v_command, double init_field_rps) {
        v_command = init_v_command;
        field_rps = init_field_rps;
    }
};
