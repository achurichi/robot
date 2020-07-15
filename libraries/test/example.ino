#include "utils.h"
unsigned long timer3;
unsigned long timer4;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    timer3_init(1);
    timer4_init(0.02);

    Serial.begin(115200);

    timer3 = millis();
    timer4 = millis();
}

ISR(TIMER3_COMPA_vect){ // timer3 interrupt
    Serial.println("Arduino says Hello!");
    // Serial.println(String(millis()-timer3));
    // timer3 = millis();
}

ISR(TIMER4_COMPA_vect){ // timer4 interrupt
    String msg = "";

    if (Serial.available() > 0) 
        while (Serial.available() > 0)
            msg += char(Serial.read());

    if (msg == "Raspberry says Hello!\n")
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  

    // Serial.println(String(millis()-timer4));
    // timer4 = millis();
}

void loop() {}
