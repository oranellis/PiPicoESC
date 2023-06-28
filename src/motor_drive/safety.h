//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== safety.h ====
//
// Contains check functions to ensure the ESC is functioning properly
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#define MOTOR_TEMP_THRESHOLD 343000;
#define MOTOR_TEMP_LIMIT 363000;
#define IGBT_TEMP_THRESHOLD 343000;
#define IGBT_TEMP_LIMIT 373000;

class Safety {

    private:

    int motor_temp = 293000; // thousanths of a degree kelvin
    int igbt_temp = 293000; // thousanths of a degree kelvin
};
