#ifndef _fsm_aim_front_left_h_
#define _fsm_aim_front_left_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_FRONT_LEFT

namespace fsm
{
    void aimFrontLeft()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("aim front left");

            fsm::priorState = fsm::state;

#if defined(ENABLE_GYRO)
            if (gyroscope::status == 0)
            {
                gyroscope::mpu.update();
                gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
            }
#endif
            fsm::referenceTime = millis();
            motors::turnLeft(fsm::configValues->aimFrontSideSpeedOuter);
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_BACK

#if defined(ENABLE_GYRO)
        if (gyroscope::status == 0)
        {
            gyroscope::mpu.update();
            gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();

            if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimFrontLeft_fsm::turnAngle)
            {
                fsm::state = fsm::defaultExploringState;
                return;
            }
        }
#endif

        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->aimFrontSideMaxTurnDuration)
        {
            fsm::state = fsm::defaultExploringState;
            return;
        }
    }
}

#endif
#endif