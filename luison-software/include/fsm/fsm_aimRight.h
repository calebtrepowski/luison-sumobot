#ifndef _fsm_aim_right_h_
#define _fsm_aim_right_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_RIGHT

namespace aimRight_fsm
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
    void aimRight()
    {
        using namespace gyroscope;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim right");
#endif
#ifdef DEBUG_BLUETOOTH
            bluetooth::SerialBT.println("aim right");
#endif
            fsm::priorState = fsm::state;

            mpu.update();
            motors::goForward(aimRight_fsm::aimSpeedOuter, aimRight_fsm::aimSpeedInner);
            referenceAngleZ = mpu.getAngleZ();
            aimRight_fsm::referenceTime = millis();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_BACK

        mpu.update();
        currentAngleZ = mpu.getAngleZ();

        if (abs(currentAngleZ - referenceAngleZ) > aimRight_fsm::turnAngle)
        {
            fsm::state = normalSearch;
            return;
        }

        aimRight_fsm::t = millis();

        if (aimRight_fsm::t - aimRight_fsm::referenceTime > aimRight_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif

#endif