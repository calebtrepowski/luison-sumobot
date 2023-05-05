#ifndef _on_off_killswitch_h_
#define _on_off_killswitch_h_

#if ON_OFF_METHOD == 3
#include "onOffControl.h"

#include "fsm/fsm.h"
#include "pinNumbers.h"

namespace onOffControl
{
    void setup()
    {
        pinMode(KILL_SWITCH_START, INPUT_PULLDOWN);
        pinMode(KILL_SWITCH_EMERGENCY_STOP, INPUT_PULLUP);

        attachInterrupt(KILL_SWITCH_EMERGENCY_STOP, switchToIdleISR, FALLING);
    }

    bool loadStart(uint_fast8_t &active)
    {
        if (digitalRead(KILL_SWITCH_START))
        {
            active = 1;
            return true;
        }

        active = 0;
        return false;
    }

    void IRAM_ATTR switchToIdleISR()
    {
        fsm::state = fsm::idle;
    }

}

#endif

#endif