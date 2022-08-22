//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== states.h ====
//
// Header file for states.cpp
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#include "interfacing.hpp"
#include "controller_maths.hpp"

enum class States {
    kFault,
    kInit,
    kReady,
    kRegen,
    kCharging,
    kIdle,
    kPower
};

enum class DriveModes {
    kPark,
    kReverse,
    kNeutral,
    kEco,
    kDrive,
    kSpeeeeeed,
};


void Init();


void IdleLoop();


void ReadyLoop();


void PowerLoop(Interface* interface);


void RegenLoop();


void FaultLoop();


void ChargingLoop();
