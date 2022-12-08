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
#ifdef DEBUG_BLUETOOTH
            bluetooth::SerialBT.println("idle");
#endif
            fsm::priorState = fsm::state;
        }
        motors::brake();
    }
}

#endif