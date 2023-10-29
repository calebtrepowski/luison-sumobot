#ifndef _fsm_aim_left_h_
#define _fsm_aim_left_h_

#include "fsm.h"

#ifdef ENABLE_STATE_AIM_LEFT

namespace fsm
{
    void aimLeft()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("aim left");

            fsm::priorState = fsm::state;

#if defined(ENABLE_GYRO)
            gyroscope::mpu.update();
#endif
            motors::turnLeft(fsm::configValues->aimSideSpeedOuter);
#if defined(ENABLE_GYRO)
            gyroscope::referenceAngleZ = gyroscope::mpu.getAngleZ();
#endif
            fsm::referenceTime = millis();
        }

        line::readValues();
        proximity::readStates();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        TRANSITION_ATTACK_FRONT
        // TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_BACK

#if defined(ENABLE_GYRO)
        gyroscope::mpu.update();
        gyroscope::currentAngleZ = gyroscope::mpu.getAngleZ();

        if (abs(gyroscope::currentAngleZ - gyroscope::referenceAngleZ) > aimLeft_fsm::turnAngle)
        {
            fsm::state = fsm::defaultExploringState;
            return;
        }
#endif

        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->aimSideMaxTurnDuration)
        {
            fsm::state = fsm::defaultExploringState;
            return;
        }
    }
}

#endif

#endif