#ifndef _fsm_h_
#define _fsm_h_

#include "fsm_configValues.h"

#ifndef DRIVER_ZEROLAG
#include "motor.h"
#else
#include "motorZerolag.h"
#endif

#include "line.h"
#include "gyroscope.h"
#include "proximity.h"

namespace fsm
{
    /* state handlers */
    typedef void (*STATE_HANDLER_T)();
    typedef void (*INNER_STATE_HANDLER_T)();

    volatile STATE_HANDLER_T priorState, state;
    volatile INNER_STATE_HANDLER_T priorInnerState, innerState;

    /* main states */
    void idle();

#ifdef ENABLE_STATE_AVOID_FALL_FRONT_LEFT
    void avoidFallFrontLeft();
#define TRANSITION_AVOID_FALL_FRONT_LEFT      \
    if (LINE_FRONT_LEFT_DETECTED)             \
    {                                         \
        fsm::state = fsm::avoidFallFrontLeft; \
        return;                               \
    }
#else
#define TRANSITION_AVOID_FALL_FRONT_LEFT ;
#endif

#ifdef ENABLE_STATE_AVOID_FALL_FRONT_RIGHT
    void avoidFallFrontRight();
#define TRANSITION_AVOID_FALL_FRONT_RIGHT      \
    if (LINE_FRONT_RIGHT_DETECTED)             \
    {                                          \
        fsm::state = fsm::avoidFallFrontRight; \
        return;                                \
    }
#else
#define TRANSITION_AVOID_FALL_FRONT_RIGHT ;
#endif

#ifdef ENABLE_STATE_ATTACK_FRONT
    void attackFront();
#define TRANSITION_ATTACK_FRONT              \
    if (OPPONENT_DETECTED_FRONT_CENTER_ONLY) \
    {                                        \
        fsm::state = fsm::attackFront;       \
        return;                              \
    }
#else
#define TRANSITION_ATTACK_FRONT ;
#endif

#ifdef ENABLE_STATE_NORMAL_SEARCH
    void normalSearch();
#endif
#ifdef ENABLE_STATE_AIM_FRONT_RIGHT
    void aimFrontRight();
#define TRANSITION_AIM_FRONT_RIGHT       \
    if (OPPONENT_DETECTED_FRONT_RIGHT)   \
    {                                    \
        fsm::state = fsm::aimFrontRight; \
        return;                          \
    }
#else
#define TRANSITION_AIM_FRONT_RIGHT ;
#endif

#ifdef ENABLE_STATE_AIM_FRONT_LEFT
    void aimFrontLeft();
#define TRANSITION_AIM_FRONT_LEFT       \
    if (OPPONENT_DETECTED_FRONT_LEFT)   \
    {                                   \
        fsm::state = fsm::aimFrontLeft; \
        return;                         \
    }
#else
#define TRANSITION_AIM_FRONT_LEFT ;
#endif

#ifdef ENABLE_STATE_AIM_LEFT
    void aimLeft();
#define TRANSITION_AIM_LEFT        \
    if (OPPONENT_DETECTED_LEFT)    \
    {                              \
        fsm::state = fsm::aimLeft; \
        return;                    \
    }
#else
#define TRANSITION_AIM_LEFT ;
#endif

#ifdef ENABLE_STATE_AIM_RIGHT
    void aimRight();
#define TRANSITION_AIM_RIGHT        \
    if (OPPONENT_DETECTED_RIGHT)    \
    {                               \
        fsm::state = fsm::aimRight; \
        return;                     \
    }
#else
#define TRANSITION_AIM_RIGHT ;
#endif

#ifdef ENABLE_STATE_AIM_BACK
    void aimBack();
#define TRANSITION_AIM_BACK        \
    if (OPPONENT_DETECTED_BACK)    \
    {                              \
        fsm::state = fsm::aimBack; \
        return;                    \
    }
#else
#define TRANSITION_AIM_BACK ;
#endif

    /* initial strategies */
    void diagonalAttack();
    void diagonalKickBack();
}

#include "fsm_idle.h"
#include "fsm_normalSearch.h"
#include "fsm_avoidFallFrontRight.h"
#include "fsm_avoidFallFrontLeft.h"
#include "fsm_attackFront.h"
#include "fsm_aimFrontRight.h"
#include "fsm_aimFrontLeft.h"
#include "fsm_aimLeft.h"
#include "fsm_aimRight.h"
#include "fsm_aimBack.h"

#endif