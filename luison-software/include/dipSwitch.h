#ifndef _dip_switch_h
#define _dip_switch_h
#include <Arduino.h>
#include "pinNumbers.h"

namespace dipSwitch
{
    struct DipSwitch
    {
        uint_fast8_t pinBit0;
        uint_fast8_t pinBit1;
        uint_fast8_t pinBit2;
        uint_fast8_t pinBit3;
    } rotaryDip;

    void setup()
    {
        rotaryDip = {
            .pinBit0 = DIP_BIT_0,
            .pinBit1 = DIP_BIT_1,
            .pinBit2 = DIP_BIT_2,
            .pinBit3 = DIP_BIT_3};

        pinMode(rotaryDip.pinBit0, INPUT_PULLDOWN);
        pinMode(rotaryDip.pinBit1, INPUT_PULLDOWN);
        pinMode(rotaryDip.pinBit2, INPUT_PULLDOWN);
        pinMode(rotaryDip.pinBit3, INPUT_PULLDOWN);
    }

    const uint_fast8_t readInt()
    {
        int bit3, bit2, bit1, bit0;

        bit3 = digitalRead(rotaryDip.pinBit3);
        bit2 = digitalRead(rotaryDip.pinBit2);
        bit1 = digitalRead(rotaryDip.pinBit1);
        bit0 = digitalRead(rotaryDip.pinBit0);

        return bit3 * 8 + bit2 * 4 + bit1 * 2 + bit0;
    }
}

#endif