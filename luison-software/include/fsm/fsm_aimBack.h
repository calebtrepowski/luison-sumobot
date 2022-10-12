#ifndef _fsm_escape_back_h_
#define _fsm_escape_back_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_BACK

namespace aimBack_fsm
{

    const uint_fast8_t goFrontDuration = 300U; // ms
    const uint_fast8_t maxTurnDuration = 500U; // ms

    /* por alguna razon el giroscopio lee a la mitad */
    const uint_fast8_t turnAngle = 2 * 180U; // °
    uint_fast32_t referenceTime;

    uint_fast32_t t;
    const uint_fast8_t goFrontSpeed = 6U;
    const uint_fast8_t turnSpeed = 10U;

    void goFront();
    void turn180Right();

    void goFront()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
#ifdef DEBUG
            Serial.println("aim back: go front");
#endif
            fsm::priorInnerState = fsm::innerState;
            referenceTime = millis();
            motors::setSpeedBoth(goFrontDuration);
            motors::goForward();
        }

        t = millis();

        if (t - referenceTime > goFrontDuration)
        {
            fsm::innerState = turn180Right;
        }
    }

    void turn180Right()
    {
        using namespace gyroscope;

        if (fsm::innerState != fsm::priorInnerState)
        {
#ifdef DEBUG
            Serial.println("aim back: turn 180 right");
#endif
            fsm::priorInnerState = fsm::innerState;
            mpu.update();
            motors::turnRight();
            referenceAngleZ = mpu.getAngleZ();
            referenceTime = millis();
        }

        if (motors::currentSpeed > turnSpeed)
        {
            motors::setSpeedBoth(motors::currentSpeed - 1);
        }
        else if (motors::currentSpeed < turnSpeed)
        {
            motors::setSpeedBoth(motors::currentSpeed + 1);
        }

        mpu.update();
        currentAngleZ = mpu.getAngleZ();

        if (abs(currentAngleZ - referenceAngleZ) > turnAngle)
        {
            fsm::innerState = NULL;
        }

        t = millis();
        if (t - referenceTime > maxTurnDuration)
        {
            fsm::innerState = NULL;
        }
    }
}

namespace fsm
{
    void aimBack()
    {
        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("aim back");
#endif
            fsm::priorState = fsm::state;

            fsm::priorInnerState = NULL;
            fsm::innerState = aimBack_fsm::goFront;
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

        if (fsm::innerState != NULL)
        {
            fsm::innerState();
            return;
        }

        fsm::state = fsm::normalSearch;

        // proximity::readStates();

        // TRANSITION_ATTACK_FRONT
        // TRANSITION_AIM_FRONT_RIGHT
        // TRANSITION_AIM_FRONT_LEFT

        // gyroscope::mpu.update();
        // gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();

        // if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimBack_fsm::turnAngle)
        // {
        //     fsm::state = normalSearch;
        //     return;
        // }

        // aimBack_fsm::t = millis();

        // if (aimBack_fsm::t - aimBack_fsm::referenceTime > aimBack_fsm::maxTurnDuration)
        // {
        //     fsm::state = normalSearch;
        //     return;
        // }
    }
}

#endif

#endif