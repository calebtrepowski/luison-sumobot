#ifndef _fsm_h_
#define _fsm_h_

#include "motor.h"
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
    void avoidFallFrontLeft();
    void avoidFallFrontRight();
    void attackFront();
    void normalSearch();
    void aimFrontRight();
    void aimFrontLeft();
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

#endif