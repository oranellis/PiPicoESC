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

#include "common/types.hpp"

#define COMMAND_INTERUPT 26


extern queue_t command_queue;
extern bool core_1_loop_interupt;


// Inline helper function to handle sending messages
inline void messaging_wrapper(char type, int32_t data) {
    Message message(type, data);
    queue_add_blocking(&command_queue, &message);
}

//Overload for above to allow automatic inference of mode change
inline void messaging_wrapper(States message_state) {
    Message message('m', static_cast<int32_t>(message_state));
    queue_add_blocking(&command_queue, &message);
}
