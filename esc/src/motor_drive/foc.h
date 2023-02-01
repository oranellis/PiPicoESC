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

#include "motor_drive/gatedriver_io.h"
#include "motor_drive/current_sense.h"
#include "motor_drive/rpm_sense.h"

class Foc {
    private:

    // Local copy of the GatedriverIo pointer, used for commanding the gates
    GatedriverIo* gates_ptr;
    CurrentSensors* cs_ptr;
    RpmSensors* rs_ptr;


    public:

    // Default constructor for Foc, requires an gatedriver io handler
    Foc() {
        gates_ptr = new GatedriverIo();
        cs_ptr = new CurrentSensors();
        rs_ptr = new RpmSensors();
    }

    // Class destructor
    ~Foc() {
        delete gates_ptr;
        delete cs_ptr;
        delete rs_ptr;
    }

    GatedriverIo* GetGatedriverIoPtr();

    void DriveMode(int* command);
};
