#include "MPU9250.h"

// Create an object for the sensor and define JSON doc size
MPU9250::MPU9250() {
    sensor = new MPU9250_asukiaaa();
    jsonCapacity = 3*JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(6);
}

// Initialize the sensor
void MPU9250::init() {
    sensor->beginAccel();
    sensor->beginGyro();
    sensor->beginMag();
}

// Check if the sensor is working correctly
bool MPU9250::working() {
    uint8_t sensorId;
    if (sensor->readId(&sensorId) == 0)
        return true;
    else
        return false;
}

// Read the data from the sensor
DynamicJsonDocument MPU9250::read()
{
    error = false;

    if (sensor->accelUpdate() == 0) {
        acc[0] = sensor->accelX();
        acc[1] = sensor->accelY();
        acc[2] = sensor->accelZ();
        accSqrt = sensor->accelSqrt();
    }
    else
        error = true;

    if (sensor->gyroUpdate() == 0) {
        gyro[0] = sensor->gyroX();
        gyro[1] = sensor->gyroY();
        gyro[2] = sensor->gyroZ();
    }
    else
        error = true;

    if (sensor->magUpdate() == 0)
    {
        mag[0] = sensor->magX();
        mag[1] = sensor->magY();
        mag[2] = sensor->magZ();
        mDirection = sensor->magHorizDirection();
    }
    else
        error = true;

    return toJson();
}

// Convert data to a JSON format
DynamicJsonDocument MPU9250::toJson() {
    DynamicJsonDocument doc(jsonCapacity);

    JsonArray acc = doc.createNestedArray("acc");
    acc.add(acc[0]);
    acc.add(acc[1]);
    acc.add(acc[2]);

    doc["accSqrt"] = accSqrt;

    JsonArray gyro = doc.createNestedArray("gyro");
    gyro.add(gyro[0]);
    gyro.add(gyro[1]);
    gyro.add(gyro[2]);
    
    doc["mDirection"] = mDirection;

    JsonArray mag = doc.createNestedArray("mag");
    mag.add(mag[0]);
    mag.add(mag[1]);
    mag.add(mag[2]);
    
    doc["error"] = error;

    return doc;
}