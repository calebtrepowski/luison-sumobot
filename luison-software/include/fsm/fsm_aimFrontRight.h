#ifndef _fsm_aim_front_right_h_
#define _fsm_aim_front_right_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_FRONT_RIGHT

namespace aimFrontRight_fsm
{
    const uint_fast8_t maxTurnDuration = AIM_FRONT_SIDE_MAX_TURN_DURATION; // ms
    const uint_fast8_t turnAngle = AIM_FRONT_SIDE_TURN_ANGLE;              // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t aimSpeedOuter = AIM_FRONT_SIDE_SPEED_OUTER;
    const uint_fast8_t aimSpeedInner = AIM_FRONT_SIDE_SPEED_INNER;
}

namespace fsm
{
    void aimFrontRight()
    {
        using namespace gyroscope;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim front right");
#endif
            fsm::priorState = fsm::state;

            mpu.update();
            motors::turnDifferentSpeeds(aimFrontRight_fsm::aimSpeedOuter, aimFrontRight_fsm::aimSpeedInner);
            referenceAngleZ = mpu.getAngleZ();
            aimFrontRight_fsm::referenceTime = millis();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_AIM_RIGHT
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_BACK

        mpu.update();
        currentAngleZ = mpu.getAngleZ();

        if (abs(currentAngleZ - referenceAngleZ) > aimFrontRight_fsm::turnAngle)
        {
            fsm::state = normalSearch;
            return;
        }

        aimFrontRight_fsm::t = millis();

        if (aimFrontRight_fsm::t - aimFrontRight_fsm::referenceTime > aimFrontRight_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif

#endif