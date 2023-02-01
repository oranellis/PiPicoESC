//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== foc.cpp ====
//
// Field Oriented Control algorithms
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "foc.hpp"

GatedriverIo* Foc::GetGatedriverIoPtr() {
    return gates_ptr;
}

void Foc::DriveMode(int* command) {

/*
    Speed measurement ->
    Position generator ->
    Sin-Cos lookup *1

    current measurements ->
    clarke transform *2

    Direct current PI loop {
    (needs to be 0)
    }

    target current ->
    Quadrature current PI loop {
    }

    inverse park transform ->
    (generates the sin waves)
    space vector modulation
    (turns it into PWM values for the phases)
*/

    unsigned int loopTimestepMicroSeconds = 100;

    int motorPositionMilliRads = 0;

    bool loopingState = true;

    while (loopingState) {

        absolute_time_t loopStartTime = get_absolute_time();

        int motorMilliRadiansPerSecond = rs_ptr->GetMilliRadiansPerSecond();

        motorPositionMilliRads = (motorPositionMilliRads + (motorMilliRadiansPerSecond * loopTimestepMicroSeconds) / 1000000);

        int phaseACurrentMilliAmps = cs_ptr->GetPhaseACurrentMilliAmps();
        int phaseBCurrentMilliAmps = cs_ptr->GetPhaseBCurrentMilliAmps();
        int phaseCCurrentMilliAmps = cs_ptr->GetPhaseCCurrentMilliAmps();

        // Clarke transform


// ---------------------------------------------------------------------------
        if (get_absolute_time() > loopStartTime + loopTimestepMicroSeconds) {

            loopingState = false;
        }

        sleep_until(loopStartTime + loopTimestepMicroSeconds);
    }
}
