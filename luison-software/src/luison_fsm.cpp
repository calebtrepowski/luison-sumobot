#ifdef LUISON_FSM
#include <Arduino.h>

#include "pinNumbers.h"
#include "gyroscope.h"
#include "line.h"
#include "motorDriver.h"
// #include "onOffControl.h"
// #include "onOffInterruption.h"
#include "proximity.h"
#include "fsm/fsm.h"
#include "bluetooth.h"

uint_fast8_t active;

void setup()
{
    gyroscope::setup();
    line::setup();
    motors::setup();
    // onOffControl::setup();
    proximity::setup();

    bluetooth::setup();

    // onOffInterruption::setOnOffInterruption();

    fsm::priorState = NULL;
    fsm::state = fsm::idle;

    active = false;

#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("setup");
#endif

#ifdef DEBUG_BLUETOOTH
    bluetooth::SerialBT.println("setup");
#endif
}

void loop()
{
    if (!active)
    {
        fsm::state = fsm::idle;
    }
    fsm::state();
    if(bluetooth::loadStart(active)){
        fsm::state = fsm::normalSearch;
    };
}

#endif