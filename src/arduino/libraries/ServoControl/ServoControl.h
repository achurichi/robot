#ifndef ServoControl_h
#define ServoControl_h

#include "Arduino.h"
#include <Servo.h>

class ServoControl {
    public:
        void init(int, int[], int[], int[], int[]); 
        void setServo(int, int);
        void setAllServos(int[]);

    private:
        Servo *servos;
        int numberOfServos; 
        int *servoPins;
        int *servoPosMax;
        int *servoPosMin;
        int *servoPosStart;
        int *servoPos;
};

#endif