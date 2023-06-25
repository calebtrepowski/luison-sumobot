#ifndef _fsm_diagonal_attack_h_
#define _fsm_diagonal_attack_h_

#include "fsm.h"

#ifdef ENABLE_STRATEGY_DIAGONAL_ATTACK

namespace diagonalAttack_fsm
{
    const uint_fast8_t moveForwardSpeed = DIAGONAL_ATTACK_MOVE_FORWARD_SPEED;
    const uint_fast8_t moveForwardDuration = DIAGONAL_ATTACK_MOVE_FORWARD_DURATION;
    uint_fast32_t currentTime;
    uint_fast32_t referenceTime;
    const uint_fast8_t turnAimSpeedOuter = DIAGONAL_ATTACK_TURN_AIM_SPEED_OUTER;
    const uint_fast8_t turnAimSpeedInner = DIAGONAL_ATTACK_TURN_AIM_SPEED_INNER;
    const uint_fast8_t turnAimDuration = DIAGONAL_ATTACK_TURN_AIM_DURATION;

    void moveForward();
    void turnAim();

    void moveForward()
    {
        if (fsm::innerState != fsm::priorInnerState)
        {
            DEBUG_PRINTLN("diagonal attack: move forward");

            fsm::priorInnerState = fsm::innerState;

            referenceTime = millis();
            motors::goForward(moveForwardSpeed);
        }

        line::readValues();
        TRANSITION_AVOID_FALL_FRONT_LEFT
        TRANSITION_AVOID_FALL_FRONT_RIGHT

        proximity::readStates();
        TRANSITION_ATTACK_FRONT
        TRANSITION_AIM_FRONT_RIGHT
        TRANSITION_AIM_RIGHT
        TRANSITION_AIM_BACK

        currentTime = millis();

        if (currentTime - referenceTime > moveForwardDuration)
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

            referenceTime = millis();
            motors::goForward(turnAimSpeedInner, turnAimSpeedOuter);
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

        currentTime = millis();

        if (currentTime - referenceTime > turnAimDuration)
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