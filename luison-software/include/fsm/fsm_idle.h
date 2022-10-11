#ifndef _fsm_idle_h_
#define _fsm_idle_h_

#include "fsm.h"

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
        }
        if (motors::currentSpeed > 0U)
        {
            motors::setSpeedBoth(motors::currentSpeed - 1);
        }
        else if (motors::currentSpeed == 0U)
        {
            motors::brake();
        }
    }
}

#endif