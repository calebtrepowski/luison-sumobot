#ifndef _fsm_aim_front_right_h_
#define _fsm_aim_front_right_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_FRONT_RIGHT

namespace fsm
{
    void aimFrontRight()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("aim front right");

            fsm::priorState = fsm::state;

#if defined(ENABLE_GYRO)
            gyroscope::mpu.update();
#endif
            motors::turnRight(fsm::configValues->aimFrontSideSpeedOuter);
#if defined(ENABLE_GYRO)
            gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
#endif
            fsm::referenceTime = millis();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_BACK

#if defined(ENABLE_GYRO)
        gyroscope::mpu.update();
        gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();

        if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimFrontRight_fsm::turnAngle)
        {
            fsm::state = fsm::defaultExploringState;
            return;
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