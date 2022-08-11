//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== states.cpp ====
//
// Source file for drive state specific functions
//
// authored by: Oran Ellis, Karl Hartmann
// licence: GPLv3

#include "interfacing.h"
#include "states.h"
#include "controller_maths.h"


// currently the following are constants but must be dynamically assigned 
double v_command = 1; // Between 0 and 1
double field_rps_command = 8; // Flux rotation speed/synchronous speed
const int phase_steps = 1; // Can be a multiple of 2 up to 512 to reduce resolution
const int phase_res = 1536/phase_steps; // Number of steps through one sin wave



void Init(Interface* interface, States* state) {
}


void IdleLoop(Interface* interface, States* state) {
}


void ReadyLoop(Interface* interface, States* state) {
}


void PowerLoop(Interface* interface, States* state) {
    volatile int phase_a_level_raw, phase_b_level_raw, phase_c_level_raw;
    volatile int phase_a_level, phase_b_level, phase_c_level;
    volatile int phase_a_pos = 0, phase_b_pos = 512, phase_c_pos = 1024; // the phase angle of each output, 120deg out of phase with each other
    volatile int counter = 0; // For debugging
    volatile long timeold = time_us_64(), timenow = timeold; // For debugging

    // This while loop can be moved to the second core and this core can manage the field speed and voltage based on throttle and current motor rps
    while (1) {
        phase_a_pos = (phase_a_pos + phase_steps) % 1536;
        phase_b_pos = (phase_b_pos + phase_steps) % 1536;
        phase_c_pos = (phase_c_pos + phase_steps) % 1536;

        phase_a_level_raw = fastsin[phase_a_pos];
        phase_b_level_raw = fastsin[phase_b_pos];
        phase_c_level_raw = fastsin[phase_c_pos];

        phase_a_level = phase_a_level_raw * v_command;
        phase_b_level = phase_b_level_raw * v_command;
        phase_c_level = phase_c_level_raw * v_command;

        interface->PwmALevel(phase_a_level);
        interface->PwmBLevel(phase_b_level);
        interface->PwmCLevel(phase_c_level);

        if (v_command <= 0) {
        interface->PwmALevel(phase_a_level);
            *state = States::kIdle;
            break;
        }

        if (*state == States::kFault) {
            break;
        }

        sleep_us((1000000/(field_rps_command*phase_res)));
    }
}


void RegenLoop(Interface* interface, States* state) {
    while (1) {
        *state = States::kFault;

        if (v_command >= 0) {
            *state = States::kIdle;
        }

        if (*state == States::kFault) {
            break;
        }
    }
}


void FaultLoop(Interface* interface, States* state) {
}

void ChargingLoop(Interface* interface, States* state) {

}
