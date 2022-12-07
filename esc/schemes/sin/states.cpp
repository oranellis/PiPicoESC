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

const int phase_steps = 2; // Can be a multiple of 2 up to 512 to reduce resolution
const int phase_res = 1536/phase_steps; // Number of steps through one sin wave


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
    Message message;
    double throttle = 0.5;

    interface.PwmALevel(0);
    interface.PwmBLevel(0);
    interface.PwmCLevel(0);

    // while (state == States::kIdle) {
    //     if (!queue_is_empty(&command_queue)) {
    //         while (!queue_is_empty(&command_queue)) {
    //             queue_remove_blocking(&command_queue, &message);
    //             switch (message.type) {
    //                 case 't': {
    //                     throttle = message.data; // (double) message.data / 1000;
    //                 }
    //                 case 'm': {
    //                     state = static_cast<States>(message.data);
    //                     break;
    //                 }
    //                 default: {
    //                     break;
    //                 }
    //             }
    //         }
    //         if (state != States::kPower) {
    //             break;
    //         }
    //     }
    //     if (throttle>0) {
    //         state = States::kPower;
    //     }
    //     else if (throttle<0) {
    //         state = States::kRegen;
    //     }
    // }
    state = States::kPower;
    sleep_ms(1);
}


void PowerLoop() {
    Message message;
    volatile float field_rps = 200;
    volatile float v_command = 0.25;
    volatile int phase_a_pos = 0;
    volatile int phase_b_pos = 1024;
    volatile int phase_c_pos = 512;
    volatile int phase_a_level, phase_b_level, phase_c_level;

    gpio_init(15);
    gpio_set_dir(15, GPIO_OUT);



    while (1) {
        if (!queue_is_empty(&command_queue)) {
            while (!queue_is_empty(&command_queue)) {
                queue_remove_blocking(&command_queue, &message);
                switch (message.type) {
                    case 't': {
                        float throttle = (float) message.data / 1000;
                        // MotorData motor_data = motor_data_from_throttle(throttle);
                        // field_rps = motor_data.field_rps;
                        // v_command = motor_data.v_command;
                        break;
                    }
                    case 'm': {
                        state = static_cast<States>(message.data);
                        break;
                    }
                }
            }
            if (state != States::kPower) {
                break;
            }
        }

        gpio_put(15, true);
        phase_a_level = fastsin[phase_a_pos] * v_command;
        phase_b_level = fastsin[phase_b_pos] * v_command;
        phase_c_level = fastsin[phase_c_pos] * v_command;

        gpio_put(15, false);
        interface.PwmALevel(phase_a_level);
        interface.PwmBLevel(phase_b_level);
        interface.PwmCLevel(phase_c_level);

        phase_a_pos = (phase_a_pos + phase_steps) % 1535;
        phase_b_pos = (phase_b_pos + phase_steps) % 1535;
        phase_c_pos = (phase_c_pos + phase_steps) % 1535;
        // if (v_command <= 0) {
        //     state = States::kIdle;
        //     break;
        // }

        // if (state == States::kFault) {
        //     break;
        // }

    }
}


void RegenLoop() {
    int wait_time;
    Message message;
    double field_rps;

    while (1) {
        if (!queue_is_empty(&command_queue)) {
            while (!queue_is_empty(&command_queue)) {
                queue_remove_blocking(&command_queue, &message);
                switch (message.type) {
                    case 'r':
                        field_rps = (double) message.data / 1000;
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
        wait_time = 166667/(field_rps);

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
