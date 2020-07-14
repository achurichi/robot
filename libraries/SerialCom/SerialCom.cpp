#include "SerialCom.h"
#include "CRC32.h"

SerialCom::SerialCom(uint32_t port=115200)
{
    this->port = port;
}

// Send the message for the serial port with the specified baud rate 
bool SerialCom::write(String msg)
{
    CRC32 crc;
    for (int i=0; i<msg.length(); i++)
        crc.update((byte)msg[i]);
    msg += "_";
    msg += String(crc.finalize());

    Serial.begin(this->port);
    Serial.println(msg);
    // Serial.end();

    return true; //Add comprobation method
}

// Read all the content in the serial port
String SerialCom::read()
{
    String msg = "";
    String crc_code = "";
    bool is_crc = false;
    CRC32 crc;
    uint8_t data_byte;

    Serial.begin(this->port);
    if (Serial.available() > 0) 
    {
        delay(2);
        msg = ""; //sacar
        while (Serial.available() > 0)
        {
            data_byte = Serial.read();
            if (char(data_byte) == '_') // Next byte is crc
                is_crc = true;
            else
            {
                if (is_crc) // Read crc
                    crc_code += char(data_byte);  
                else // Read data
                {
                    crc.update(data_byte);
                    msg += char(data_byte);  
                }
            }
        }
    }
    // Serial.end();

    crc_code = crc_code.substring(0, crc_code.length() - 1); // Remove '\n' at the end
    if (crc_code == String(crc.finalize()))
        return msg;
    else
        return "%%error";
}