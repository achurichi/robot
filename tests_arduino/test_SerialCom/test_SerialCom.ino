#include "src/arduino/libraries/SerialCom.h"
#include "src/arduino/libraries/utils.h"

SerialCom arduinoSerial;

void setup() {
    arduinoSerial.init(115200);

    pinMode(LED_BUILTIN, OUTPUT);

    timer3_init(1);
    timer4_init(0.02);
}

ISR(TIMER3_COMPA_vect){ // timer3 interrupt
    sei(); // allow interrupts
    arduinoSerial.write("Arduino says Hello!");
}

ISR(TIMER4_COMPA_vect){ // timer4 interrupt
    sei(); // allow interrupts
    if (arduinoSerial.read() == "Raspberry says Hello!")
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  
}

void loop() {}
