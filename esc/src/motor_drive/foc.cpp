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

#define kp_i 0.04
#define ki_i 0.08

Foc::Foc(MotorCommand* motor_command_ptr_init) {

    mc_ptr = motor_command_ptr_init;

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

    int q_integration_cummulative = 0;
    int d_integration_cummulative = 0;

    while (loopingState) {

        absolute_time_t loopStartTime = get_absolute_time();

        int motorMilliRadiansPerSecond = rs_ptr->GetMilliRadiansPerSecond();

        motorPositionMilliRads = (motorPositionMilliRads + (motorMilliRadiansPerSecond * loopTimestepMicroSeconds) / 1000000);

        int a_current = cs_ptr->GetPhaseACurrentMilliAmps();
        int b_current = cs_ptr->GetPhaseBCurrentMilliAmps();
        int c_current = cs_ptr->GetPhaseCCurrentMilliAmps();

        // Clarke transform
        // Could be changed to int operation for reduced accuracy but much faster speed
        int x_current = (2 * a_current - b_current - c_current) * inv_sqrt_6;
        int y_current = (b_current - c_current) * inv_sqrt_2;
        // int Z = (aCurr + bCurr + cCurr) * inv_sqrt_3;

        // Park transform
        int cos_theta = fcos(fieldPositionMilliRads);
        int sin_theta = fsin(fieldPositionMilliRads);

        int d_current = (cos_theta * x_current + sin_theta * y_current) / 4095;
        int q_current = (cos_theta * y_current - sin_theta * x_current) / 4095;

        int d_setpoint = mc_ptr->GetDCurrent();
        int q_setpoint = mc_ptr->GetQCurrent();

        // Begin PI loops

        int d_error = d_current - d_setpoint;
        int q_error = q_current - q_setpoint;

        d_integration_cummulative += d_error * timestep;

        int d_command = d_error * kp_i + ;
        int q_command = q_error * kp_i;

// ---------------------------------------------------------------------------
        if (get_absolute_time() > loopStartTime + loopTimestepMicroSeconds) {

            loopingState = false;
        }

        sleep_until(loopStartTime + loopTimestepMicroSeconds);
    }
}
