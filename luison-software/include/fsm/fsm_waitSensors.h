#ifndef _fsm_wait_sensors_h_
#define _fsm_wait_sensors_h_

#include "fsm.h"

#ifdef ENABLE_STRATEGY_WAIT_SENSORS

namespace waitSensors_fsm
{
    bool goingForward;
}

namespace fsm
{
    void waitSensors()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("wait sensors");

            fsm::priorState = fsm::state;

            fsm::referenceTime = millis();
            waitSensors_fsm::goingForward = false;
            motors::brake();
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_BACK

        fsm::currentTime = millis();

        if (waitSensors_fsm::goingForward)
        {
            if (fsm::currentTime - fsm::referenceTime > fsm::configValues->waitSensorsMoveForwardDuration)
            {
                waitSensors_fsm::goingForward = false;
                motors::brake();
                DEBUG_PRINTLN("wait sensors: brake");
                fsm::referenceTime = fsm::currentTime;
            }
        }
        else
        {
            if (fsm::currentTime - fsm::referenceTime > fsm::configValues->waitSensorsWaitMaxDuration)
            {
                waitSensors_fsm::goingForward = true;
                motors::goForward(fsm::configValues->waitSensorsMoveForwardSpeed);
                DEBUG_PRINTLN("wait sensors: go forward");
                fsm::referenceTime = fsm::currentTime;
            }
        }
    }
}

#endif

#endif