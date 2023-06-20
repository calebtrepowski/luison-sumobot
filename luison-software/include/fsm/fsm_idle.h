#ifndef _fsm_idle_h_
#define _fsm_idle_h_

#include "fsm.h"

namespace fsm
{
    void idle()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("idle");

            fsm::priorState = fsm::state;
        }
        motors::brake();
    }
}

#endif