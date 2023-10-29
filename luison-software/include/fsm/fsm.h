#ifndef _fsm_h_
#define _fsm_h_

#include "fsm_configValues.h"
#include "motorDriver.h"
#include "line.h"
#if defined(ENABLE_GYRO)
#include "gyroscope.h"
#endif
#include "proximity.h"
#include "debugUtils.h"

namespace fsm
{
    /* state handlers */
    typedef void (*STATE_HANDLER_T)();
    typedef void (*INNER_STATE_HANDLER_T)();

    volatile STATE_HANDLER_T priorState, state, defaultExploringState;
    volatile INNER_STATE_HANDLER_T priorInnerState, innerState;

    ConfigValues *configValues = &metalRing;

    uint_fast32_t currentTime;
    uint_fast32_t referenceTime;

    void initializeValues(void);

    /* main states */
    void idle();

#ifdef ENABLE_STATE_AVOID_FALL_FRONT_LEFT
    void avoidFallFrontLeft();
#define TRANSITION_AVOID_FALL_FRONT_LEFT                         \
    if (LINE_FRONT_LEFT_DETECTED && OPPONENT_NOT_DETECTED_FRONT) \
    {                                                            \
        fsm::state = fsm::avoidFallFrontLeft;                    \
        if (fsm::innerState != NULL)                             \
        {                                                        \
            fsm::innerState = NULL;                              \
        }                                                        \
        return;                                                  \
    }
#else
#define TRANSITION_AVOID_FALL_FRONT_LEFT ;
#endif

#ifdef ENABLE_STATE_AVOID_FALL_FRONT_RIGHT
    void avoidFallFrontRight();
#define TRANSITION_AVOID_FALL_FRONT_RIGHT                         \
    if (LINE_FRONT_RIGHT_DETECTED && OPPONENT_NOT_DETECTED_FRONT) \
    {                                                             \
        fsm::state = fsm::avoidFallFrontRight;                    \
        if (fsm::innerState != NULL)                              \
        {                                                         \
            fsm::innerState = NULL;                               \
        }                                                         \
        return;                                                   \
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
        if (fsm::innerState != NULL)         \
        {                                    \
            fsm::innerState = NULL;          \
        }                                    \
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
        if (fsm::innerState != NULL)     \
        {                                \
            fsm::innerState = NULL;      \
        }                                \
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
        if (fsm::innerState != NULL)    \
        {                               \
            fsm::innerState = NULL;     \
        }                               \
        return;                         \
    }
#else
#define TRANSITION_AIM_FRONT_LEFT ;
#endif

#ifdef ENABLE_STATE_AIM_LEFT
    void aimLeft();
#define TRANSITION_AIM_LEFT          \
    if (OPPONENT_DETECTED_LEFT)      \
    {                                \
        fsm::state = fsm::aimLeft;   \
        if (fsm::innerState != NULL) \
        {                            \
            fsm::innerState = NULL;  \
        }                            \
        return;                      \
    }
#else
#define TRANSITION_AIM_LEFT ;
#endif

#ifdef ENABLE_STATE_AIM_RIGHT
    void aimRight();
#define TRANSITION_AIM_RIGHT         \
    if (OPPONENT_DETECTED_RIGHT)     \
    {                                \
        fsm::state = fsm::aimRight;  \
        if (fsm::innerState != NULL) \
        {                            \
            fsm::innerState = NULL;  \
        }                            \
        return;                      \
    }
#else
#define TRANSITION_AIM_RIGHT ;
#endif

#ifdef ENABLE_STATE_AIM_BACK
    void aimBack();
#define TRANSITION_AIM_BACK          \
    if (OPPONENT_DETECTED_BACK)      \
    {                                \
        fsm::state = fsm::aimBack;   \
        if (fsm::innerState != NULL) \
        {                            \
            fsm::innerState = NULL;  \
        }                            \
        return;                      \
    }
#else
#define TRANSITION_AIM_BACK ;
#endif

/* initial strategies */
#ifdef ENABLE_STRATEGY_DIAGONAL_ATTACK
    void diagonalAttack();
#endif

#ifdef ENABLE_STRATEGY_DIAGONAL_KICKBACK
    void diagonalKickBack();
#endif

#ifdef ENABLE_STRATEGY_WAIT_SENSORS
    void waitSensors();
#endif

#ifdef ENABLE_STRATEGY_AVOID_BACK
    void avoidBack();
#endif

#ifdef ENABLE_STRATEGY_AVOID_BACK_IN_J
    void avoidBackInJ(void);
#endif

#ifdef ENABLE_STRATEGY_AVOID_BACK_IN_J_FRONT
    void avoidBackInJFront(void);
#endif

#ifdef ENABLE_STRATEGY_BULLET
    void bullet();
#endif

#ifdef ENABLE_STRATEGY_AVOID_BULLET
    void avoidBullet(void);
#endif

    void setup()
    {
        proximity::setup();
        line::setup();
#ifdef ENABLE_GYRO
        gyroscope::setup();
#endif
        motors::setup();
        initializeValues();

        fsm::priorState = NULL;
        fsm::state = fsm::idle;
        fsm::state();
    }

    void initialAction(int initialStrategy = 0)
    {
        switch (initialStrategy)
        {
        case 0:
            fsm::defaultExploringState = fsm::normalSearch;
            fsm::state = fsm::normalSearch;
            break;
        case 1:
            fsm::defaultExploringState = fsm::waitSensors;
            fsm::state = fsm::waitSensors;
            break;
        case 2:
            fsm::defaultExploringState = fsm::waitSensors;
            fsm::state = fsm::avoidBullet;
            break;
        // case 3:
        //     fsm::defaultExploringState = fsm::waitSensors;
        //     fsm::state = fsm::avoidBack;
        //     break;
        // case 4:
        //     fsm::defaultExploringState = fsm::waitSensors;
        //     fsm::state = fsm::avoidBackInJ;
        //     break;
        // case 5:
        //     fsm::defaultExploringState = fsm::waitSensors;
        //     fsm::state = fsm::avoidBackInJFront;
        //     break;
        // case 6:
        //     fsm::defaultExploringState = fsm::normalSearch;
        //     fsm::state = fsm::bullet;
        //     break;
        default:
            fsm::defaultExploringState = fsm::normalSearch;
            fsm::state = fsm::normalSearch;
            break;
        }
    }

    void action()
    {
        state();
    }

    void cleanupAction()
    {
        priorState = NULL;
        state = idle;
        state();
    }
}

#include "fsm_configValues.h"
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
#include "fsm_diagonalAttack.h"
#include "fsm_diagonalKickBack.h"
#include "fsm_waitSensors.h"
#include "fsm_avoidBack.h"
#include "fsm_avoidBackInJ.h"
#include "fsm_avoidBackInJFront.h"
#include "fsm_bullet.h"
#include "fsm_avoidBullet.h"

#endif