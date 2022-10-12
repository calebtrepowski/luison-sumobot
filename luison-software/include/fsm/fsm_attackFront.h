#ifndef _fsm_attackFront_h_
#define _fsm_attackFront_h_

#include "fsm.h"

#ifdef ENABLE_STATE_ATTACK_FRONT

namespace attackFront_fsm
{
    const uint_fast8_t attackFrontSpeed = ATTACK_FRONT_SPEED;
}

namespace fsm
{
    void attackFront()
    {
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("attack front");
#endif
            fsm::priorState = fsm::state;
            motors::setSpeedBoth(attackFront_fsm::attackFrontSpeed);
            motors::goForward();
        }

        line::readValues();
        if (LINE_FRONT_LEFT_DETECTED)
        {
            fsm::state = fsm::avoidFallFrontLeft;
            return;
        }

        if (LINE_FRONT_RIGHT_DETECTED)
        {
            fsm::state = fsm::avoidFallFrontRight;
            return;
        }

        proximity::readStates();
        if (OPPONENT_NOT_DETECTED_FRONT_CENTER)
        {
            fsm::state = fsm::normalSearch;
            return;
        }

        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_LEFT

        // if (OPPONENT_DETECTED_BACK)
        // {
        //     fsm::state = fsm::aimBack;
        //     return;
        // }
    }
}

#endif

#endif