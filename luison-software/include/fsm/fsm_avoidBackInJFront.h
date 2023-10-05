#ifndef _avoid_back_in_j_front_h_
#define _avoid_back_in_j_front_h_

#include "fsm.h"

namespace fsm
{
    void avoidBackInJFront(void)
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid back in J front");
            fsm::priorState = fsm::state;
            motors::goForward(configValues->avoidBackInJFrontInnerSpeed, configValues->avoidBackInJFrontOuterSpeed);
            fsm::referenceTime = millis();
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

        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidBackInJFrontMaxTurnDuration)
        {
            fsm::state = fsm::defaultExploringState;
            return;
        }
    }
}

#endif