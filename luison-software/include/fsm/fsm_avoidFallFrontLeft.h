#ifndef _fsm_avoid_fall_front_left_h_
#define _fsm_avoid_fall_front_left_h_

#include "fsm.h"

namespace avoidFallFrontLeft_fsm
{
    const uint_fast8_t reverseDuration = AVOID_FALL_FRONT_REVERSE_DURATION;  // ms
    const uint_fast8_t maxTurnDuration = AVOID_FALL_FRONT_MAX_TURN_DURATION; // ms
    uint_fast32_t currentTime;
    const uint_fast8_t turnAngle = AVOID_FALL_FRONT_TURN_ANGLE; // °
    uint_fast32_t referenceTime;
    const uint_fast8_t reverseSpeed = AVOID_FALL_FRONT_REVERSE_SPEED; // ms
    const uint_fast8_t turnSpeed = AVOID_FALL_FRONT_TURN_SPEED;       // ms

    void reverse();
    void turnRight();

    void reverse()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid fall front left: reverse");

            fsm::priorInnerState = fsm::innerState;

            referenceTime = millis();
            motors::goBack(reverseSpeed);
        }

        currentTime = millis();

        if (currentTime - referenceTime > reverseDuration)
        {
            fsm::innerState = turnRight;
        }
    }

    void turnRight()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid fall front left: turn right");

            fsm::priorInnerState = fsm::innerState;
#if defined(ENABLE_GYRO)
            gyroscope::mpu.update();
#endif
            motors::turnRight(turnSpeed);
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
    void avoidFallFrontLeft()
    {

        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid fall front left");

            fsm::priorState = fsm::state;
            fsm::priorInnerState = NULL;
            fsm::innerState = avoidFallFrontLeft_fsm::reverse;
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