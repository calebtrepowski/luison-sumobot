#ifdef LUISON_FSM
#include <Arduino.h>

#include "pinNumbers.h"

#include "gyroscope.h"
#include "line.h"

#ifndef DRIVER_ZEROLAG
#include "motor.h"
#else
#include "motorZerolag.h"
#endif

#include "onOffControl.h"
#include "onOffInterruption.h"
#include "proximity.h"
#include "fsm/fsm.h"

void setup()
{
    gyroscope::setup();
    line::setup();
    motors::setup();
    onOffControl::setup();
    proximity::setup();

    onOffInterruption::setOnOffInterruption();

    fsm::priorState = NULL;
    fsm::state = fsm::idle;
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("setup");
#endif
}

void loop()
{
    fsm::state();
}

#endif