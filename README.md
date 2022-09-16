# PiPicoESC
Simple testing of using a pi pico to drive an IGBT module for motor speed control, and a project to expand my C++ skills


## Developer Notes

The program is structured such that core 0 is responsible for the command io and general management of the esc state, while core 1 runs the control loops that update the pwm outputs to drive the motor (or charge the battery) which can be found in states.cpp. The interaction between the cores is done using a queue and interupts such that when a command is sent (e.g. changing the throttle), the command message is added to the `command_queue` and an interrupt is fired on core 1 to interrupt the control loop and action it.
