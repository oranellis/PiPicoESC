//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// The program entrypoint
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#define DEBUG

#include "loops.h"

#include "pico/time.h"

int main() {

    int errorcode = 0;
    int counter100hz = 0;
    int counter10hz = 0;
    unsigned long long loop_start_us = 0;
    unsigned long loop_period_us = 0;

    while (errorcode & 0) {

        loop_start_us = time_us_64();

        Loop4khz();

        if (counter100hz >= 40) {

            Loop100hz();
            counter100hz = 0;

            if (counter10hz >= 10) {

                Loop10hz();
                counter10hz = 0;

                loop_period_us = time_us_64() - loop_start_us;

            }

            else {

                counter10hz++;

            }

        }

        else {

            counter100hz++;

        }

        busy_wait_until(loop_start_us + 250); // 4kHz looptime

    }

    return errorcode;

}
