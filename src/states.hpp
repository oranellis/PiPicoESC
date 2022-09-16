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

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "interfacing.hpp"
#include "maths.hpp"
#include "core_io.hpp"

enum class States {
    kFault,
    kInit,
    kReady,
    kRegen,
    kCharging,
    kIdle,
    kPower,
    kTest
};


enum class DriveModes {
    kPark,
    kReverse,
    kNeutral,
    kEco,
    kDrive,
    kSpeeeeeed,
};


// void core_1_irq_handler();


void Init();


void IdleLoop();


void ReadyLoop();


void PowerLoop();


void RegenLoop();


void FaultLoop();


void ChargingLoop();


// Global state variable declaration
extern States state;
