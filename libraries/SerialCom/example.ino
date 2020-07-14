#include "SerialCom.h"

SerialCom arduino_serial;

void setup() {
    arduino_serial.init();
}

void loop() {
    // if (arduino_serial.read() == "Raspberry says Hello!")
    // {
    //     arduino_serial.write("Arduino received Hello from Raspberry");
    //     delay(1000);
    //     arduino_serial.write("Arduino says Hello!");
    // }
    // delay(1000);
}
