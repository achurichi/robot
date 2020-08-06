#include "SerialCom.h"
#include <Crc16.h>

// Initialize the serial communication with the specified baud rate
void SerialCom::init(uint32_t port=115200)
{
    Serial.begin(port);
    Serial.setTimeout(4);
}

// Send the message through the serial port 
void SerialCom::write(String msg)
{
    Crc16 crc;
    for (int i=0; i<msg.length(); i++)
        crc.updateCrc((byte)msg[i]);
    msg += "_";
    msg += String(crc.getCrc());

    Serial.println(msg);
}

// Read all the content in the serial port
String SerialCom::read()
{
    String msg = "";
    String crc_from_msg = "";
    int underscore_idx;
    Crc16 crc;

    if (Serial.available() > 0)
        msg = Serial.readStringUntil('\n');
    
    underscore_idx = msg.lastIndexOf('_');
    crc_from_msg = msg.substring(underscore_idx + 1, msg.length());
    msg = msg.substring(0, underscore_idx);

    for (int i=0; i<msg.length(); i++)
        crc.updateCrc((byte)msg.charAt(i));

    if (crc_from_msg == String(crc.getCrc()))
        return msg;
    else
        return "%%error";
}