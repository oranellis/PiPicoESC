#include "controllerMaths.h"
#include "hardware/timer.h"
#include "interfacing.h"
#include "enums.h"

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"

volatile int throttle = 1; // Between 0 and 32767
volatile int fieldSpinSpeed = 2048; //256*revs per second
volatile enum states state = s_power;

volatile long prevLoopTimestamp;
volatile long phaseTime = 0; //time in us through the phase rotation
volatile long timediff = 0;
volatile int phaseA, phaseB, phaseC;
volatile int phaseAPos1024, phaseBPos1024, phaseCPos1024;
volatile int counter = 0;
volatile long countertime = 0;
volatile long timenow = 0;
volatile int targetFieldRps = 10;
const int phaseSteps = 4;
const int phaseRes = 1024/phaseSteps;

void powerLoop() {
    phaseAPos1024 = 0;
    phaseBPos1024 = 683;
    phaseCPos1024 = 384;
    while (1) {
        prevLoopTimestamp = time_us_64();
        phaseAPos1024 = (phaseAPos1024 + phaseSteps) % 1024;
        phaseBPos1024 = (phaseBPos1024 + phaseSteps) % 1024;
        phaseCPos1024 = (phaseCPos1024 + phaseSteps) % 1024;
        phaseA = fastsin[phaseAPos1024];
        phaseB = fastsin[phaseBPos1024];
        phaseC = fastsin[phaseCPos1024];
        if (counter > 10000) {
            counter = 0;
            timenow = time_us_64();
            printf("dif: %li\n",timenow-countertime);
            countertime = timenow;
        }
        else {
            counter++;
        }

        if (throttle <= 0) {
            state = s_idle;
            break;
        }

        if (state == s_fault) {
            break;
        }

        sleep_us((1000000/(targetFieldRps*phaseRes)));
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


void faultLoop() {
}




int main() {

    // =================== Interfacing setup ===================
    // if (iosetup() != 0) {
        // printf("eFailed to initialise IO");
        // return 1;
    // }
    iosetup();

    // =================== Global variables ===================
    // Motor state variables

    // Main event loop

    while (1) {
        switch (state) {
            // case s_fault: faultLoop(); break;
            // case s_init: init(); break;
            // case s_idle: idleLoop(); break;
            // case s_ready: readyLoop(); break;
            case s_power: powerLoop(); break;
            // case s_regen: regenLoop(); break;
           default: faultLoop(); break;
        }
    }

    return 0;
}
