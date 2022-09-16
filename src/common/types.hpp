//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== types.hpp ====
//
// Header file containing all commonly used types
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

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
