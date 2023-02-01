//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== foc.h ====
//
// Field Oriented Control algorithms
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "pico/stdlib.h"

#include "defines.h"
#include "motor_drive/gatedriver_io.h"
#include "motor_drive/current_sense.h"
#include "motor_drive/rpm_sense.h"

class Foc {
    private:

    GatedriverIo* gates_ptr;
    CurrentSensors* cs_ptr;
    RpmSensors* rs_ptr;


    public:

    Foc();

    ~Foc();

    GatedriverIo* GetGatedriverIoPtr();

    void DriveMode(int* command);
};
