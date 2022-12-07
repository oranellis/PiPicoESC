// ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== main.cpp ====
//
// Main script containing the logic to drive an induction motor
//
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "pico/stdio.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "common/types.hpp"
#include "common/maths.hpp"
#include "platform/pico/core_io.hpp"
#include "platform/pico/interfacing.hpp"
#include "schemes/sin/states.hpp"


// Global variable declaration
States state; // From extern in states.hpp
Interface * interface = new Interface(); // From extern in interface.hpp
queue_t command_queue; // From extern in core_io.hpp


void core_1_entry() {
    // =================== Core 1 Setup ===================
    // irq_clear(COMMAND_INTERUPT);
    // irq_add_shared_handler(COMMAND_INTERUPT, core_1_irq_handler, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY); // irq handler defined in states.hpp
    // irq_set_enabled(COMMAND_INTERUPT, true);


    // =================== Main Event Loop ===================
    while (1) {
        if (!queue_is_empty(&command_queue)) {
            Message recieved_message;
            queue_remove_blocking(&command_queue, &recieved_message);
            if (recieved_message.type == 'm') {
                state = static_cast<States>(recieved_message.data);
            }
        }
        switch (state) {
            case States::kFault: Fault(); break;
            case States::kInit: Init(); break;
            case States::kIdle: IdleLoop(); break;
            case States::kDisabled: Disabled(); break;
            case States::kPower: PowerLoop(); break;
            case States::kRegen: RegenLoop(); break;
            case States::kCharging: ChargingLoop(); break;
            default: Fault(); break;
        }
    }
}


int main() {
    // =================== Setup ===================
    // Initialise command queue
    queue_init(&command_queue, sizeof(Message), 4);
    multicore_launch_core1(core_1_entry);

    messaging_wrapper(States::kFault);

    // Initialise uart comms
    stdio_uart_init();

    // =================== Terminal Loop ===================
    // must delay the program termination so the core_1 code can run
    while (true) {
        return 0;
    }

    return 0;
}
