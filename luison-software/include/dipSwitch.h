#ifndef _dip_switch_h
#define _dip_switch_h
#include <Arduino.h>
#include "pinNumbers.h"

namespace dipSwitch
{
    int bit1, bit0;
    struct DipSwitch
    {
        uint_fast8_t pinBit0;
        uint_fast8_t pinBit1;
    } rotaryDip;

    void setup()
    {
        rotaryDip = {
            .pinBit0 = DIP_BIT_0,
            .pinBit1 = DIP_BIT_1};

        pinMode(rotaryDip.pinBit0, INPUT_PULLDOWN);
        pinMode(rotaryDip.pinBit1, INPUT_PULLDOWN);
    }

    int readInt()
    {
        bit1 = digitalRead(rotaryDip.pinBit1);
        bit0 = digitalRead(rotaryDip.pinBit0);
        return bit1 * 2 + bit0;
    }
}

#endif