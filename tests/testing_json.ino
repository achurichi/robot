#include <ArduinoJson.h>
#include "libraries/SerialCom/SerialCom.h"
#include "libraries/utils.h"

SerialCom arduino_serial;
data myData;
StaticJsonDocument<400> doc_read;
StaticJsonDocument<400> doc_send;

void setup() {
    arduino_serial.init();
    timer3_init(1); 
    timer4_init(1); 

    myData.m_1 = 1;
    myData.m_2 = 2;
    myData.m_3 = 3;
    myData.state = true;
}

ISR(TIMER3_COMPA_vect){ // timer3 interrupt
    sei(); // allow interrupts
    deserializeJson(doc_read, arduino_serial.read());

    String pi_says = doc_read["pi_says"];
    float num_1 = doc_read["numbers"][0];
}

ISR(TIMER4_COMPA_vect){ // timer3 interrupt
    sei(); // allow interrupts

    doc_send["m_1"] = myData.m_1;
    doc_send["m_2"] = myData.m_2;
    doc_send["m_3"] = myData.m_3;
    doc_send["state"] = myData.state;

    arduino_serial.write(doc_send.as<String>());
}

void loop() {}