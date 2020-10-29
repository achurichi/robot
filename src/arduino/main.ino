#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SerialCom.h>
#include <ServoControl.h>
#include <Utils.h>

#define NUMBER_OF_SERVOS 12

uint8_t servoPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
uint16_t servoPosMax[] = {180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180};
uint16_t servoPosMin[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t servoPosSafeStart[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
uint16_t servoPos[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

ServoControl servos;

SerialCom arduino_serial;

// data myData; // data structure
StaticJsonDocument<300> doc_read; // Readed JSON document
// StaticJsonDocument<300> doc_send; // Sended JSON document

// LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup()
{
    arduino_serial.init(115200); // Serial initialization

    timer3_init(0.02); // Timer3 initialization
    timer4_init(1);    // Timer4 initialization

    // lcd.init(); // Initialize the lcd
    // lcd.backlight();

    // Default values for sensors and actuators
    // for (int i; i<12; i++)
    //     myData.motor[0] = 0;
    // myData.state = false;

    servos.init(NUMBER_OF_SERVOS, servoPins, servoPosMax, servoPosMin, servoPosSafeStart);
}

void loop()
{
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Motor 0: ");
    // lcd.print(String(myData.motor[0]));
    // delay(100);
}

//-------------------- Functions --------------------

// Timers

ISR(TIMER3_COMPA_vect)
{          // timer3 interrupt
    sei(); // allow interrupts

    String msg = arduino_serial.read();
    if (msg != "%%error")
    {
        deserializeJson(doc_read, msg);

        for (uint8_t i = 0; i < NUMBER_OF_SERVOS; i++)
            // myData.motor[i] = doc_read["motor"][i];
            servos.setServo(i, (uint16_t)doc_read["motor"][i]);
    }
}

ISR(TIMER4_COMPA_vect)
{          // timer4 interrupt
    sei(); // allow interrupts

    // doc_send["m_1"] = myData.m_1;
    // doc_send["m_2"] = myData.m_2;
    // doc_send["m_3"] = myData.m_3;
    // doc_send["state"] = myData.state;

    // arduino_serial.write(doc_send.as<String>());
}