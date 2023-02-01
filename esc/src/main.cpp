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

#include "defines.h"
#include "motor_drive/gatedriver_io.h"
#include "motor_drive/foc.h"
#include "uart_io/uart_io.h"

int main() {

    // Class initialisation
    Foc* foc_ptr = new Foc();
    UartIo* uart_io_ptr = new UartIo();

    // TODO the logic
    foc_ptr->GetGatedriverIoPtr()->SetLedState(true);

    // Cleanup
    delete foc_ptr;

    return 0;

}
