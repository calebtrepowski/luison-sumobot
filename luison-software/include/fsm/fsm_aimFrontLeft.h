#ifndef _fsm_aim_front_left_h_
#define _fsm_aim_front_left_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_FRONT_LEFT

namespace aimFrontLeft_fsm
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
    void aimFrontLeft()
    {
        using namespace gyroscope;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim front left");
#endif
            fsm::priorState = fsm::state;

            mpu.update();
            motors::turnDifferentSpeeds(aimFrontLeft_fsm::aimSpeedOuter, aimFrontLeft_fsm::aimSpeedInner);
            referenceAngleZ = mpu.getAngleZ();
            aimFrontLeft_fsm::referenceTime = millis();
        }

        line::readValues();


        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();

        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_RIGHT

        // if (OPPONENT_DETECTED_BACK)
        // {
        //     fsm::state = fsm::aimBack;
        //     return;
        // }

        mpu.update();
        currentAngleZ = mpu.getAngleZ();

        if (abs(currentAngleZ - referenceAngleZ) > aimFrontLeft_fsm::turnAngle)
        {
            fsm::state = normalSearch;
            return;
        }

        aimFrontLeft_fsm::t = millis();

        if (aimFrontLeft_fsm::t - aimFrontLeft_fsm::referenceTime > aimFrontLeft_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif

#endif