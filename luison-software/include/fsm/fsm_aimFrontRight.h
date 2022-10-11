#ifndef _fsm_aim_front_right_h_
#define _fsm_aim_front_right_h_

#include "fsm.h"

namespace aimFrontRight_fsm
{
    const uint_fast8_t maxTurnDuration = 50U; // ms

    /* por alguna razon el giroscopio lee a la mitad */
    const uint_fast8_t turnAngle = 2 * 50; // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t aimSpeed = 3U;
    const uint_fast8_t aimDeltaSpeed = 9U;
    // juntos no tienen que sumar más de 14!
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
            motors::goForward();
            referenceAngleZ = mpu.getAngleZ();
            aimFrontRight_fsm::referenceTime = millis();
            motors::setSpeed(aimFrontRight_fsm::aimSpeed, aimFrontRight_fsm::aimSpeed + aimFrontRight_fsm::aimDeltaSpeed, aimFrontRight_fsm::aimSpeed);
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

        if (OPPONENT_DETECTED_FRONT_LEFT)
        {
            fsm::state = fsm::aimFrontLeft;
            return;
        }

        // if (OPPONENT_DETECTED_BACK)
        // {
        //     fsm::state = fsm::escapeBack;
        //     return;
        // }

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