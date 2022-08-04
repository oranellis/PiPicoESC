#include "controller_maths.h"
#include "interfacing.h"
#include "enums.h"

#include "pico/stdlib.h"
#include "pico/time.h"

#include <stdio.h>

volatile double v_command = 1; // Between 0 and 32767
volatile enum states state = s_power; // set to power for testing

volatile double field_rps_command = 8;
const int phase_steps = 1; // Can be a multiple of 2 up to 512
const int phase_res = 1536/phase_steps;


void PowerLoop() {
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

        PwmALevel(phase_a_level);
        PwmBLevel(phase_b_level);
        PwmCLevel(phase_c_level);

        if (v_command <= 0) {
        PwmALevel(phase_a_level);
            state = s_idle;
            break;
        }

        if (state == s_fault) {
            break;
        }

        sleep_us((1000000/(field_rps_command*phase_res)));
    }
}


void RegenLoop() {
    while (1) {
        state = s_fault;

        if (v_command >= 0) {
            state = s_idle;
        }

        if (state == s_fault) {
            break;
        }
    }
}


void FaultLoop() {
}




int main() {

    // =================== Interfacing setup ===================
    if (IoSetup() != 0) {
        printf("eFailed to initialise IO");
        return 1;
    }

    // =================== Main Event Loop ===================

    while (1) {
        switch (state) {
            // case s_fault: FaultLoop(); break;
            // case s_init: Init(); break;
            // case s_idle: IdleLoop(); break;
            // case s_ready: ReadyLoop(); break;
            case s_power: PowerLoop(); break;
            // case s_regen: RegenLoop(); break;
           default: FaultLoop(); break;
        }
    }

    return 0;
}
