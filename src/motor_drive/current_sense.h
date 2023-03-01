//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// ==== current_sense.h ====
//
// Current sensing logic and wrappers
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "defines.h"

class CurrentSensors {

    public:

    int GetPhaseACurrentMilliAmps();

    int GetPhaseBCurrentMilliAmps();

    int GetPhaseCCurrentMilliAmps();


};
