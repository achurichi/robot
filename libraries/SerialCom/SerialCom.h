#ifndef SerialCom_h
#define SerialCom_h

#include "Arduino.h"

class SerialCom
{
    public:
        SerialCom(uint32_t port);
        bool write(String msg);
        String read();

    private:
        uint32_t port;
};

#endif