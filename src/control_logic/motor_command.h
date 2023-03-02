//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== motor_command.h ====
//
// Rpm sensing
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "motor_drive/safety.h"

class MotorCommand {

    private:

    enum mode {
        current,
        rpm
    };

    int throttle = 0; // between -1000 and 1000
    int iq_command = 0; // commanded Q current
    int id_command = 0; // commanded D current, for field weakening
    bool regen = false;
    mode current_mode = mode::current;

    public:

    MotorCommand();

    ~MotorCommand();

    void SetRpm(int throttle);

    void SetThrottle(int throttle);

    void SetRegen(int regen_throttle);

    int GetQCurrentSetpoint();

    int GetDCurrentSetpoint();
};
