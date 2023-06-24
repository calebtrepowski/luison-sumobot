#ifndef _fsm_aim_front_left_h_
#define _fsm_aim_front_left_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_FRONT_LEFT

namespace aimFrontLeft_fsm
{
    const uint_fast8_t maxTurnDuration = AIM_FRONT_SIDE_MAX_TURN_DURATION; // ms
    const uint_fast8_t turnAngle = AIM_FRONT_SIDE_TURN_ANGLE;              // °
    uint_fast32_t referenceTime;
    uint_fast32_t currentTime;
    const uint_fast8_t aimSpeedOuter = AIM_FRONT_SIDE_SPEED_OUTER;
    const uint_fast8_t aimSpeedInner = AIM_FRONT_SIDE_SPEED_INNER;
}

namespace fsm
{
    void aimFrontLeft()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("aim front left");

            fsm::priorState = fsm::state;

#if defined(ENABLE_GYRO)
            if (gyroscope::status == 0)
            {
                gyroscope::mpu.update();
                gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
            }
#endif
            aimFrontLeft_fsm::referenceTime = millis();
            motors::goForward(aimFrontLeft_fsm::aimSpeedInner, aimFrontLeft_fsm::aimSpeedOuter);
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_AIM_LEFT
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_BACK

#if defined(ENABLE_GYRO)
        if (gyroscope::status == 0)
        {
            gyroscope::mpu.update();
            gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();

            if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimFrontLeft_fsm::turnAngle)
            {
                fsm::state = normalSearch;
                return;
            }
        }
#endif

        aimFrontLeft_fsm::currentTime = millis();

        if (aimFrontLeft_fsm::currentTime - aimFrontLeft_fsm::referenceTime > aimFrontLeft_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif
#endif