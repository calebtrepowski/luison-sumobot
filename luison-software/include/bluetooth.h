#ifndef _bluetooth_h
#define _bluetooth_h

namespace bluetooth
{
    void setup();
    void echo();
    bool loadStart(uint_fast8_t &active);
}


#include "bluetoothSerial.h"
#include "bluetoothBLE.h"
#include "bluetoothDabble.h"

#endif