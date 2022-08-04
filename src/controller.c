#include "controllerMaths.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "interfacing.h"
#include "enums.h"

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"

volatile int throttle = 1; // Between 0 and 32767
volatile enum states state = s_power;

volatile int phaseALevelRaw, phaseBLevelRaw, phaseCLevelRaw;
volatile int phaseALevel, phaseBLevel, phaseCLevel;
volatile int phaseAPos1024, phaseBPos1024, phaseCPos1024;
volatile int counter = 0;
volatile long countertime = 0;
volatile long timenow = 0;
volatile double targetFieldRps = 0.1;
const int phaseSteps = 1; // Can be a multiple of 2 up to 512
const int phaseRes = 1536/phaseSteps;


void powerLoop() {
    phaseAPos1024 = 0;
    phaseBPos1024 = 512;
    phaseCPos1024 = 1024;
    while (1) {
        phaseAPos1024 = (phaseAPos1024 + phaseSteps) % 1536;
        phaseBPos1024 = (phaseBPos1024 + phaseSteps) % 1536;
        phaseCPos1024 = (phaseCPos1024 + phaseSteps) % 1536;

        phaseALevelRaw= fastsin[phaseAPos1024];
        phaseBLevelRaw = fastsin[phaseBPos1024];
        phaseCLevelRaw = fastsin[phaseCPos1024];

        if (phaseALevelRaw <= phaseBLevelRaw && phaseALevelRaw <= phaseCLevelRaw) {
            phaseALevel = 0;
            phaseBLevel = phaseBLevelRaw - phaseALevelRaw;
            phaseCLevel = phaseCLevelRaw - phaseALevelRaw;
        }
        else if (phaseBLevelRaw <= phaseCLevelRaw && phaseBLevelRaw <= phaseALevelRaw) {
            phaseALevel = phaseALevelRaw - phaseBLevelRaw;
            phaseBLevel = 0;
            phaseCLevel = phaseCLevelRaw - phaseBLevelRaw;
        }
        else {
            phaseALevel = phaseALevelRaw - phaseCLevelRaw;
            phaseBLevel = phaseBLevelRaw - phaseCLevelRaw;
            phaseCLevel = 0;
        }

        if (phaseALevel == 0) {
            gpio_put(outputALow, 1);
        }
        else {
            gpio_put(outputALow, 0);
        }

        if (phaseBLevel == 0) {
            gpio_put(outputBLow, 1);
        }
        else {
            gpio_put(outputBLow, 0);
        }

        if (phaseCLevel == 0) {
            gpio_put(outputCLow, 1);
        }
        else {
            gpio_put(outputALow, 0);
        }

        pwm_set_chan_level(slice_num_0, channel_0, phaseALevel);
        pwm_set_chan_level(slice_num_1, channel_1, phaseBLevel);
        pwm_set_chan_level(slice_num_2, channel_2, phaseCLevel);


        if (counter > 1000) {
            counter = 0;
            timenow = time_us_64();
            printf("a: %i b: %i c: %i    a: %i b: %i c: %i    time: %li \n", phaseALevel, phaseBLevel, phaseCLevel, phaseALevelRaw, phaseBLevelRaw, phaseCLevelRaw, timenow-countertime);
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
    if (iosetup() != 0) {
        printf("eFailed to initialise IO");
        return 1;
    }
    iosetup();

    // =================== Main Event Loop ===================

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
