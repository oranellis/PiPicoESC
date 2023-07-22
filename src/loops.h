//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "peripherals/throttle.h"
#include "peripherals/reverse.h"
#include "peripherals/current.h"
#include "peripherals/voltage.h"
#include "peripherals/hv_battery.h"

void DriveLoop(int* error_code_ptr);

void ChargeLoop(int* error_code_ptr);
