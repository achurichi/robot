#include "SerialCom.h"

SerialCom::SerialCom(uint32_t port=115200)
{
    this->port = port;
}

// Send the message for the serial port with the specified baud rate 
bool SerialCom::write(String msg)
{
    Serial.begin(this->port);
    Serial.print(msg);
    Serial.end();

    return true; //Add comprobation method
}

// Read all the content in the serial port
String SerialCom::read()
{
    String msg = "";
    Serial.begin(this->port);
    if (Serial.available() > 0) 
    {
        delay(2);
        msg = "";
        while (Serial.available() > 0)
        //while (!msg.endsWith("%e"))
        msg += char(Serial.read());  
    }
    Serial.end();

    return msg;
    // Serial.println(msg.toFloat()); //servoMotor.write(msg.toFloat());
}