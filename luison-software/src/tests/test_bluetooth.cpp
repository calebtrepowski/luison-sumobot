#ifdef TEST_BLUETOOTH
#include <Arduino.h>
#include "bluetooth.h"
#include "debugUtils.h"

uint_fast8_t active = 0;

void setup()
{
    bluetooth::setup();
}

void loop()
{
    // DEBUG_PRINTLN("Idle");
    bluetooth::echo();
    // if (!active)
    // {
    //     DEBUG_PRINTLN("Idle");
    // }
    // if (bluetooth::loadStart(active))
    // {
    //     DEBUG_PRINTLN("Estado inicial");
    // }
    // delay(100);
}

#endif