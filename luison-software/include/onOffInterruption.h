#ifndef _on_off_interruption_h
#define _on_off_interruption_h
#include <Arduino.h>
#include "onOffControl.h"
#include "dipSwitch.h"
#include "fsm/fsm.h"

namespace onOffInterruption
{
    uint_fast32_t buttonTime = 0UL;
    uint_fast32_t lastButtonTime = 0UL;
    uint_fast32_t lastOnTime = 0UL;
    uint_fast32_t lastOffTime = 0UL;

    const uint_fast8_t debounceTime = 30;     // ms
    const uint_fast8_t minimumOnTime = 500;   // ms
    const uint_fast8_t minimumOffTime = 2000; // ms

    uint_fast8_t initialStrategy = 0;

    void IRAM_ATTR toggleIdleISR()
    {
        buttonTime = millis();
        if (buttonTime - lastButtonTime > debounceTime)
        {
            if (fsm::state == fsm::idle)
            {
                if (buttonTime - lastOnTime > minimumOffTime || lastOnTime == 0)
                {
                    // minimumOnTime es para que no se apague si el arbitro mantiene apretado

                    initialStrategy = dipSwitch::readInt();
                    switch (initialStrategy)
                    {
                    // case 1:
                    //     state = diagonalAttack;
                    //     break;
                    // case 2:
                    //     state = diagonalKickBack;
                    //     break;
                    // case 3:
                    // break;
                    default:
                        fsm::state = fsm::normalSearch;
                        break;
                    }

                    lastOffTime = buttonTime;
                }
            }
            else
            {
                if (buttonTime - lastOffTime > minimumOnTime)
                {
                    fsm::state = fsm::idle;
                    lastOnTime = buttonTime;
                }
            }
        }

        lastButtonTime = buttonTime;
    }

    void setOnOffInterruption()
    {
        attachInterrupt(onOffControl::control.pin, toggleIdleISR, RISING);
    }
}

#endif