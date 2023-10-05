#ifndef _fsm_avoid_fall_front_left_h_
#define _fsm_avoid_fall_front_left_h_

#include "fsm.h"

namespace avoidFallFrontLeft_fsm
{
    void reverse();
    void turnRight();

    void reverse()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid fall front left: reverse");

            fsm::priorInnerState = fsm::innerState;

            fsm::referenceTime = millis();
            motors::goBack(fsm::configValues->avoidFallFrontReverseSpeed);
        }

        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidFallFrontReverseDuration)
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
            motors::turnRight(fsm::configValues->avoidFallFrontTurnSpeed);
#if defined(ENABLE_GYRO)
            gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
#endif
            fsm::referenceTime = millis();
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

        fsm::currentTime = millis();
        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidFallFrontMaxTurnDuration)
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

        // TODO: add transitions for proximity sensors

        if (fsm::innerState != NULL)
        {
            fsm::innerState();
            return;
        }

        fsm::state = fsm::defaultExploringState;
    }
}

#endif