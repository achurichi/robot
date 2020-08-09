#include "ServoControl.h"

void ServoControl::init(int numberOfServos, int servoPins[], int servoPosMax[],
                        int servoPosMin[], int servoPosStart[]) {
    // Create vectors with the corresponding size
    this->numberOfServos = numberOfServos;
    this->servoPins = new int[numberOfServos];
    this->servoPosMax = new int[numberOfServos];
    this->servoPosMin = new int[numberOfServos];
    this->servoPosStart = new int[numberOfServos];
    this->servoPos = new int[numberOfServos];

    // Copy the values from the parameters
    memcpy(this->servoPins, servoPins, sizeof(servoPins[0])*numberOfServos);
    memcpy(this->servoPosMax, servoPosMax, sizeof(servoPosMax[0])*numberOfServos);
    memcpy(this->servoPosMin, servoPosMin, sizeof(servoPosMin[0])*numberOfServos);
    memcpy(this->servoPosStart, servoPosStart, sizeof(servoPosStart[0])*numberOfServos);
    memcpy(this->servoPos, servoPosStart, sizeof(servoPosStart[0])*numberOfServos);

    // Iniitalize servos
    this->servos = new Servo[numberOfServos];

    for (int i=0; i<numberOfServos; i++) {
        servos[i].attach(servoPins[i]); // Servo setup
        servos[i].write(servoPosStart[i]);
    }
}

// Set the position of a servo
void ServoControl::setServo(int idx, int angle) {
    if (this->servoPos[idx] != angle) { // Change only if the new angle is different
        angle = constrain(angle, this->servoPosMin[idx], this->servoPosMax[idx]);
        this->servos[idx].write(angle);
        this->servoPos[idx] = angle;
    }
}

// Set the position of all servos
void ServoControl::setAllServos(int angles[]) {
    int angle;

    for (int i=0; i<this->numberOfServos; i++)
        if (this->servoPos[i] != angles[i]) { // Change only if the new angle is different
            angle = constrain(angles[i], this->servoPosMin[i], this->servoPosMax[i]);
            this->servos[i].write(angle);
            this->servoPos[i] = angle;
        }
}

int ServoControl::getServo(int idx) { return this->servoPos[idx]; }