#ifndef _on_off_control_h
#define _on_off_control_h

#include "Arduino.h"
#include "pinNumbers.h"

namespace onOffControl
{
    uint_fast8_t active;

    void setup();
    bool loadStart(uint_fast8_t &active);
}

#include "onOffKillSwitch.h"
#include "onOffBluetooth.h"

#endif
