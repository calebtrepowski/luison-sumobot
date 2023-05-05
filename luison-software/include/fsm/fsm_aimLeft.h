#ifndef _fsm_aim_left_h_
#define _fsm_aim_left_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_LEFT

namespace aimLeft_fsm
{
    const uint_fast8_t maxTurnDuration = AIM_SIDE_MAX_TURN_DURATION; // ms
    const uint_fast8_t turnAngle = AIM_SIDE_TURN_ANGLE;              // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t aimSpeedOuter = AIM_SIDE_SPEED_OUTER;
    const uint_fast8_t aimSpeedInner = AIM_SIDE_SPEED_INNER;
}

namespace fsm
{
    void aimLeft()
    {
        using namespace gyroscope;
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN(std::string("aim left"));

            fsm::priorState = fsm::state;

            mpu.update();
            motors::goForward(aimLeft_fsm::aimSpeedInner, aimLeft_fsm::aimSpeedOuter);
            referenceAngleZ = mpu.getAngleZ();
            aimLeft_fsm::referenceTime = millis();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_BACK

        mpu.update();
        currentAngleZ = mpu.getAngleZ();

        if (abs(currentAngleZ - referenceAngleZ) > aimLeft_fsm::turnAngle)
        {
            fsm::state = normalSearch;
            return;
        }

        aimLeft_fsm::t = millis();

        if (aimLeft_fsm::t - aimLeft_fsm::referenceTime > aimLeft_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif

#endif