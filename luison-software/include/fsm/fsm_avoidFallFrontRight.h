#ifndef _fsm_avoid_fall_front_right_h_
#define _fsm_avoid_fall_front_right_h_

#include "fsm.h"

namespace avoidFallFrontRight_fsm
{
    void reverse();
    void turnLeft();

    void reverse()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid fall front right: reverse");

            fsm::priorInnerState = fsm::innerState;

            fsm::referenceTime = millis();
            motors::goBack(fsm::configValues->avoidFallFrontReverseSpeed);
        }

        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidFallFrontReverseDuration)
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
    void avoidFallFrontRight()
    {

        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid fall front right");

            fsm::priorState = fsm::state;

            fsm::priorInnerState = NULL;
            fsm::innerState = avoidFallFrontRight_fsm::reverse;
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