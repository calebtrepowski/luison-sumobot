#ifndef _fsm_bullet_h
#include "fsm.h"

namespace fsm
{
    void bullet()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("bullet");
            fsm::priorState = fsm::state;
            motors::goForward(configValues->bulletSpeed);
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
    }
}

#endif