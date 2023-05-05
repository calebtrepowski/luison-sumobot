#ifndef _fsm_diagonal_kickback_h_
#define _fsm_diagonal_kickback_h_

#include "fsm.h"

#ifdef ENABLE_STRATEGY_DIAGONAL_KICKBACK

namespace diagonalKickBack_fsm
{
    const uint_fast8_t maxReverseTime = DIAGONAL_KICKBACK_MAX_REVERSE_TIME;
    const uint_fast8_t innerReverseSpeed = DIAGONAL_KICKBACK_INNER_REVERSE_SPEED;
    const uint_fast8_t outerReverseSpeed = DIAGONAL_KICKBACK_OUTER_REVERSE_SPEED;
    uint_fast32_t referenceTime;
    uint_fast32_t currentTime;
}

namespace fsm
{
    void diagonalKickBack()
    {
        using namespace diagonalKickBack_fsm;
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN(std::string("diagonal kick back"));

            fsm::priorState = fsm::state;

            motors::goBack(innerReverseSpeed, outerReverseSpeed);
            referenceTime = millis();
        }

        proximity::readStates();
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_RIGHT

        currentTime = millis();
        if (currentTime - referenceTime > maxReverseTime)
        {
            fsm::state = fsm::normalSearch;
            return;
        }
    }
}

#endif

#endif