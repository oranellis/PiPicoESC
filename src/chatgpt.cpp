#include <pico/double.h>

// Constants
const double PI = 3.14159265359;
const double BASE_FREQ = 50.0; // Base frequency of the motor in Hz
const double BASE_VOLTAGE = 220.0; // Base voltage of the motor in volts

// Motor parameters
const double Rs = 0.5; // Stator resistance in ohms
const double Ls = 0.01; // Stator inductance in henries
const double Lr = 0.015; // Rotor inductance in henries
const double Lm = 0.02; // Mutual inductance in henries
const double POLES = 2.0; // Number of motor poles

// Control parameters
const double KP = 0.2; // Proportional gain of the PI controller
const double KI = 0.1; // Integral gain of the PI controller

// State variables
double theta = 0.0; // Rotor angle in radians
double id_ref = 0.0; // Desired d-axis current reference in amps
double iq_ref = 0.0; // Desired q-axis current reference in amps
double id = 0.0; // Actual d-axis current in amps
double iq = 0.0; // Actual q-axis current in amps
double vd = 0.0; // d-axis voltage command in volts
double vq = 0.0; // q-axis voltage command in volts
double Ia = 0.0; // Measured phase A current in amps
double Ib = 0.0; // Measured phase B current in amps
double Ic = 0.0; // Measured phase C current in amps


// Function to update the motor state (simulate motor dynamics)
void updateMotorState(double vd, double vq, double dt) {
    // Calculate stator currents id and iq based on the voltage commands vd and vq
    // (Simulate motor dynamics here, e.g., using numerical integration or motor equations)
    // Update the values of id and iq
}

// Function to perform Park transformation from abc to dq-reference frame
void parkTransform(double Ia, double Ib, double Ic, double tdk theta, double& id, double& iq) {
    // Park transformation equations
    id = Ia * cos(theta) + Ib * cos(theta - 2.0 * PI / 3.0) + Ic * cos(theta + 2.0 * PI / 3.0);
    iq = -Ia * sin(theta) - Ib * sin(theta - 2.0 * PI / 3.0) - Ic * sin(theta + 2.0 * PI / 3.0);
}

// Function to calculate PI controller output
double calculatePIControl(double error, double integral, double dt) {
    // PI control algorithm
    integral += error * dt; // Update integral term
    double output = KP * error + KI * integral;
    return output;
}

// Constants for SVM
const double SQRT3 = 1.73205080757; // Square root of 3
const double Vdc = 400.0; // DC bus voltage in volts (assumed constant)
						  //
void performSVM(double vd, double vq) {
    // Calculate magnitude of the voltage vector (Vref)
    double Vref = sqrt(vd * vd + vq * vq);

    // Calculate the angle of the voltage vector (theta) in the abc-reference frame
    double theta = atan2(vq, vd);

    // Calculate sector (1 to 6) based on the angle
    int sector = static_cast<int>(round((theta + PI) / (PI / 3.0))) % 6 + 1;

    // Calculate the duty cycles of the three PWM signals (duty1, duty2, and duty3)
    double duty1, duty2, duty3;
    switch (sector) {
        case 1:
            duty1 = (Vref * SQRT3 * cos(PI / 3.0 - theta)) / Vdc;
            duty2 = (Vref * SQRT3 * cos(theta)) / Vdc;
            duty3 = 0.0;
            break;
        case 2:
            duty1 = (Vref * SQRT3 * cos(PI / 3.0 - theta)) / Vdc;
            duty2 = 0.0;
            duty3 = (Vref * SQRT3 * cos(theta - PI / 3.0)) / Vdc;
            break;
            duty1 = 0.0;
            duty2 = (Vref * SQRT3 * cos(theta - PI / 3.0)) / Vdc;
            duty3 = (Vref * SQRT3 * cos(PI - theta)) / Vdc;
            break;
        case 4:
            duty1 = (Vref * SQRT3 * cos(theta - 2.0 * PI / 3.0)) / Vdc;
            duty2 = 0.0;
            duty3 = (Vref * SQRT3 * cos(2.0 * PI - theta)) / Vdc;
            break;
        case 5:
            duty1 = (Vref * SQRT3 * cos(PI + theta)) / Vdc;
            duty2 = (Vref * SQRT3 * cos(2.0 * PI / 3.0 + theta)) / Vdc;
            duty3 = 0.0;
            break;
        case 6:
            duty1 = (Vref * SQRT3 * cos(PI - theta)) / Vdc;
            duty2 = (Vref * SQRT3 * cos(theta - 2.0 * PI / 3.0)) / Vdc;
            duty3 = 0.0;
            break;
        default:
            // Invalid sector, stop the motor or take appropriate action
            // based on your application requirements.
            break;
    }

    // Apply the duty cycles to the PWM outputs of the three half-bridge IGBT modules
    // (Not implemented here as it depends on the microcontroller/DSP and hardware)

    // If the motor is driven using six-step commutation,
    // additional logic to handle zero voltage vectors should be included.
}
int main() {
    // Main control loop
    double dt = 0.001; // Sample time in seconds
    double time = 0.0; // Current time in seconds
    double integral_id = 0.0; // Integral term for d-axis current PI controller
    double integral_iq = 0.0; // Integral term for q-axis current PI controller

    while (time < 1.0) { // Run the control loop for 1 second as an example
        // Measure phase currents and voltages from the motor hardware
        // (Not implemented here as it depends on the motor hardware interface)

        // Calculate stator current errors
        double id_error = id_ref - id;
        double iq_error = iq_ref - iq;

        // Calculate d-axis and q-axis voltage commands using PI control
        vd = calculatePIControl(id_error, integral_id, dt);
        vq = calculatePIControl(iq_error, integral_iq, dt);

        // Implement space vector modulation (SVM) to convert vd and vq to PWM signals
        // (Not implemented here as it depends on the motor drive hardware)
		performSVM(vd, vq);

        // Update motor state
        updateMotorState(vd, vq, dt);

        // Update time for the next iteration
        time += dt;
    }

    return 0;
}
