#ifndef _on_off_control_h
#define _on_off_control_h

#include "Arduino.h"
#include "pinNumbers.h"

namespace onOffControl
{
    struct OnOffControl
    {
        uint_fast8_t pin;
    } control;

    void setup()
    {
        control.pin = ON_OFF_CONTROL;
        pinMode(control.pin, INPUT_PULLDOWN);
    }
}

#endif
