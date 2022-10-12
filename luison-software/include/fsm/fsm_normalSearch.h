#ifndef _fsm_normal_search_h_
#define _fsm_normal_search_h_

#include "fsm.h"

namespace normalSearch_fsm
{
    const uint_fast8_t normalSearchSpeed = NORMAL_SEARCH_SPEED;
}

namespace fsm
{
    void normalSearch()
    {
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("normal operation");
#endif
            fsm::priorState = fsm::state;
            motors::goForward();
            motors::setSpeedBoth(normalSearch_fsm::normalSearchSpeed);
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
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_RIGHT

        // if (OPPONENT_DETECTED_BACK)
        // {
        //     fsm::state = fsm::escapeBack;
        //     return;
        // }
    }
}

#endif