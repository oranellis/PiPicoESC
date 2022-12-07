//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== foc.cpp ====
//
// Field Oriented Control algorithms
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "motor_drive/foc.hpp"

void Foc::Core1DriveMode(GatedriverIo* io, int* command) {
    // TODO FOC magic on a seperate core

}

int Foc::DriveMode(int* command) {
    Core1DriveMode(io, command);
    return 0;
}
