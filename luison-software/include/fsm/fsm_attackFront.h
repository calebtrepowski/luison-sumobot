#ifndef _fsm_attackFront_h_
#define _fsm_attackFront_h_

#include "fsm.h"

namespace attackFront_fsm
{
    const uint_fast8_t attackFrontSpeed = 6U;
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
            // motors::setSpeedBoth(attackFront_fsm::attackFrontSpeed);
            motors::goForward();
        }

        if (motors::currentSpeed > attackFront_fsm::attackFrontSpeed)
        {
            motors::setSpeedBoth(motors::currentSpeed - 1);
        }
        else if (motors::currentSpeed < attackFront_fsm::attackFrontSpeed)
        {
            motors::setSpeedBoth(motors::currentSpeed + 1);
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
        if (OPPONENT_DETECTED_FRONT_RIGHT)
        {
            fsm::state = fsm::aimFrontRight;
            return;
        }
        if (OPPONENT_DETECTED_FRONT_LEFT)
        {
            fsm::state = fsm::aimFrontLeft;
            return;
        }
        // if (OPPONENT_DETECTED_BACK)
        // {
        //     fsm::state = fsm::escapeBack;
        //     return;
        // }
    }
}

#endif