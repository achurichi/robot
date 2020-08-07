#include "MPU9250.h"

// Creates an object for the sensor and define JSON doc size
MPU9250::MPU9250() {
    sensor = new MPU9250_asukiaaa();
    jsonCapacity = 3*JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(6);
}

// Initializes the sensor
void MPU9250::init() {
    sensor->beginAccel();
    sensor->beginGyro();
    sensor->beginMag();
}

// Checks if the sensor is working correctly
bool MPU9250::working() {
    uint8_t sensorId;
    if (sensor->readId(&sensorId) == 0)
        return true;
    else
        return false;
}

// Reads the data from the sensor and returns a JSON object with 3 decimals of precision
DynamicJsonDocument MPU9250::read()
{
    DynamicJsonDocument doc(jsonCapacity);
    bool error = false;

    JsonArray acc = doc.createNestedArray("acc");
    if (sensor->accelUpdate() == 0) {
        acc.add(round(sensor->accelX()*1000)/1000.0);
        acc.add(round(sensor->accelY()*1000)/1000.0);
        acc.add(round(sensor->accelZ()*1000)/1000.0);
        
        doc["accSqrt"] = round(sensor->accelSqrt()*1000)/1000.0;
    }
    else
        error = true;

    JsonArray gyro = doc.createNestedArray("gyro");
    if (sensor->gyroUpdate() == 0) {
        gyro.add(round(sensor->gyroX()*1000)/1000.0);
        gyro.add(round(sensor->gyroY()*1000)/1000.0);
        gyro.add(round(sensor->gyroZ()*1000)/1000.0);
    }
    else
        error = true;

    JsonArray mag = doc.createNestedArray("mag");
    if (sensor->magUpdate() == 0)
    {
        mag.add(round(sensor->magX()*1000)/1000.0);
        mag.add(round(sensor->magY()*1000)/1000.0);
        mag.add(round(sensor->magZ()*1000)/1000.0);

        doc["mDirection"] = round(sensor->magHorizDirection()*1000)/1000.0;
    }
    else
        error = true;

    doc["error"] = error;

    return doc;
}