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

#include "pico/stdlib.h"

#include "interfacing.hpp"
#include "maths.hpp"

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


void Init(Interface* interface, States* state);


void IdleLoop(Interface* interface, States* state);


void ReadyLoop(Interface* interface, States* state);


void PowerLoop(Interface* interface, States* state);


void RegenLoop(Interface* interface, States* state);


void FaultLoop(Interface* interface, States* state);


void ChargingLoop(Interface* interface, States* state);
