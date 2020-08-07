#ifndef MPU9250_h
#define MPU9250_h

#include "Arduino.h"
#include <MPU9250_asukiaaa.h>
#include <ArduinoJson.h>

class MPU9250 {
    public:
        MPU9250();
        void init();
        bool working();
        DynamicJsonDocument read();
    
    private:
        MPU9250_asukiaaa *sensor;
        size_t jsonCapacity;
};

#endif