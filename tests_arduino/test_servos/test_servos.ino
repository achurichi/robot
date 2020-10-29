#include <ServoControl.h>
#define NUMBER_OF_SERVOS 12

uint8_t servoPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
uint16_t servoPosMax[] = {270, 270, 270, 270, 270, 270, 270, 270, 270, 270, 270, 270};
uint16_t servoPosMin[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t servoPosSafeStart[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
uint16_t servoPos[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

ServoControl servos;

void setup()
{
    servos.init(NUMBER_OF_SERVOS, servoPins, servoPosMax, servoPosMin, servoPosSafeStart);
}

void loop()
{
    int pos;
    for (int i = 0; i < 540; i += 20)
    {
        if (i <= 270)
            pos = i;
        else
            pos = 540 - i;

        for (int j = 0; j < NUMBER_OF_SERVOS; j++)
            servoPos[j] = pos;

        servos.setAllServos(servoPos);
        delay(500);
    }
}