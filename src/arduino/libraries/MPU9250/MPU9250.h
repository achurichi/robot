#ifndef MPU9250_h
#define MPU9250_h

#include "Arduino.h"
#include <MPU9250_asukiaaa.h>
#include <ArduinoJson.h>

class MPU9250 {
    public:
        float acc[3];
        float accSqrt;
        float gyro[3];
        float mDirection;
        float mag[3];
        bool error;

        MPU9250();
        void init();
        bool working();
        DynamicJsonDocument read();
    
    private:
        MPU9250_asukiaaa *sensor;
        size_t jsonCapacity;

        DynamicJsonDocument toJson();
};

#endif