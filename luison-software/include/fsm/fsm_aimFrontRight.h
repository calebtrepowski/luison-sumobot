#ifndef _fsm_aim_front_right_h_
#define _fsm_aim_front_right_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_FRONT_RIGHT

namespace aimFrontRight_fsm
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
    void aimFrontRight()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("aim front right");

            fsm::priorState = fsm::state;

#if defined(ENABLE_GYRO)
            gyroscope::mpu.update();
#endif
            motors::goForward(aimFrontRight_fsm::aimSpeedOuter, aimFrontRight_fsm::aimSpeedInner);
#if defined(ENABLE_GYRO)
            gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
#endif
            aimFrontRight_fsm::referenceTime = millis();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_BACK

#if defined(ENABLE_GYRO)
        gyroscope::mpu.update();
        gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();

        if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimFrontRight_fsm::turnAngle)
        {
            fsm::state = normalSearch;
            return;
        }
#endif

        aimFrontRight_fsm::currentTime = millis();

        if (aimFrontRight_fsm::currentTime - aimFrontRight_fsm::referenceTime > aimFrontRight_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif

#endif