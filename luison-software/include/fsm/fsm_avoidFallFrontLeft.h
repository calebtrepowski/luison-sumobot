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
            DEBUG_PRINTLN(std::string("avoid fall front left: reverse"));

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
        using namespace gyroscope;
        if (fsm::innerState != fsm::priorInnerState)
        {
#ifdef DEBUG
            Serial.println("avoid fall front left: turn right");
#endif

#ifdef DEBUG_BLUETOOTH
            bluetooth::SerialBT.println("avoid fall front left: turn right");
#endif
            fsm::priorInnerState = fsm::innerState;
            mpu.update();
            motors::turnRight(turnSpeed);
            referenceAngleZ = mpu.getAngleZ();
            referenceTime = millis();
        }

        mpu.update();
        currentAngleZ = mpu.getAngleZ();
        currentTime = millis();

        if (abs(currentAngleZ - referenceAngleZ) > turnAngle || currentTime - referenceTime > maxTurnDuration)
        {
            fsm::innerState = NULL;
        }
    }
}

namespace fsm
{
    void avoidFallFrontLeft()
    {

        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN(std::string("avoid fall front left"));

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