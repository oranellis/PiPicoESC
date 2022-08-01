#include "controllerMaths.h"
#include "interfacing.h"
#include "enums.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"
volatile int fieldRotPos = 0; // Clamped between 0 and 1023 with datum at phase 1 positive current magnetic field orientation
volatile int throttle = 0; // Between 0 and 32767
volatile int fieldSpinSpeed = 2048; //256*revs per second
volatile enum states state = s_fault;
volatile uint64_t timeshitter;
volatile long phaseTime = 0; //time in us through the phase rotation
volatile long phasePeriod = 4000000; // period of phase rotation (spinnning speeeeeeeeeeeeeeeeeeeeeeeed)
volatile long timediff = 0;

void powerLoop() {
    while (1) {
        state = s_fault;


        if (throttle <= 0) {
            state = s_idle;
            break;
        }

        if (state == s_fault) {
            break;
        }
    }
}


void regenLoop() {
    while (1) {
        state = s_fault;

        if (throttle >= 0) {
            state = s_idle;
        }

        if (state == s_fault) {
            break;
        }
    }
}

volatile int phaseA, phaseB, phaseC;
volatile double phasePos;
volatile long phasePos1024;

void faultLoop() {
    timediff = time_us_64() - timeshitter;
    timeshitter = time_us_64();
    phaseTime = (phaseTime + timediff) % phasePeriod;
    phasePos = (phaseTime / phasePeriod);
    phasePos1024 = (long) phasePos * 1024;
    phaseA = fastsin[(phasePos1024)%1024];
    phaseB = fastsin[(phasePos1024+341)%1024];
    phaseC = fastsin[(phasePos1024+683)%1024];
    // printf("A: %i B: %i C: %i\n", phaseA, phaseB, phaseC);
    printf("C: %i\n", timeshitter);
    sleep_ms(1);
}




int main() {

    // =================== Interfacing setup ===================
    if (iosetup() != 0) {
        printf("eFailed to initialise IO");
        return 1;
    }

    // =================== Global variables ===================
    // Motor state variables
  

    printf("State number: %i\n", state);

    // Main event loop

    while (1) {
        
        switch (state) {
            // case s_fault: faultLoop(); break;
            // case s_init: init(); break;
            // case s_idle: idleLoop(); break;
            // case s_ready: readyLoop(); break;
            // case s_power: powerLoop(); break;
            // case s_regen: regenLoop(); break;
            default: faultLoop(); break;
        }
    }

    return 0;
}
