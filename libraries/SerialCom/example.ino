#include "SerialCom.h"

SerialCom mySerial;

void setup() {}

void loop() {
    mySerial.write("Hello!");
    delay(1000);
}
