#ifndef _fsm_normal_search_h_
#define _fsm_normal_search_h_

#include "fsm.h"

namespace fsm
{
    void normalSearch()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("normal operation");
            fsm::priorState = fsm::state;
            motors::goForward(configValues->normalInitialSearchSpeed);
            fsm::referenceTime = millis();
            // motors::brake(); //uncomment for testing turns
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_BACK

        if (millis() - fsm::referenceTime > fsm::configValues->normalInitialSearchDuration)
        {
            motors::goForward(configValues->normalSearchSpeed);
        }
    }
}

#endif