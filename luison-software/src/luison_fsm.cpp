#ifdef LUISON_FSM
#include <Arduino.h>

#include "pinNumbers.h"
#include "gyroscope.h"
#include "onOffControl.h"
#include "proximity.h"
#include "fsm/fsm.h"

void setup()
{
    gyroscope::setup();
    line::setup();
    motors::setup();
    onOffControl::setup();
    proximity::setup();

    fsm::priorState = NULL;
    fsm::state = fsm::idle;

    DEBUG_BEGIN(MONITOR_SPEED);
}

void loop()
{
    if (!onOffControl::active)
    {
        fsm::state = fsm::idle;
    }

    fsm::state();

    if (onOffControl::loadStart(onOffControl::active))
    {
        fsm::state = fsm::normalSearch;
    };
}

#endif