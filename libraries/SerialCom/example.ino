#include "SerialCom.h"
#include "utils.h"

SerialCom arduino_serial;

void setup() {
    arduino_serial.init();

    pinMode(LED_BUILTIN, OUTPUT);

    timer3_init(1);
    timer4_init(0.02);
}

ISR(TIMER3_COMPA_vect){ // timer3 interrupt
    sei(); // allow interrupts
    arduino_serial.write("Arduino says Hello!");
}

ISR(TIMER4_COMPA_vect){ // timer4 interrupt
    sei(); // allow interrupts
    if (arduino_serial.read() == "Raspberry says Hello!")
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  
}

void loop() {}
