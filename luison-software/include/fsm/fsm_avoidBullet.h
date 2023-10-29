#ifndef _fsm_avoid_bullet_h_
#define _fsm_avoid_bullet_h_

#include "fsm.h"

namespace avoidBullet_fsm
{
    void turnRight(void);
    void goForward(void);
    void turnLeft(void);

    void turnRight(void)
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid bullet: turn right");

            fsm::priorInnerState = fsm::innerState;

            motors::turnRight(fsm::configValues->avoidBulletTurnRightSpeed);
            fsm::referenceTime = millis();
        }

        fsm::currentTime = millis();
        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidBulletTurnRightDuration)
        {
            fsm::innerState = goForward;
            return;
        }
    }
    void goForward(void)
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid bullet: go forward");

            fsm::priorInnerState = fsm::innerState;

            motors::goForward(fsm::configValues->avoidBulletGoForwardSpeed);
            fsm::referenceTime = millis();
        }

        fsm::currentTime = millis();
        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidBulletGoForwardDuration)
        {
            fsm::innerState = turnLeft;
            return;
        }
    }

    void turnLeft(void)
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("avoid bullet: turn left");

            fsm::priorInnerState = fsm::innerState;

            motors::turnLeft(fsm::configValues->avoidBulletTurnLeftSpeed);
            fsm::referenceTime = millis();
        }

        fsm::currentTime = millis();
        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->avoidBulletTurnLeftDuration)
        {
            fsm::innerState = NULL;
            return;
        }
    }
}

namespace fsm
{
    void avoidBullet(void)
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("avoid bullet");

            fsm::priorState = fsm::state;
            fsm::priorInnerState = NULL;
            fsm::innerState = avoidBullet_fsm::turnRight;
        }

        line::readValues();
        proximity::readStates();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_LEFT
        TRANSITION_AIM_FRONT_LEFT
        TRANSITION_AIM_BACK

        if (fsm::innerState != NULL)
        {
            fsm::innerState();
            return;
        }

        fsm::state = fsm::defaultExploringState;
    }
}

#endif