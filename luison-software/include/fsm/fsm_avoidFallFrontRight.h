#ifndef _fsm_avoid_fall_front_right_h_
#define _fsm_avoid_fall_front_right_h_

#include "fsm.h"

namespace avoidFallFrontRight_fsm
{
    const uint_fast8_t reverseDuration = AVOID_FALL_FRONT_REVERSE_DURATION;  // ms
    const uint_fast8_t maxTurnDuration = AVOID_FALL_FRONT_MAX_TURN_DURATION; // ms
    uint_fast32_t currentTime;
    const uint_fast8_t turnAngle = AVOID_FALL_FRONT_TURN_ANGLE; // °
    uint_fast32_t referenceTime;
    const uint_fast8_t reverseSpeed = AVOID_FALL_FRONT_REVERSE_SPEED; // ms
    const uint_fast8_t turnSpeed = AVOID_FALL_FRONT_TURN_SPEED;       // ms

    void reverse();
    void turnLeft();

    void reverse()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid fall front right: reverse");

            fsm::priorInnerState = fsm::innerState;

            referenceTime = millis();
            motors::goBack(reverseSpeed);
        }

        currentTime = millis();

        if (currentTime - referenceTime > reverseDuration)
        {
            fsm::innerState = turnLeft;
        }
    }

    void turnLeft()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid fall front right: turn left");

            fsm::priorInnerState = fsm::innerState;

#if defined(ENABLE_GYRO)
            gyroscope::mpu.update();
#endif
            motors::turnLeft(turnSpeed);
#if defined(ENABLE_GYRO)
            gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
#endif
            referenceTime = millis();
        }

#if defined(ENABLE_GYRO)
        gyroscope::mpu.update();
        gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();
        if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > turnAngle)
        {
            fsm::innerState = NULL;
            return;
        }
#endif
        
        currentTime = millis();
        if (currentTime - referenceTime > maxTurnDuration)
        {
            fsm::innerState = NULL;
            return;
        }
    }
}

namespace fsm
{
    void avoidFallFrontRight()
    {

        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid fall front right");

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