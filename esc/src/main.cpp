//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== main.cpp ====
//
// The program entrypoint
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "defines.hpp"
#include "motor_drive/gatedriver_io.hpp"
#include "motor_drive/foc.hpp"

int main() {

    // Class initialisation
    GatedriverIo* gatedriverIo = new GatedriverIo(); // Runs gatedriver power init sequence
    Foc* foc = new Foc(gatedriverIo);

    // TODO the logic

    // Cleanup
    delete foc;
    delete gatedriverIo;

    return 0;

}
