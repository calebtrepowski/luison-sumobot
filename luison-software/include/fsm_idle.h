#ifndef _fsm_idle_h_
#define _fsm_idle_h_
#include "fsm.h"
#include "motor.h"

namespace fsm
{
    void idle()
    {
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("idle");
#endif
            fsm::priorState = fsm::state;
            motors::brake();
            motors::setSpeedBoth(0U);
        }
    }
}
#endif