#ifndef _fsm_attackFront_h_
#define _fsm_attackFront_h_

#include "fsm.h"

#ifdef ENABLE_STATE_ATTACK_FRONT

namespace attackFront_fsm
{
    const uint_fast8_t fullGasSpeed = ATTACK_FRONT_FULL_GAS_SPEED;
    const uint_fast8_t fullGasTime = ATTACK_FRONT_FULL_GAS_TIME;
    const uint_fast8_t liftOffSpeed = ATTACK_FRONT_LIFT_OFF_SPEED;
    const uint_fast8_t liftOffTime = ATTACK_FRONT_LIFT_OFF_TIME;
    uint_fast32_t t;
}

namespace fsm
{
    void attackFront()
    {
        using namespace attackFront_fsm;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("attack front");
#endif
            fsm::priorState = fsm::state;
            motors::goForward(fullGasSpeed);
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

        t = millis();
        if (t % fullGasTime > fullGasTime)
        {
            motors::goForward(liftOffSpeed);
        }
        else if (t % liftOffTime > liftOffTime)
        {
            motors::goForward(fullGasSpeed);
        }
    }
}

#endif

#endif