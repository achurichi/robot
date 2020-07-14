#include "SerialCom.h"

SerialCom mySerial;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    mySerial.write(mySerial.read());

    delay(1000);
}
