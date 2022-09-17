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
const int phase_steps = 1; // Can be a multiple of 2 up to 512 to reduce resolution
const int phase_res = 1536/phase_steps; // Number of steps through one sin wave


// Interupt handler for interupting running command loops, not sure how to fire an interupt though so not used yet
// void core_1_irq_handler() {
//     if (!queue_is_empty(&command_queue)) {
//         Message recieved_message;
//         queue_remove_blocking(&command_queue, &recieved_message);
//         if (recieved_message.type == 'm') {
//             state = (States) recieved_message.data;
//         }
//         else if (recieved_message.type == 'r') {
//             field_rps_command = recieved_message.data;
//         }
//     }
// }


void Init() {
    // Pulse the high and low side outputs to initialise the gate driver
    interface.PwmALevel(4095);
    sleep_ms(1);
    interface.PwmALevel(0);
    sleep_ms(1);
    interface.PwmALevel(-4095);
    sleep_ms(1);
    interface.PwmALevel(0);
    sleep_ms(1);
    interface.PwmBLevel(4095);
    sleep_ms(1);
    interface.PwmBLevel(0);
    sleep_ms(1);
    interface.PwmBLevel(-4095);
    sleep_ms(1);
    interface.PwmBLevel(0);
    sleep_ms(1);
    interface.PwmCLevel(4095);
    sleep_ms(1);
    interface.PwmCLevel(0);
    sleep_ms(1);
    interface.PwmCLevel(-4095);
    sleep_ms(1);
    interface.PwmCLevel(0);
    sleep_ms(1);
    state = States::kIdle;
}


void IdleLoop() {
    double field_rps;
    double v_command;
    Message message;

    interface.PwmALevel(0);
    interface.PwmBLevel(0);
    interface.PwmCLevel(0);

    while (state == States::kIdle) {
        if (!queue_is_empty(&command_queue)) {
            while (!queue_is_empty(&command_queue)) {
                queue_remove_blocking(&command_queue, &message);
                switch (message.type) {
                    case 't':
                        double throttle = message.data / 1000;
                        MotorData motor_data = motor_data_from_throttle(throttle);
                        field_rps = motor_data.field_rps;
                        v_command = motor_data.v_command;
                        break;
                    case 'm':
                        state = static_cast<States>(message.data);
                        break;
                }
            }
            if (state != States::kPower) {
                break;
            }
        }
        if (v_command>0) {
            state = States::kPower;
        }
        else if (v_command<0) {
            state = States::kRegen;
        }
    }
    sleep_ms(1);
}


void PowerLoop() {
    volatile int phase_pos;
    volatile int phase_a_level, phase_b_level, phase_c_level;
    volatile int counter = 0; // For debugging
    volatile double v_command = 0.3; // Between 0 and 1
    volatile double field_rps_command = 120; // Flux rotation speed/synchronous speed

    Message message;

    // This while loop can be moved to the second core and this core can manage the field speed and voltage based on throttle and current motor rps
    while (1) {
        if (!queue_is_empty(&command_queue)) {
            while (!queue_is_empty(&command_queue)) {
                queue_remove_blocking(&command_queue, &message);
                switch (message.type) {
                    case 't':
                        double throttle = message.data / 1000;
                        break;
                    case 'm':
                        state = static_cast<States>(message.data);
                        break;
                }
            }
            if (state != States::kPower) {
                break;
            }
        }

        phase_pos = (phase_pos + phase_steps) % 1536;

        phase_a_level = fastsin[phase_pos] * v_command;
        phase_b_level = fastsin[phase_pos + 1024] * v_command;
        phase_c_level = fastsin[phase_pos + 512] * v_command;

        interface.PwmALevel(phase_a_level);
        interface.PwmBLevel(phase_b_level);
        interface.PwmCLevel(phase_c_level);

        if (v_command <= 0) {
        interface.PwmALevel(phase_a_level);
            state = States::kIdle;
            break;
        }

        if (state == States::kFault) {
            break;
        }

        sleep_us((1000000/(field_rps_command*phase_res)));

        // Square wave, fixed rpm, implementation
        // interface.SetAStatePWM('h', v_command);
        // sleep_us(wait_time);
        // interface.SetCStatePWM('l', v_command);
        // sleep_us(wait_time);
        // interface.SetBStatePWM('h', v_command);
        // sleep_us(wait_time);
        // interface.SetAStatePWM('l', v_command);
        // sleep_us(wait_time);
        // interface.SetCStatePWM('h', v_command);
        // sleep_us(wait_time);
        // interface.SetBStatePWM('l', v_command);
        // sleep_us(wait_time);
    }
}


void RegenLoop() {
    int wait_time;
    Message message;

    while (1) {
        if (!queue_is_empty(&command_queue)) {
            while (!queue_is_empty(&command_queue)) {
                queue_remove_blocking(&command_queue, &message);
                switch (message.type) {
                    case 'r':
                        field_rps_command = (double) message.data / 1000;
                        break;
                    case 'm':
                        state = static_cast<States>(message.data);
                        break;
                }
            }
            if (state != States::kRegen) {
                break;
            }
        }
        wait_time = 166667/(field_rps_command);

        // TODO Implement regen loop
    }
}


void ChargingLoop() {

}


void Disabled() {

}


void Fault() {
    // printf("Fault, halting...");
    interface.PwmALevel(0);
    interface.PwmBLevel(0);
    interface.PwmCLevel(0);
}

