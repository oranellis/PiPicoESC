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

#include "foc.h"

#define inv_sqrt_6 0.4082482904
#define inv_sqrt_3 0.5773502692
#define inv_sqrt_2 0.7071067811

Foc::Foc() {
    gates_ptr = new GatedriverIo();
    cs_ptr = new CurrentSensors();
    rs_ptr = new RpmSensors();
}

Foc::~Foc() {
    delete gates_ptr;
    delete cs_ptr;
    delete rs_ptr;
}

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
    int fieldPositionMilliRads = 0;

    bool loopingState = true;

    while (loopingState) {

        absolute_time_t loopStartTime = get_absolute_time();

        int motorMilliRadiansPerSecond = rs_ptr->GetMilliRadiansPerSecond();

        motorPositionMilliRads = (motorPositionMilliRads + (motorMilliRadiansPerSecond * loopTimestepMicroSeconds) / 1000000);

        int aCurr = cs_ptr->GetPhaseACurrentMilliAmps();
        int bCurr = cs_ptr->GetPhaseBCurrentMilliAmps();
        int cCurr = cs_ptr->GetPhaseCCurrentMilliAmps();

        // Clarke transform
        // Could be changed to int operation for reduced accuracy but much faster speed
        int X = (2 * aCurr - bCurr - cCurr) * inv_sqrt_6;
        int Y = (bCurr - cCurr) * inv_sqrt_2;
        // int Z = (aCurr + bCurr + cCurr) * inv_sqrt_3;

        // Park transform
        int cosTh = fcos(fieldPositionMilliRads);
        int sinTh = fsin(fieldPositionMilliRads);

        int D = (cosTh * X + sinTh * Y) / 4095;
        int Q = (cosTh * Y - sinTh * X) / 4095;

        int target_current = GetTargetCurrent();

// ---------------------------------------------------------------------------
        if (get_absolute_time() > loopStartTime + loopTimestepMicroSeconds) {

            loopingState = false;
        }

        sleep_until(loopStartTime + loopTimestepMicroSeconds);
    }
}
