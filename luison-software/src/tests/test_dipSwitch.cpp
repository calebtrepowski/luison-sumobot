#ifdef TEST_DIP_SWITCH
#include <Arduino.h>
#include "debugUtils.h"
#include "dipSwitch.h"

void setup()
{
    dipSwitch::setup();
    DEBUG_BEGIN(MONITOR_SPEED);
}

void loop()
{
    DEBUG_PRINTLN(dipSwitch::readInt());
    delay(100);
}
#endif