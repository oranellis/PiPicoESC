# FOC Control

This motor controller uses Field Oriented Control to drive both induction and BLDC motors.

FOC control drives the motor such that the magnetic field generated is exactly 90deg out of phase with the magnetic field present, so the force generated from these field interactions creates purely torque and no force towards or away from the motor axis (which represents wasted energy).

The voltage, current, and magnetic fields of the motor can be represented by an amplitude and phase (mathematical) which can be converted to and from the magnitudes on each motor phase (winding) using Clarke and Park transforms. The current measured across each phase inferres the orientation of the rotor magnetic field and the voltage generated specifies the generated magnetic field. It is therefore possible to generate this optimal drive condition by measuring the phase of the current and specifying the phase of the voltage to be 90deg ahead.

Measurement of the current is done using shunt resistors connected to isolated ADC's connected to the pico.

Phases are labeled A, B and C, the datum (0 degrees) is aligned with positive phase A direction.
