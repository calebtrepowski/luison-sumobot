#ifndef _fsm_aim_right_h_
#define _fsm_aim_right_h_

#include "fsm.h"

namespace aimRight_fsm
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
    void aimRight()
    {
        using namespace gyroscope;
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim right");
#endif
            fsm::priorState = fsm::state;

            mpu.update();
            motors::setSpeedBoth(aimRight_fsm::aimSpeed);
            motors::turnRight();
            referenceAngleZ = mpu.getAngleZ();
            aimRight_fsm::referenceTime = millis();
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

        if (OPPONENT_DETECTED_FRONT_CENTER_ONLY)
        {
            fsm::state = fsm::attackFront;
            return;
        }

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