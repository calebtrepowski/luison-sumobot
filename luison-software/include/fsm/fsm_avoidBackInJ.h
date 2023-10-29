#ifndef _avoid_back_in_j_h_
#define _avoid_back_in_j_h_

#include "fsm.h"

namespace fsm
{
    void avoidBackInJ(void)
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid back in J");
            fsm::priorState = fsm::state;
            motors::goBack(configValues->avoidBackInJInnerSpeed, configValues->avoidBackInJOuterSpeed);
            fsm::referenceTime = millis();
        }

        line::readValues();
        proximity::readStates();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_BACK


        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidBackInJMaxTurnDuration)
        {
            fsm::state = fsm::defaultExploringState;
            return;
        }
    }
}

#endif