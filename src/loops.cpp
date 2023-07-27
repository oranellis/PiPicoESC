//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "loops.h"

void DriveLoop(int* error_code_ptr) {

	// read sensors for required values

	float i_a = 0;
	float i_b = 0;
	float i_c = 0;

	float v_a = 0;
	float v_b = 0;
	float v_c = 0;

	float v_hv = 0;

	float mot_rot_spd = 0;
	float mot_pos = 0;

	float timestep = 0.00004;

	// Main loop
	while (!*error_code_ptr) {

		// Safety checks
		if (v_hv < HvInput::v_min || v_hv > HvInput::v_max) {

			*error_code_ptr = 1;
			break;

		}

		// Populate measurement vars
		i_a = PhaseCurrent::GetA();
		i_b = PhaseCurrent::GetB();
		i_c = PhaseCurrent::GetC();

		v_a = PhaseVoltage::GetA();
		v_b = PhaseVoltage::GetB();
		v_c = PhaseVoltage::GetC();

		v_hv = HvInput::GetVoltage();

		mot_rot_spd = MotorRotation::GetVel();

		mot_pos = mot_pos + (mot_rot_spd * timestep);

        // Clarke transform
        float i_x = (2 * i_a - i_b - i_c) * inv_sqrt_6;
        float i_y = (i_b - i_c) * inv_sqrt_2;
        // float z_current = (a_current + b_current + c_current) * inv_sqrt_3;


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


        // absolute_time_t loop_start_time = get_absolute_time();

        // float motor_radians_per_second = rs_ptr->GetMilliRadiansPerSecond();

        // motor_position_rads = (motor_position_rads + \
        //                        (motor_radians_per_second * loop_timestep) \
        //                        / 1000000);

        // float a_current = (float)cs_ptr->GetPhaseACurrentMilliAmps()/1000;
        // float b_current = (float)cs_ptr->GetPhaseBCurrentMilliAmps()/1000;
        // float c_current = (float)cs_ptr->GetPhaseCCurrentMilliAmps()/1000;

        // // Clarke transform
        // float x_current = (2 * a_current - b_current - c_current) * inv_sqrt_6;
        // float y_current = (b_current - c_current) * inv_sqrt_2;
        // // float z_current = (a_current + b_current + c_current) * inv_sqrt_3;

        // // Park transform
        // float cos_theta = fcos((int)roundf(field_position_rads * 1000));
        // float sin_theta = fsin((int)roundf(field_position_rads * 1000));

        // float d_current = (cos_theta * x_current + sin_theta * y_current) / 4095;
        // float q_current = (cos_theta * y_current - sin_theta * x_current) / 4095;

        // float d_setpoint = mc_ptr->GetDCurrentSetpoint();
        // float q_setpoint = mc_ptr->GetQCurrentSetpoint();

        // // PI loops
        // float d_error = d_current - d_setpoint;
        // float q_error = q_current - q_setpoint;

        // d_integration_cummulative += d_error * loop_timestep; // Unbounded
        // q_integration_cummulative += q_error * loop_timestep; // Unbounded

        // float d_command = d_error * kp_i + d_integration_cummulative * ki_i;
        // float q_command = q_error * kp_i + q_integration_cummulative * ki_i;

        // // Inverse park transform
        // float x_command = cos_theta * d_command - sin_theta * q_command;
        // float y_command = sin_theta * d_command + cos_theta * q_command;

        // // Inverse clarke transform
        // float a_command = sqrt_2_over_3 * x_command;
        // float b_command = -inv_sqrt_6 * x_command;
        // float c_command = b_command - inv_sqrt_2 * y_command;
        // b_command += inv_sqrt_2 * y_command;

	}

	return;

}

void ChargeLoop(int* error_code_ptr) {

	return;

}
