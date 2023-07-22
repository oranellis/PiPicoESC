//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "hv_battery.h"

float HvBattery::cell_v_min = 3.4;
float HvBattery::cell_v_max = 3.75;

float HvBattery::v_min = 122.4;
float HvBattery::v_max = 135.0;

