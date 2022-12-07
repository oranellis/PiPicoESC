#pragma once

#include "pico/stdlib.h"

#include "motor_drive/gatedriver_io.hpp"

class Foc {
    private:

    // Local copy of the GatedriverIo pointer, used for commanding the gates
    GatedriverIo* io;

    // Function to be run on core 1 for motor drive
    void Core1Drive(GatedriverIo* io, int* command);

    public:

    // Default constructor for Foc, requires an gatedriver io handler
    Foc(GatedriverIo* initIo): io(initIo) {}

    int DriveForwards(int* command);
};
