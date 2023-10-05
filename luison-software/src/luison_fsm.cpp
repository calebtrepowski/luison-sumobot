#ifdef LUISON_FSM
#include <Arduino.h>
#include "onOffKillSwitch.h"
#include "RGBLed.h"
#include "dipSwitch.h"
#include "fsm/fsm.h"

void setup()
{
    onOffControl::setup();
    dipSwitch::setup();
    RGBLed::showGreen();
    fsm::setup();
}

void loop()
{
    while (!digitalRead(KILL_SWITCH_START))
    {
    }

    fsm::initialAction(dipSwitch::readInt());

    RGBLed::showRed();

    while (digitalRead(KILL_SWITCH_START))
    {
        fsm::state();
    }

    fsm::cleanupAction();
    RGBLed::showGreen();
}

#endif