#ifndef _fsm_attackFront_h_
#define _fsm_attackFront_h_

#include "fsm.h"

#ifdef ENABLE_STATE_ATTACK_FRONT

namespace attackFront_fsm
{
    uint_fast8_t currentSpeed;
}

namespace fsm
{
    void attackFront()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("attack front");

            fsm::priorState = fsm::state;

            motors::goForward(fsm::configValues->attackFrontFullGasSpeed);
            attackFront_fsm::currentSpeed = fsm::configValues->attackFrontFullGasSpeed;
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        if (OPPONENT_NOT_DETECTED_FRONT_CENTER)
        {
            fsm::state = fsm::normalSearch;
            return;
        }

        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_BACK

        fsm::currentTime = millis();
        if (fsm::currentTime % fsm::configValues->attackFrontLiftOffTime > fsm::configValues->attackFrontFullGasTime && attackFront_fsm::currentSpeed == fsm::configValues->attackFrontFullGasSpeed)
        {
            DEBUG_PRINTLN("lift off speed");
            motors::goForward(fsm::configValues->attackFrontLiftOffSpeed);
            attackFront_fsm::currentSpeed = fsm::configValues->attackFrontLiftOffSpeed;
        }
        else if (attackFront_fsm::currentSpeed == fsm::configValues->attackFrontLiftOffSpeed)
        {
            DEBUG_PRINTLN("full gas speed");
            motors::goForward(fsm::configValues->attackFrontFullGasSpeed);
            attackFront_fsm::currentSpeed = fsm::configValues->attackFrontFullGasSpeed;
        }
    }
}

#endif

#endif