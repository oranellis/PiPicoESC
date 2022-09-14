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
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "states.hpp"

bool core_1_loop_interupt;

// currently the following are constants but must be dynamically assigned
double v_command = 0.3; // Between 0 and 1
double field_rps_command = 120; // Flux rotation speed/synchronous speed

const int phase_steps = 1; // Can be a multiple of 2 up to 512 to reduce resolution
const int phase_res = 1536/phase_steps; // Number of steps through one sin wave


// Interupt handler for interupting running command loops
void core_1_irq_handler() {
    if (!queue_is_empty(&command_queue)) {
        Message recieved_message(' ',' ', 0);
        queue_remove_blocking(&command_queue, &recieved_message);
        if (recieved_message.type == 'm') {
            switch (recieved_message.data) {
                case (uint16_t) States::kFault: state = States::kFault; break;
                case (uint16_t) States::kInit: state = States::kInit; break;
                default: state = States::kPower; break; // change default to fault after testing
            }
        }
        else if (recieved_message.type == 'r') {
            field_rps_command = recieved_message.data;
        }
    }
}


void Init() {
    // Pulse the high and low side outputs to initialise the gate driver
    interface.SetAStatePWM('h', v_command);
    sleep_ms(1);
    interface.SetAStatePWM('f', v_command);
    sleep_ms(1);
    interface.SetAStatePWM('l', v_command);
    sleep_ms(1);
    interface.SetAStatePWM('f', v_command);
    sleep_ms(1);
    interface.SetBStatePWM('h', v_command);
    sleep_ms(1);
    interface.SetBStatePWM('f', v_command);
    sleep_ms(1);
    interface.SetBStatePWM('l', v_command);
    sleep_ms(1);
    interface.SetBStatePWM('f', v_command);
    sleep_ms(1);
    interface.SetCStatePWM('h', v_command);
    sleep_ms(1);
    interface.SetCStatePWM('f', v_command);
    sleep_ms(1);
    interface.SetCStatePWM('l', v_command);
    sleep_ms(1);
    interface.SetCStatePWM('f', v_command);
    sleep_ms(1);
    state = States::kIdle;
}


void IdleLoop() {
    interface.SetAState('f');
    interface.SetBState('f');
    interface.SetCState('f');
    while (state == States::kIdle) {
        if (v_command>0) {
            state = States::kPower;
        }
        else if (v_command<0) {
            state = States::kRegen;
        }
    }
    sleep_ms(1);
}


void ReadyLoop() {
}


void PowerLoop() {
    volatile int phase_a_level_raw, phase_b_level_raw, phase_c_level_raw;
    volatile int phase_a_level, phase_b_level, phase_c_level;
    volatile int phase_a_pos = 0, phase_b_pos = 512, phase_c_pos = 1024; // the phase angle of each output, 120deg out of phase with each other
    volatile int counter = 0; // For debugging
    volatile long timeold = time_us_64(), timenow = timeold; // For debugging
    int wait_time;

    // This while loop can be moved to the second core and this core can manage the field speed and voltage based on throttle and current motor rps
    while (1) {
        wait_time = 166667/(field_rps_command);
        /* if (loopInterupt) { */
        /* } */
        /* phase_a_pos = (phase_a_pos + phase_steps) % 1536; */
        /* phase_b_pos = (phase_b_pos + phase_steps) % 1536; */
        /* phase_c_pos = (phase_c_pos + phase_steps) % 1536; */

        /* phase_a_level_raw = fastsin[phase_a_pos]; */
        /* phase_b_level_raw = fastsin[phase_b_pos]; */
        /* phase_c_level_raw = fastsin[phase_c_pos]; */

        /* phase_a_level = phase_a_level_raw * v_command; */
        /* phase_b_level = phase_b_level_raw * v_command; */
        /* phase_c_level = phase_c_level_raw * v_command; */

        /* interface.PwmALevel(phase_a_level); */
        /* interface.PwmBLevel(phase_b_level); */
        /* interface.PwmCLevel(phase_c_level); */

        /* if (v_command <= 0) { */
        /* interface.PwmALevel(phase_a_level); */
        /*     *state = States::kIdle; */
        /*     break; */
        /* } */

        /* if (*state == States::kFault) { */
        /*     break; */
        /* } */

        /* sleep_us((1000000/(field_rps_command*phase_res))); */
        interface.SetAStatePWM('h', v_command);
        sleep_us(wait_time);
        interface.SetCStatePWM('l', v_command);
        sleep_us(wait_time);
        interface.SetBStatePWM('h', v_command);
        sleep_us(wait_time);
        interface.SetAStatePWM('l', v_command);
        sleep_us(wait_time);
        interface.SetCStatePWM('h', v_command);
        sleep_us(wait_time);
        interface.SetBStatePWM('l', v_command);
        sleep_us(wait_time);
    }
}


void RegenLoop() {
    while (1) {
        state = States::kFault;

        if (v_command >= 0) {
            state = States::kIdle;
        }

        if (state == States::kFault) {
            break;
        }
    }
}


void FaultLoop() {
}

void ChargingLoop() {

}
