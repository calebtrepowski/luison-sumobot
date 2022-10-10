#ifndef _fsm_normal_search_h_
#define _fsm_normal_search_h_

#include "fsm.h"

namespace normalSearch_fsm
{
    const uint_fast8_t normalSearchSpeed = 3U;
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
            motors::setSpeedBoth(normalSearch_fsm::normalSearchSpeed);
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

        // proximity::readStates();
        // if (OPPONENT_DETECTED_FRONT_CENTER_ONLY)
        // {
        // }
        // if (OPPONENT_DETECTED_BACK_ONLY)
        // {
        //     turnAngle = 180;
        //     state = turnLeft;
        //     return;
        // }
    }
}
#endif