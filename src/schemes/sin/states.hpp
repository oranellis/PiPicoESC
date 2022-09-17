//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== states.hpp ====
//
// Header file for states.cpp
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include <stdio.h>

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "common/maths.hpp"
#include "platform/pico/interfacing.hpp"
#include "platform/pico/core_io.hpp"



// void core_1_irq_handler();


void Init();


void IdleLoop();


void PowerLoop();


void RegenLoop();


void ChargingLoop();


void Disabled();


void Fault();


// Global state variable declaration
extern States state;
