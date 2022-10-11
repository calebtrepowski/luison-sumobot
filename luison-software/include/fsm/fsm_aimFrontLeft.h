#ifndef _fsm_aim_front_left_h_
#define _fsm_aim_front_left_h_

#include "fsm.h"

namespace aimFrontLeft_fsm
{
    const uint_fast8_t maxTurnDuration = 500U; // ms

    /* por alguna razon el giroscopio lee a la mitad */
    const uint_fast8_t turnAngle = 2 * 90; // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t aimSpeed = 3U;
    const uint_fast8_t aimDeltaSpeed = 9U;
    // juntos no tienen que sumar más de 14!
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
            motors::goForward();
            referenceAngleZ = mpu.getAngleZ();
            aimFrontLeft_fsm::referenceTime = millis();
            motors::setSpeed(aimFrontLeft_fsm::aimSpeed + aimFrontLeft_fsm::aimDeltaSpeed, aimFrontLeft_fsm::aimSpeed, aimFrontLeft_fsm::aimSpeed);
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