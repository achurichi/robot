#include <MPU9250.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

MPU9250 mpuSensor;

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println("started");

    mpuSensor.init();

    lcd.init(); // initialize the lcd
    lcd.backlight();
}

void loop()
{
    serializeJson(mpuSensor.read(), Serial);
    Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Test Line 1");
    lcd.setCursor(0, 1);
    lcd.print("Test Line 2");
    delay(500);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Test Line222 3");
    lcd.setCursor(0, 1);
    lcd.print("Test Line 4");
    delay(500);
}
