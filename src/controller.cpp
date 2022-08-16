//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== controller.cpp ====
//
// Main script containing the logic to drive an induction motor
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "pico/stdio.h"
#include "pico/time.h"

#include "controller_maths.h"
#include "interfacing.h"
#include "states.h"



int main() {

    // =================== Interfacing setup ===================
    Interface i;
    Interface * interface = &i;

    States state = States::kPower; // The current controller state

    // =================== Main Event Loop ===================

    while (1) {
        switch (state) {
            case States::kFault: FaultLoop(); break;
            case States::kInit: Init(); break;
            case States::kIdle: IdleLoop(); break;
            case States::kReady: ReadyLoop(); break;
            case States::kPower: PowerLoop(interface); break;
            case States::kRegen: RegenLoop(); break;
            case States::kCharging: ChargingLoop(); break;
            default: FaultLoop(); break;
        }
    }

    return 0;
}
