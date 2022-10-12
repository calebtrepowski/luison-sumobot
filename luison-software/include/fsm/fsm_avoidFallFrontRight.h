#ifndef _fsm_avoid_fall_front_right_h_
#define _fsm_avoid_fall_front_right_h_

#include "fsm.h"

namespace avoidFallFrontRight_fsm
{
    const uint_fast8_t reverseDuration = 300U; // ms
    const uint_fast8_t maxTurnDuration = 500U; // ms
    uint_fast32_t t;

    /* por alguna razon el giroscopio lee a la mitad */
    const uint_fast8_t turnAngle = 2 * 30; // °
    uint_fast32_t referenceTime;

    const uint_fast8_t reverseSpeed = 5U; // ms
    const uint_fast8_t turnSpeed = 5U;    // ms

    void reverse();
    void turnLeft();

    void reverse()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
#ifdef DEBUG
            Serial.println("avoid fall front right: reverse");
#endif
            fsm::priorInnerState = fsm::innerState;
            referenceTime = millis();
            motors::setSpeedBoth(reverseSpeed);
            motors::goBack();
        }

        t = millis();

        if (t - referenceTime > reverseDuration)
        {
            fsm::innerState = turnLeft;
        }
    }

    void turnLeft()
    {
        using namespace gyroscope;
        if (fsm::innerState != fsm::priorInnerState)
        {
#ifdef DEBUG
            Serial.println("avoid fall front right: turn left");
#endif
            fsm::priorInnerState = fsm::innerState;
            mpu.update();
            motors::setSpeedBoth(turnSpeed);
            motors::turnLeft();
            referenceAngleZ = mpu.getAngleZ();
            referenceTime = millis();
        }

        mpu.update();
        currentAngleZ = mpu.getAngleZ();
        t = millis();

        if (abs(currentAngleZ - referenceAngleZ) > turnAngle || t - referenceTime > maxTurnDuration)
        {
            fsm::innerState = NULL;
        }
    }
}

namespace fsm
{
    void avoidFallFrontRight()
    {

        if (fsm::state != fsm::priorState)
        {
#ifdef DEBUG
            Serial.println("avoid fall front right");
#endif
            fsm::priorState = fsm::state;

            fsm::priorInnerState = NULL;
            fsm::innerState = avoidFallFrontRight_fsm::reverse;
        }

        if (fsm::innerState != NULL)
        {
            fsm::innerState();
            return;
        }

        fsm::state = fsm::normalSearch;
    }
}

#endif