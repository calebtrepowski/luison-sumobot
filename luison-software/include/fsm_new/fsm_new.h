#ifndef _fsm_new_h_
#define _fsm_new_h_

#include "motorDriver.h"

/* Model for improved fsm scheme */

namespace fsm_new
{
    typedef void (*StateAction_t)();

    struct State
    {
        StateAction_t initialAction;
        StateAction_t permanentAction;
        StateAction_t checkTransition;
    };

    State *state, *nextState;

    State idle, normalSearch;

    void idleInitial()
    {
        motors::brake();
    }
    void idlePermanentAction()
    {
    }
    void idleTransition()
    {
    }

    void setup()
    {
        idle = {.initialAction = idleInitial,
                .permanentAction = idlePermanentAction,
                .checkTransition = idleTransition};
    }

}

#endif
