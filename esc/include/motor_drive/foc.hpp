//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== foc.hpp ====
//
// Field Oriented Control algorithms
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "pico/stdlib.h"

#include "motor_drive/gatedriver_io.hpp"

class Foc {
    private:

    // Local copy of the GatedriverIo pointer, used for commanding the gates
    GatedriverIo* io;

    // Function to be run on core 1 for motor drive
    void Core1DriveMode(GatedriverIo* io, int* command);

    public:

    // Default constructor for Foc, requires an gatedriver io handler
    Foc(GatedriverIo* initIo): io(initIo) {}

    int DriveMode(int* command);
};
