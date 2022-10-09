#ifndef _on_off_interruption_h
#define _on_off_interruption_h
#include <Arduino.h>
#include "onOffControl.h"
#include "dipSwitch.h"

namespace onOffControl
{
    volatile bool state;

    uint_fast32_t buttonTime = 0;
    uint_fast32_t lastButtonTime = 0;
    uint_fast32_t lastOnTime = 0;

    const uint_fast8_t debounceTime = 10;   // ms
    const uint_fast8_t minimumOnTime = 500; // ms

    uint_fast8_t strategy = 0;

    void IRAM_ATTR toggleStateISR()
    {
        buttonTime = millis();
        if (buttonTime - lastButtonTime > debounceTime)
        {
            if (buttonTime - lastOnTime > minimumOnTime)
            {
                // para que no se apague si el árbitro mantiene apretado
                if (!state)
                {
                    strategy = dipSwitch::readInt();
                }
                state = !state;
                lastOnTime = buttonTime;
            }
        }
        lastButtonTime = buttonTime;
    }

    void setOnOffInterruption()
    {
        attachInterrupt(control.pin, toggleStateISR, RISING);
    }
}

#endif