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
#define ki_i 0.0 // Off for now

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

    float loop_timestep = 0.0001;

    float motor_position_rads = 0;
    float field_position_rads = 0;

    bool looping_state = true;

    float d_integration_cummulative = 0;
    float q_integration_cummulative = 0;

    while (looping_state) {

        absolute_time_t loop_start_time = get_absolute_time();

        float motor_radians_per_second = rs_ptr->GetMilliRadiansPerSecond();

        motor_position_rads = (motor_position_rads + \
                               (motor_radians_per_second * loop_timestep) \
                               / 1000000);

        float a_current = (float)cs_ptr->GetPhaseACurrentMilliAmps()/1000;
        float b_current = (float)cs_ptr->GetPhaseBCurrentMilliAmps()/1000;
        float c_current = (float)cs_ptr->GetPhaseCCurrentMilliAmps()/1000;

        // Clarke transform
        float x_current = (2 * a_current - b_current - c_current) * inv_sqrt_6;
        float y_current = (b_current - c_current) * inv_sqrt_2;
        // float z_current = (a_current + b_current + c_current) * inv_sqrt_3;

        // Park transform
        float cos_theta = fcos((int)roundf(field_position_rads * 1000));
        float sin_theta = fsin((int)roundf(field_position_rads * 1000));

        float d_current = (cos_theta * x_current + sin_theta * y_current) / 4095;
        float q_current = (cos_theta * y_current - sin_theta * x_current) / 4095;

        float d_setpoint = mc_ptr->GetDCurrentSetpoint();
        float q_setpoint = mc_ptr->GetQCurrentSetpoint();

        // PI loops
        float d_error = d_current - d_setpoint;
        float q_error = q_current - q_setpoint;

        d_integration_cummulative += d_error * loop_timestep; // Unbounded
        q_integration_cummulative += q_error * loop_timestep; // Unbounded

        float d_command = d_error * kp_i + d_integration_cummulative * ki_i;
        float q_command = q_error * kp_i + q_integration_cummulative * ki_i;

        // Inverse park transform
        float x_command = cos_theta * d_command - sin_theta * q_command;
        float y_command = sin_theta * d_command + cos_theta * q_command;

        float a_command = x_command;
        float b_command;
        float c_command;


// ---------------------------------------------------------------------------
        if (get_absolute_time() > loop_start_time + loop_timestep) {

            looping_state = false;
        }

        sleep_until(loop_start_time + loop_timestep);
    }
}
