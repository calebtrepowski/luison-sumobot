#ifndef _fsm_escape_back_h_
#define _fsm_escape_back_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_BACK

namespace aimBack_fsm
{
    const uint_fast8_t maxTurnDuration = AIM_BACK_MAX_TURN_DURATION; // ms
    const uint_fast8_t turnAngle = AIM_BACK_TURN_ANGLE;              // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t turnSpeedOuter = AIM_BACK_SPEED_OUTER;
    const uint_fast8_t turnSpeedInner = AIM_BACK_SPEED_INNER;
}

namespace fsm
{
    void aimBack()
    {
        using namespace aimBack_fsm;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim back");
#endif
            fsm::priorState = fsm::state;

            gyroscope::mpu.update();
            motors::turnDifferentSpeeds(aimBack_fsm::turnSpeedInner, aimBack_fsm::turnSpeedOuter);
            gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
            referenceTime = millis();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_RIGHT

        gyroscope::mpu.update();
        gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();
        if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimBack_fsm::turnAngle)
        {
            fsm::state = normalSearch;
            return;
        }

        aimBack_fsm::t = millis();
        if (aimBack_fsm::t - aimBack_fsm::referenceTime > aimBack_fsm::maxTurnDuration)
        {
            fsm::state = normalSearch;
            return;
        }
    }
}

#endif

#endif