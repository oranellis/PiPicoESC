//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== core_io.hpp ====
//
// Header containing stuff related to communication between cores
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "hardware/irq.h"
#include "pico/util/queue.h"


#define COMMAND_INTERUPT 26


extern queue_t command_queue;
extern bool core_1_loop_interupt;


struct Message {
    char type;
    uint32_t data;

    // Empty constructor
    Message() {
        type = ' ';
        data = 0;
    }

    // Populating constructor
    Message(char init_type, uint32_t init_data) {
        type = init_type;
        data = init_data;
    }
};


// Inline helper function to ensure messages are sent correctly
inline void messaging_wrapper(Message message) {
    queue_add_blocking(&command_queue, &message);
    if (message.type != 'r') {
    }
}
