#ifndef _fsm_diagonal_attack_h_
#define _fsm_diagonal_attack_h_

#include "fsm.h"

#ifdef ENABLE_STRATEGY_DIAGONAL_ATTACK

namespace diagonalAttack_fsm
{
    void moveForward();
    void turnAim();

    void moveForward()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("diagonal attack: move forward");

            fsm::priorInnerState = fsm::innerState;

            fsm::referenceTime = millis();
            motors::goForward(fsm::configValues->diagonalAttackMoveForwardSpeed);
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_BACK

        fsm::currentTime = millis();

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->diagonalAttackMoveForwardDuration)
        {
            fsm::innerState = turnAim;
        }
    }

    void turnAim()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("diagonal attack: turn aim");

            fsm::priorInnerState = fsm::innerState;

            fsm::referenceTime = millis();
            motors::goForward(fsm::configValues->diagonalTurnAimSpeedInner,
                              fsm::configValues->diagonalTurnAimSpeedOuter);
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

        if (fsm::currentTime - fsm::referenceTime > fsm::configValues->diagonalTurnAimDuration)
        {
            fsm::innerState = NULL;
        }
    }
}

namespace fsm
{
    void diagonalAttack()
    {
        if (fsm::state != fsm::priorState)
        {
            DEBUG_PRINTLN("diagonal attack");

            fsm::priorState = fsm::state;
            fsm::priorInnerState = NULL;
            fsm::innerState = diagonalAttack_fsm::moveForward;
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

#endif