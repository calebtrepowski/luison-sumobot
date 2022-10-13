#ifndef _fsm_escape_back_h_
#define _fsm_escape_back_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_BACK

namespace aimBack_fsm
{

    const uint_fast8_t goFrontDuration = AIM_BACK_GO_FRONT_DURATION; // ms
    const uint_fast8_t maxTurnDuration = AIM_BACK_MAX_TURN_DURATION; // ms
    const uint_fast8_t turnAngle = AIM_BACK_TURN_ANGLE;              // °
    uint_fast32_t referenceTime;
    uint_fast32_t t;
    const uint_fast8_t goFrontSpeed = AIM_BACK_GO_FRONT_SPEED;
    const uint_fast8_t turnSpeed = AIM_BACK_TURN_SPEED;

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
            motors::goForward(goFrontDuration);
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
            motors::turnRight(turnSpeed);
            referenceAngleZ = mpu.getAngleZ();
            referenceTime = millis();
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

        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT

        if (fsm::innerState != NULL)
        {
            fsm::innerState();
            return;
        }

        fsm::state = fsm::normalSearch;
    }
}

#endif

#endif