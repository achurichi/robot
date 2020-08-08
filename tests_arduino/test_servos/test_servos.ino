#include <ServoControl.h>
#define NUMBER_OF_SERVOS 12

int servoPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int servoPosMax[] = {180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180};
int servoPosMin[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int servoPosSafeStart[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
int servoPos[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

ServoControl servos;

void setup() {
    servos.init(NUMBER_OF_SERVOS, servoPins, servoPosMax, servoPosMin, servoPosSafeStart);
}

void loop() {
    int pos;
    for (int i=0; i<360; i+=20) {
        if (i <= 180)
            pos = i;
        else
            pos = 360 - i;
    
        for (int j=0; j<NUMBER_OF_SERVOS; j++)
            servoPos[j] = pos;
    
        servos.setAllServos(servoPos);
        delay(500);
    }
}