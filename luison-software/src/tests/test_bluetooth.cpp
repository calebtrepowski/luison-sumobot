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
    bluetooth::echo();
    // if (!active)
    // {
    //     DEBUG_PRINTLN(std::string("Idle"));
    // }
    // if (bluetooth::loadStart(active))
    // {
    //     DEBUG_PRINTLN(std::string("Estado inicial"));
    // }
    // delay(100);
}

#endif