#ifndef _fsm_wait_sensors_h_
#define _fsm_wait_sensors_h_

#include "fsm.h"

#ifdef ENABLE_STRATEGY_WAIT_SENSORS

namespace waitSensors_fsm
{
    int goForwardSpeed = WAIT_SENSORS_MOVE_FORWARD_SPEED;
    int goForwardDuration = WAIT_SENSORS_MOVE_FORWARD_DURATION;
    int waitMaxDuration = WAIT_SENSORS_WAIT_MAX_DURATION;
    uint_fast32_t referenceTime;
    uint_fast32_t currentTime;
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

            waitSensors_fsm::referenceTime = millis();
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

        waitSensors_fsm::currentTime = millis();

        if (waitSensors_fsm::goingForward)
        {
            if (waitSensors_fsm::currentTime - waitSensors_fsm::referenceTime > waitSensors_fsm::goForwardDuration)
            {
                waitSensors_fsm::goingForward = false;
                motors::brake();
                DEBUG_PRINTLN("wait sensors: brake");
                waitSensors_fsm::referenceTime = waitSensors_fsm::currentTime;
            }
        }
        else
        {
            if (waitSensors_fsm::currentTime - waitSensors_fsm::referenceTime > waitSensors_fsm::waitMaxDuration)
            {
                waitSensors_fsm::goingForward = true;
                motors::goForward(waitSensors_fsm::goForwardSpeed);
                DEBUG_PRINTLN("wait sensors: go forward");
                waitSensors_fsm::referenceTime = waitSensors_fsm::currentTime;
            }
        }
    }
}

#endif

#endif