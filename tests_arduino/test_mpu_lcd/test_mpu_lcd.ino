#include <MPU9250_asukiaaa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println("started");

    mySensor.beginAccel();
    mySensor.beginGyro();
    mySensor.beginMag();

    // You can set your own offset for mag values
    // mySensor.magXOffset = -50;
    // mySensor.magYOffset = -55;
    // mySensor.magZOffset = -10;

    lcd.init(); // initialize the lcd
    lcd.backlight();
}

void loop()
{
    uint8_t sensorId;
    if (mySensor.readId(&sensorId) == 0)
    {
        Serial.println("sensorId: " + String(sensorId));
    }
    else
    {
        Serial.println("Cannot read sensorId");
    }

    if (mySensor.accelUpdate() == 0)
    {
        aX = mySensor.accelX();
        aY = mySensor.accelY();
        aZ = mySensor.accelZ();
        aSqrt = mySensor.accelSqrt();
        Serial.println("accelX: " + String(aX));
        Serial.println("accelY: " + String(aY));
        Serial.println("accelZ: " + String(aZ));
        Serial.println("accelSqrt: " + String(aSqrt));
    }
    else
    {
        Serial.println("Cannod read accel values");
    }

    if (mySensor.gyroUpdate() == 0)
    {
        gX = mySensor.gyroX();
        gY = mySensor.gyroY();
        gZ = mySensor.gyroZ();
        Serial.println("gyroX: " + String(gX));
        Serial.println("gyroY: " + String(gY));
        Serial.println("gyroZ: " + String(gZ));
    }
    else
    {
        Serial.println("Cannot read gyro values");
    }

    if (mySensor.magUpdate() == 0)
    {
        mX = mySensor.magX();
        mY = mySensor.magY();
        mZ = mySensor.magZ();
        mDirection = mySensor.magHorizDirection();
        Serial.println("magX: " + String(mX));
        Serial.println("maxY: " + String(mY));
        Serial.println("magZ: " + String(mZ));
        Serial.println("horizontal direction: " + String(mDirection));
    }
    else
    {
        Serial.println("Cannot read mag values");
    }

    Serial.println("at " + String(millis()) + "ms");
    Serial.println("");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Test Line 1");
    lcd.setCursor(0, 1);
    lcd.print("Test Line 2");
    delay(500);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Test Line 3");
    lcd.setCursor(0, 1);
    lcd.print("Test Line 4");
    delay(500);
}
