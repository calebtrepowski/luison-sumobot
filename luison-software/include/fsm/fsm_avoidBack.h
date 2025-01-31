#ifndef _fsm_avoid_back_h_
#define _fsm_avoid_back_h_

#include "fsm.h"

namespace fsm
{
    void avoidBack()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid Back");
            fsm::priorState = fsm::state;
            motors::turnLeft(configValues->avoidBackTurnSpeed);
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

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidBackMaxTurnDuration)
        {
            fsm::state = fsm::defaultExploringState;
            return;
        }
    }
}

#endif