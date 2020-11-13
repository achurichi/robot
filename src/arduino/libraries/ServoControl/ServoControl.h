
#ifndef ServoControl_h
#define ServoControl_h

#include "Arduino.h"
#include <Servo.h>

class ServoControl
{
public:
    void init(uint8_t, uint8_t[], uint16_t[], uint16_t[], uint16_t[], uint16_t[], uint16_t[]);
    void setServo(uint8_t, uint16_t);
    void setAllServos(uint16_t[]);
    uint16_t getServo(uint8_t);

private:
    Servo *servos;
    uint8_t numberOfServos;
    uint8_t *servoPins;
    uint16_t *servoPosMax;
    uint16_t *servoPosMin;
    uint16_t *servoPosStart;
    uint16_t *servoPos;
    uint16_t *servoMicrosMin;
    uint16_t *servoMicrosMax;
};

#endif