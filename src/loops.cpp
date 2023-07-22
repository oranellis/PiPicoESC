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

	float i_a = GetACurrent();
	float i_b = GetBCurrent();
	float i_c = GetCCurrent();

	float v_a = GetAVoltage();
	float v_b = GetBVoltage();
	float v_c = GetCVoltage();

	float v_hv = GetHvVoltage();
	float v_lv = GetLvVoltage();

	// Safety checks

	if (v_hv < HvBattery::v_min || v_hv > HvBattery::v_max) {

		*error_code_ptr = 1;
		return;

	}

	// Phase control calculations

}

void ChargeLoop(int* error_code_ptr) {

	return;

}
