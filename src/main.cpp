//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== main.cpp ====
//
// Main script containing the logic to drive an induction motor
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "pico/stdio.h"
#include "pico/time.h"

#include "maths.hpp"
#include "interfacing.hpp"
#include "states.hpp"



int main() {

    // =================== Interfacing setup ===================
    Interface i;
    Interface * interface = &i;

    States s = States::kInit; // The current controller state
    States * state = &s;

    // =================== Main Event Loop ===================

    while (1) {
        switch (*state) {
            case States::kFault: FaultLoop(interface, state); break;
            case States::kInit: Init(interface, state); break;
            case States::kIdle: IdleLoop(interface, state); break;
            case States::kReady: ReadyLoop(interface, state); break;
            case States::kPower: PowerLoop(interface, state); break;
            case States::kRegen: RegenLoop(interface, state); break;
            case States::kCharging: ChargingLoop(interface, state); break;
            default: FaultLoop(interface, state); break;
        }
    }

    return 0;
}
