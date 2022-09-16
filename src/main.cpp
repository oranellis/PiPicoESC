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

#include "maths.hpp"
#include "interfacing.hpp"
#include "states.hpp"
#include "core_io.hpp"


// Global variable declaration
States state; // From extern in states.hpp
Interface interface; // From extern in interface.hpp
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
            case States::kFault: FaultLoop(); break;
            case States::kInit: Init(); break;
            case States::kIdle: IdleLoop(); break;
            case States::kReady: ReadyLoop(); break;
            case States::kPower: PowerLoop(); break;
            case States::kRegen: RegenLoop(); break;
            case States::kCharging: ChargingLoop(); break;
            default: FaultLoop(); break;
        }
    }
}


int main() {
    // =================== Setup ===================
    state = States::kInit
    queue_init(&command_queue, sizeof(Message), 4);
    multicore_launch_core1(core_1_entry);

    Message message('m', (uint32_t) States::kFault);
    queue_add_blocking(&command_queue, &message);
    sleep_ms(4000);

    message = Message('m', (uint32_t) States::kInit);
    queue_add_blocking(&command_queue, &message);
    sleep_ms(6000);
    gpio_put(LED_PIN, false);

    for (int r = 120; r < 200; r++) {
        message = Message('r', (uint32_t) r);
        queue_add_blocking(&command_queue, &message);
        sleep_ms(50);
    }


    message = Message('m', (uint32_t) States::kFault);
    queue_add_blocking(&command_queue, &message);

    // =================== Terminal Loop ===================
    // must delay the program termination so the core_1 code can run
    while (true) {
        sleep_ms(250);
        gpio_put(LED_PIN, true);
        sleep_ms(250);
        gpio_put(LED_PIN, false);
    }

    return 0;
}
