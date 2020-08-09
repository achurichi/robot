#include "ServoControl.h"

void ServoControl::init(uint8_t numberOfServos, uint8_t servoPins[], uint16_t servoPosMax[],
                        uint16_t servoPosMin[], uint16_t servoPosStart[]) {
    // Create vectors with the corresponding size
    this->numberOfServos = numberOfServos;
    this->servoPins = new uint8_t[numberOfServos];
    this->servoPosMax = new uint16_t[numberOfServos];
    this->servoPosMin = new uint16_t[numberOfServos];
    this->servoPosStart = new uint16_t[numberOfServos];
    this->servoPos = new uint16_t[numberOfServos];

    // Copy the values from the parameters
    memcpy(this->servoPins, servoPins, sizeof(servoPins[0])*numberOfServos);
    memcpy(this->servoPosMax, servoPosMax, sizeof(servoPosMax[0])*numberOfServos);
    memcpy(this->servoPosMin, servoPosMin, sizeof(servoPosMin[0])*numberOfServos);
    memcpy(this->servoPosStart, servoPosStart, sizeof(servoPosStart[0])*numberOfServos);
    memcpy(this->servoPos, servoPosStart, sizeof(servoPosStart[0])*numberOfServos);

    // Iniitalize servos
    this->servos = new Servo[numberOfServos];

    for (uint8_t i=0; i<numberOfServos; i++) {
        servos[i].attach(servoPins[i]); // Servo setup
        servos[i].write(servoPosStart[i]);
    }
}

// Set the position of a servo
void ServoControl::setServo(uint8_t idx, uint16_t angle) {
    if (this->servoPos[idx] != angle) { // Change only if the new angle is different
        angle = constrain(angle, this->servoPosMin[idx], this->servoPosMax[idx]);
        this->servos[idx].write(angle);
        this->servoPos[idx] = angle;
    }
}

// Set the position of all servos
void ServoControl::setAllServos(uint16_t angles[]) {
    uint16_t angle;

    for (uint8_t i=0; i<this->numberOfServos; i++)
        if (this->servoPos[i] != angles[i]) { // Change only if the new angle is different
            angle = constrain(angles[i], this->servoPosMin[i], this->servoPosMax[i]);
            this->servos[i].write(angle);
            this->servoPos[i] = angle;
        }
}

uint16_t ServoControl::getServo(uint8_t idx) { return this->servoPos[idx]; }