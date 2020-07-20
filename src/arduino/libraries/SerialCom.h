#ifndef SerialCom_h
#define SerialCom_h

#include "Arduino.h"

class SerialCom
{
    public:
        void init(uint32_t port);
        void write(String msg);
        String read();
};

#endif