#include "motor_drive/foc.hpp"

void Foc::Core1Drive(GatedriverIo* io, int* command) {
    // TODO FOC magic on a seperate core

}

int Foc::DriveForwards(int* command) {
    Core1Drive(io, command);
    return 0;
}
