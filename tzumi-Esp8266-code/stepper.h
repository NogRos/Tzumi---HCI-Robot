#include <Stepper.h>

const int stepsPerRevolution = 4096;  // number of steps per revolution for the motor
Stepper myStepper(stepsPerRevolution, D5, D7, D6, D8); // initialize the stepper library on pins 5 through 8. notice the order.
