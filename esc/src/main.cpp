#include "common/defines.hpp"
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
