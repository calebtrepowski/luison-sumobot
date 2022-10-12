#ifndef _fsm_aim_left_h_
#define _fsm_aim_left_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_LEFT

namespace aimLeft_fsm
{
    const uint_fast8_t maxTurnDuration = 1000U; // ms

    /* por alguna razon el giroscopio lee a la mitad */
    const uint_fast8_t turnAngle = 2 * 75; // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t aimSpeed = 8U;
}

namespace fsm
{
    void aimLeft()
    {
        using namespace gyroscope;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim left");
#endif
            fsm::priorState = fsm::state;

            mpu.update();
            motors::setSpeedBoth(aimLeft_fsm::aimSpeed);
            motors::turnLeft();
            referenceAngleZ = mpu.getAngleZ();
            aimLeft_fsm::referenceTime = millis();
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

        proximity::readStates();

        TRANSITION_ATTACK_FRONT

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