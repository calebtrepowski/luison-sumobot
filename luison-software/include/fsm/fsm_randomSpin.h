#ifndef _fsm_random_spin_h_
#define _fsm_random_spin_h_

#include "fsm.h"

#ifdef ENABLE_STRATEGY_RANDOM_SPIN

namespace randomSpin_fsm
{
    uint_fast8_t goForwardTime;
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    uint_fast8_t turnAngle;
}

namespace fsm
{
    void randomSpin()
    {
        using namespace randomSpin_fsm;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim front right");
#endif
            fsm::priorState = fsm::state;

            referenceTime = millis();
            
        }
    }
}

#endif

#endif