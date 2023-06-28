//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "limits.h"
#include "peripherals/throttle.h"
#include "peripherals/reverse.h"
#include "peripherals/current.h"
#include "peripherals/voltage.h"

void Loop4khz();

void Loop100hz(float* throttle_ptr, bool* reverse_ptr, bool* charging_ptr, int* errorcode_ptr);
